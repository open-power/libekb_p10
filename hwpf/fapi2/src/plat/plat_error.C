#include "plat_error.H"
#include "plat_utils.H"

namespace fapi2
{
/**
 *  @brief Function to check clock redundant mode is enabled in the system
 *
 *  Redundant mode is enabled, if the functional clock targets is greater than
 *  one in the system. Default behaviour is redundant mode disabled.
 *  Any internal failures during this function execution results redundant
 *  mode as disabled.
 *
 *  return true if clock redundant mode is enabled, false otherwise
 */
bool clock_redundancy_is_enabled()
{
	auto constexpr NUM_CLOCK_FOR_REDUNDANT_MODE = 2;

	struct pdbg_target *clock_target;
	uint8_t clock_count = 0;
	uint8_t buf[5];
	pdbg_for_each_class_target("oscrefclk", clock_target)
	{
		if (!pdbg_target_get_attribute_packed(
			clock_target, "ATTR_HWAS_STATE", "41", 1, buf)) {
			FAPI_ERR("Can not read(%s) ATTR_HWAS_STATE attribute",
				 pdbg_target_path(clock_target));
			continue;
		}
		// isFuntional bit is stored in 4th byte and bit 3 position
		// in HWAS_STATE
		if (buf[4] & 0x20)
			clock_count++;
	}

	if (clock_count != 1 && clock_count != 2) {
		FAPI_ERR("Invalid number (%d) of clock target found",
			 clock_count);
		return false;
	}

	if (clock_count == NUM_CLOCK_FOR_REDUNDANT_MODE) {
		FAPI_INF("Clock redundant mode(%d) enabled", clock_count);
		return true;
	}

	FAPI_INF("Clock redundant mode(%d) disabled", clock_count);
	return false;
}

/**
 * @brief Used to special handling of clock errors.
 *
 * The defined api is used to modify the callout and guard info
 * specific to clock failures.
 *
 * @param[in,out] ffdc        ffdc data which need to be updated if it is clock
 * failure
 * @param[in,out] hwCallout   reference of hwcallout with clock related hwid
 * @param[in] deconfRefTarget indicates whether reference target need to be
 * deconfigured or not
 *
 * @return void
 */
static void process_clock_callout(FFDC &ffdc, HWCallout &hwCallout,
				  const bool deconfRefTarget)
{
	// Planar callout is required since, clock is not a FRU, its parent has
	// to be called out, and clock targets parent is Planar.
	hwCallout.isPlanarCallout = true;

	// This is an override to CDG defined in error xml. We cant add this
	// guard in xml, since xml is comon for other systems also, where
	// deconfigured is not required.
	if (deconfRefTarget) {
		// For clock failures, reference target is always expected in
		// cdg for callout. If it is not there, which means, this guard
		// is not required.
		for (auto &cdg : ffdc.hwp_errorinfo.cdg_targets) {
			if (cdg.target_entity_path ==
			    hwCallout.target_entity_path) {
				cdg.deconfigure = true;
				cdg.guard = false;
				cdg.guard_type = plat_GardTypeEnum_tostring(
				    GardTypes::GardType::GARD_NULL);
			}
		}
	}
}

void process_HW_callout(FFDC &ffdc, const bool deconfRefTarget)
{
	for (auto &hwcallout : ffdc.hwp_errorinfo.hwcallouts) {
		// only PROC_REF_CLOCK & PCI_REF_CLOCK failure is expected in
		// BMC context.
		if ((hwcallout.hwid == "PROC_REF_CLOCK") ||
		    (hwcallout.hwid == "PCI_REF_CLOCK")) {
			process_clock_callout(ffdc, hwcallout, deconfRefTarget);
		}
	}
}
} // namespace fapi2

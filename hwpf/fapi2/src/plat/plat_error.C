#include "plat_error.H"
#include "plat_utils.H"

namespace fapi2
{
/**
 * @brief Used to special handling of clock errors.
 *
 * The defined api is used to modify the callout and guard info
 * specific to clock failures.
 *
 * @param[in,out] ffdc        ffdc data which need to be updated if it is clock failure
 * @param[in,out] hwCallout   reference of hwcallout with clock related hwid
 * @param[in] deconfRefTarget indicates whether reference target need to be deconfigured or not
 *
 * @return void
 */
static void process_clock_callout(FFDC &ffdc, HWCallout& hwCallout, const bool deconfRefTarget)
{
	// Planar callout is required since, clock is not a FRU, its parent has
	// to be called out, and clock targets parent is Planar.
	hwCallout.isPlanarCallout = true;

	// This is an override to CDG defined in error xml. We cant add this guard
	// in xml, since xml is comon for other systems also, where deconfigured is not
	// required.
	if (deconfRefTarget)
	{
		// For clock failures, reference target is always expected in cdg
		// for callout. If it is not there, which means, this guard is not
		// required.
		for (auto &cdg : ffdc.hwp_errorinfo.cdg_targets)
		{
			if (cdg.target_entity_path == hwCallout.target_entity_path)
			{
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
	for (auto &hwcallout : ffdc.hwp_errorinfo.hwcallouts)
	{
		// only PROC_REF_CLOCK failure is expected in BMC context.
		if (hwcallout.hwid == "PROC_REF_CLOCK")
		{
			process_clock_callout(ffdc, hwcallout, deconfRefTarget);
		}
	}
}
}

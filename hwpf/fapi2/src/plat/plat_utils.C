/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: hwpf/fapi2/src/plat/plat_utils.C $                            */
/*                                                                        */
/* IBM CONFIDENTIAL                                                       */
/*                                                                        */
/* EKB Project                                                            */
/*                                                                        */
/* COPYRIGHT 2011,2017                                                    */
/* [+] International Business Machines Corp.                              */
/*                                                                        */
/*                                                                        */
/* The source code for this program is not published or otherwise         */
/* divested of its trade secrets, irrespective of what has been           */
/* deposited with the U.S. Copyright Office.                              */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/**
 *  @file plat_utils.C
 *  @brief Implements fapi2 common utilities
 */

#include <assert.h>
#include <errno.h>
#include <error_info.H>
#include <plat_trace.H>
#include <return_code.H>
#include <stdint.h>
#include <target.H>
#include <time.h>
#include <utils.H>

extern "C" {
#include <libpdbg.h>
}

namespace fapi2
{
///
/// @brief Log an error.
///
void logError(fapi2::ReturnCode &io_rc, fapi2::errlSeverity_t i_sev,
	      bool i_unitTestError)
{
}

// will do the same as log error here in fapi2 plat implementation
void createPlatLog(fapi2::ReturnCode &io_rc, fapi2::errlSeverity_t i_sev)
{
	FAPI_DBG("Called createError()");
	logError(io_rc, i_sev, false);
}

///
/// @brief Associate an error to PRD PLID.
///
void log_related_error(const Target<TARGET_TYPE_ALL> &i_target,
		       fapi2::ReturnCode &io_rc,
		       const fapi2::errlSeverity_t i_sev,
		       const bool i_unitTestError)
{
	FAPI_DBG("Called log_related_error()");
	// Just commit the log in default implementation
	logError(io_rc, i_sev, i_unitTestError);
} // end log_related_error

///
/// @brief Delay this thread.
///
ReturnCode delay(uint64_t i_nanoSeconds, uint64_t i_simCycles, bool i_fixed)
{
	// void statements to keep the compiler from complaining
	// about unused variables.
	static_cast<void>(i_simCycles);
	static_cast<void>(i_fixed);
	struct timespec delay;
	int rc;

	delay.tv_sec = i_nanoSeconds / 1000000000;
	delay.tv_nsec = i_nanoSeconds % 1000000000;

	do {
		rc = nanosleep(&delay, &delay);
	} while (rc == -1 && errno == EINTR);

	if (rc)
		return FAPI2_RC_FALSE;

	return FAPI2_RC_SUCCESS;
}

///
/// @brief Assert a condition, and halt
///
/// @param[in] a boolean representing the assertion
///
void Assert(bool i_expression)
{
	assert(i_expression);
}

thread_local ReturnCode current_err;

ReturnCode plat_access_attr_SETMACRO(const char *attr, struct pdbg_target *tgt,
				     uint32_t size, uint32_t count, void *val)
{
	/* NULL targets use pdbg_dt_root */
	if (!tgt) {
		/* TODO: This should never happen but we've only got a partial
		 * implementation of targetting so far */
		FAPI_INF("NULL target reading attribute not implemented "
			 "reading %s. Using pdbg_dt_root for the moment.\n",
			 attr);
		tgt = pdbg_target_root();
	}

	if (!pdbg_target_set_attribute(tgt, attr, size, count, val)) {
		FAPI_ERR("Failed to write attribute %s\n", attr);
		return FAPI2_RC_FALSE;
	}

	return FAPI2_RC_SUCCESS;
}

ReturnCode plat_access_attr_GETMACRO(const char *attr, struct pdbg_target *tgt,
				     uint32_t size, uint32_t count, void *val)
{
	/* NULL targets use pdbg_dt_root */
	if (!tgt) {
		/* TODO: This should never happen but we've only got a partial
		 * implementation of targetting so far */
		FAPI_INF("NULL target reading attribute %s. Using pdbg_dt_root "
			 "for the moment.\n",
			 attr);
		tgt = pdbg_target_root();
	}

	if (!pdbg_target_get_attribute(tgt, attr, size, count, val)) {
		FAPI_ERR("Failed to read attribute %s\n", attr);
		return FAPI2_RC_FALSE;
	}

	return FAPI2_RC_SUCCESS;
}

std::string plat_HwCalloutEnum_tostring(HwCallouts::HwCallout hwcallout)
{
	// Initialize with "UN_SUPPORTED_PART" to return if unsupported enum
	// is given
	std::string hwcalloutstr = "UN_SUPPORTED_PART";

	switch (hwcallout) {
	case HwCallouts::HwCallout::PROC_REF_CLOCK:
		hwcalloutstr = "PROC_REF_CLOCK";
		break;
	case HwCallouts::HwCallout::PCI_REF_CLOCK:
		hwcalloutstr = "PCI_REF_CLOCK";
		break;
	default:
		FAPI_ERR("Unsupported HwCalloutEnum[%d] for tostring\n",
			 hwcallout);
		break;
	}
	return hwcalloutstr;
}

std::string plat_CalloutPriority_tostring(
    CalloutPriorities::CalloutPriority calloutpriority)
{
	// Initialize with "HIGH" to return if unsupported enum is given
	std::string calloutprioritystr = "HIGH";

	switch (calloutpriority) {
	case CalloutPriorities::CalloutPriority::LOW:
		calloutprioritystr = "LOW";
		break;
	case CalloutPriorities::CalloutPriority::MEDIUM:
		calloutprioritystr = "MEDIUM";
		break;
	case CalloutPriorities::CalloutPriority::HIGH:
		calloutprioritystr = "HIGH";
		break;
	case CalloutPriorities::CalloutPriority::NONE:
		calloutprioritystr = "NONE";
		break;
	default:
		FAPI_ERR("Unsupported CalloutPriorityEnum[%d] tostring\n",
			 calloutpriority);
		break;
	}
	return calloutprioritystr;
}

std::string plat_ProcedureCallout_tostring(
    ProcedureCallouts::ProcedureCallout procedurecallout)
{
	// Initialize with "CODE" to return if unsupported enum is given
	std::string procedurecalloutstr = "BMC0001";

	switch (procedurecallout) {
	case ProcedureCallouts::ProcedureCallout::CODE:
		procedurecalloutstr = "BMC0001";
		break;
	case ProcedureCallouts::ProcedureCallout::LVL_SUPPORT:
		procedurecalloutstr = "BMC0002";
		break;
	case ProcedureCallouts::ProcedureCallout::BUS_CALLOUT:
		procedurecalloutstr = "BMC0004";
		break;
	default:
		FAPI_ERR("Unsupported ProcedureCallout[%d[ for tostring\n",
			 procedurecallout);
		break;
	}
	return procedurecalloutstr;
}

std::string plat_GardTypeEnum_tostring(GardTypes::GardType gardtype)
{
	// Initialize with "GARD_NULL" to return if unsupported enum is given
	std::string gardtypestr = "GARD_NULL";

	switch (gardtype) {
	case GardTypes::GardType::GARD_NULL:
		gardtypestr = "GARD_NULL";
		break;
	case GardTypes::GardType::GARD_Spare:
		gardtypestr = "GARD_Spare";
		break;
	case GardTypes::GardType::GARD_User_Manual:
		gardtypestr = "GARD_User_Manual";
		break;
	case GardTypes::GardType::GARD_Unrecoverable:
		gardtypestr = "GARD_Unrecoverable";
		break;
	case GardTypes::GardType::GARD_Fatal:
		gardtypestr = "GARD_Fatal";
		break;
	case GardTypes::GardType::GARD_Predictive:
		gardtypestr = "GARD_Predictive";
		break;
	case GardTypes::GardType::GARD_Power:
		gardtypestr = "GARD_Power";
		break;
	case GardTypes::GardType::GARD_PHYP:
		gardtypestr = "GARD_PHYP";
		break;
	case GardTypes::GardType::GARD_Reconfig:
		gardtypestr = "GARD_Reconfig";
		break;
	case GardTypes::GardType::GARD_Void:
		gardtypestr = "GARD_Void";
		break;
	default:
		FAPI_ERR("Unsupported GardTypeEnum[%d] fro tostring\n",
			 gardtype);
		break;
	}
	return gardtypestr;
}
} // namespace fapi2

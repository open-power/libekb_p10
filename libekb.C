extern "C" {
#include <stdio.h>
#include <assert.h>
#include <stdarg.h>

#include <libpdbg.h>
}

#include "plat_trace.H"
#include "plat_utils.H"
#include "utils.H"

#include "libekb.H"

#include <platHwpErrParser.H>
#include <platHwpErrParserFFDC.H>
#include <return_code.H>
#include <hwp_pel_data.H>

static libekb_log_func_t __libekb_log_fn;
static void *__libekb_log_priv;
static int __libekb_log_level = LIBEKB_LOG_ERR;

static void libekb_log_default(void *priv, const char *fmt, va_list ap)
{
	vfprintf(stdout, fmt, ap);
}

int libekb_init(void)
{
	if (!__libekb_log_fn)
		libekb_set_logfunc(libekb_log_default, NULL);

	if (!pdbg_target_root()) {
		libekb_log(LIBEKB_LOG_ERR, "libpdbg not initialized\n");
		return -1;
	}

	return 0;
}

void libekb_set_logfunc(libekb_log_func_t fn, void *private_data)
{
	__libekb_log_fn = fn;
	__libekb_log_priv = private_data;
}

void libekb_set_loglevel(int loglevel)
{
	if (loglevel < LIBEKB_LOG_ERR)
		loglevel = LIBEKB_LOG_ERR;

	if (loglevel > LIBEKB_LOG_DBG)
		loglevel = LIBEKB_LOG_DBG;

	__libekb_log_level = loglevel;
}

void libekb_log(int loglevel, const char *fmt, ...)
{
	va_list ap;

	if (!__libekb_log_fn)
		return;

	if (loglevel > __libekb_log_level)
		return;

	va_start(ap, fmt);
	__libekb_log_fn(__libekb_log_priv, fmt, ap);
	va_end(ap);
}

/*
 * @brief Used to callout hardware error details.
 *
 * The defined api is used collect defined error info in error xml based on
 * given hwp return code (error code)
 *
 * @param rc used to pass hwp return code
 * @param hwp_errinfo used to pass buffer to fill error details
 *
 * @return void
 */
static void get_HWPErrorInfo(const fapi2::ReturnCode& rc, HWP_ErrorInfo& hwp_errinfo)
{
    // Get HWP rc and rc description from auto-generated code i.e error xml
    fapi2::PELData pelData = fapi2::parseHwpRc(rc);
    hwp_errinfo.rc = pelData[0].second;
    hwp_errinfo.rc_desc = pelData[1].second;

    // Get all available ffdc data (target attribute or some local required
    // data) which are present in error xml for particular error
    const fapi2::ErrorInfo* errorInfo = rc.getErrorInfo();
    for (auto ffdc : errorInfo->iv_ffdcs)
    {
        uint32_t ffdcId = ffdc->getFfdcId();
        uint32_t size;
        auto errData = ffdc->getData(size);

        std::vector<std::pair<std::string, std::string>> hwpFFDC;
        hwpFFDC = fapi2::parseHwpFfdc(ffdcId, errData, size);

        hwp_errinfo.ffdcs_data.insert(hwp_errinfo.ffdcs_data.end(),
                                      hwpFFDC.begin(), hwpFFDC.end());
    }

    // Get all available hardware callout record details which are present
    // in error xml for particular error
    for (auto hwcallout : errorInfo->iv_hwCallouts)
    {
        HWCallout hwcallout_data;
        hwcallout_data.hwid = fapi2::plat_HwCalloutEnum_tostring(hwcallout->iv_hw);
        hwcallout_data.callout_priority =
            fapi2::plat_CalloutPriority_tostring(hwcallout->iv_calloutPriority);
        fapi2::getTgtEntityPath(hwcallout->iv_refTarget,
                                hwcallout_data.target_entity_path);
        hwcallout_data.clkPos = hwcallout->iv_clkPos;

        hwp_errinfo.hwcallouts.push_back(hwcallout_data);
    }

    // Get all available procedures callout record details which are present
    // in error xml for particular error
    for (auto proc_callout : errorInfo->iv_procedureCallouts)
    {
        ProcedureCallout procedurecallout_data;
        procedurecallout_data.proc_callout =
            fapi2::plat_ProcedureCallout_tostring(proc_callout->iv_procedure);
        procedurecallout_data.callout_priority =
            fapi2::plat_CalloutPriority_tostring(proc_callout->iv_calloutPriority);

        hwp_errinfo.procedures_callout.push_back(procedurecallout_data);
    }

    // Get all available CDG (Callout,Deconfigure and Gard) record details
    // which are present in error xml for particular error
    for (auto cdg : errorInfo->iv_CDGs)
    {
        CDG_Target cdg_tgt_data;
        fapi2::getTgtEntityPath(cdg->iv_target,
                                cdg_tgt_data.target_entity_path);
        cdg_tgt_data.callout = cdg->iv_callout;
        cdg_tgt_data.callout_priority =
            fapi2::plat_CalloutPriority_tostring(cdg->iv_calloutPriority);
        cdg_tgt_data.deconfigure = cdg->iv_deconfigure;
        cdg_tgt_data.guard = cdg->iv_gard;
        cdg_tgt_data.guard_type = fapi2::plat_GardTypeEnum_tostring(cdg->iv_gardType);

        hwp_errinfo.cdg_targets.push_back(cdg_tgt_data);
    }
}

void libekb_get_ffdc(FFDC& ffdc)
{
    // Previous application called HWP return code
    fapi2::ReturnCode rc =  fapi2::current_err;

    if (rc == fapi2::FAPI2_RC_SUCCESS)
    {
        ffdc.ffdc_type = FFDC_TYPE_NONE;
        ffdc.message = "No FFDC, libekb_get_ffdc() called for success case";
    }
    else if (rc.getCreator() == fapi2::ReturnCode::CREATOR_HWP)
    {
        ffdc.ffdc_type = FFDC_TYPE_HWP;
        get_HWPErrorInfo(rc, ffdc.hwp_errorinfo);
        ffdc.message = "Collected HWP FFDC";
    }
    else if (rc.getCreator() == fapi2::ReturnCode::CREATOR_FAPI)
    {
        ffdc.ffdc_type = FFDC_TYPE_UNSUPPORTED;
        ffdc.message = "Un-Supported type to collect FFDC. Error created by FAPI";
	}
    else if (rc.getCreator() == fapi2::ReturnCode::CREATOR_PLAT)
    {
        ffdc.ffdc_type = FFDC_TYPE_UNSUPPORTED;
        ffdc.message = "Un-Supported type to collect FFDC. Error created by PLAT";
    }
    else
    {
        ffdc.ffdc_type = FFDC_TYPE_NONE;
        ffdc.message = "Unknown error creator. Failed to collect ffdc for error";
    }
}

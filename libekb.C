extern "C" {
#include <assert.h>
#include <libpdbg.h>
#include <stdarg.h>
#include <stdio.h>
}

#include "libekb.H"
#include "p10_extract_sbe_rc.H"
#include "plat_error.H"
#include "plat_trace.H"
#include "plat_utils.H"
#include "utils.H"

#include <error_info_defs.H>
#include <hwp_pel_data.H>
#include <platHwpErrParser.H>
#include <platHwpErrParserFFDC.H>
#include <return_code.H>
#include <set_sbe_error.H>

#include <string>
#include <vector>

static libekb_log_func_t __libekb_log_fn;
static void* __libekb_log_priv;
static int __libekb_log_level = LIBEKB_LOG_ERR;

static void libekb_log_default(void* priv, const char* fmt, va_list ap)
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

void libekb_set_logfunc(libekb_log_func_t fn, void* private_data)
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

void libekb_log(int loglevel, const char* fmt, ...)
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
static void get_HWPErrorInfo(const fapi2::ReturnCode& rc,
			     HWP_ErrorInfo& hwp_errinfo)
{
	// Get HWP rc and rc description from auto-generated code i.e error xml
	fapi2::PELData pelData = fapi2::parseHwpRc(rc);
	hwp_errinfo.rc = pelData[0].second;
	hwp_errinfo.rc_desc = pelData[1].second;

	// Get all available ffdc data (target attribute or some local required
	// data) which are present in error xml for particular error
	const fapi2::ErrorInfo* errorInfo = rc.getErrorInfo();
	for (auto ffdc : errorInfo->iv_ffdcs) {
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
	for (auto hwcallout : errorInfo->iv_hwCallouts) {
		HWCallout hwcallout_data;
		hwcallout_data.hwid =
		    fapi2::plat_HwCalloutEnum_tostring(hwcallout->iv_hw);

		hwcallout_data.callout_priority =
		    fapi2::plat_CalloutPriority_tostring(
			hwcallout->iv_calloutPriority);
		fapi2::getTgtEntityPath(hwcallout->iv_refTarget,
					hwcallout_data.target_entity_path);
		hwcallout_data.clkPos = hwcallout->iv_clkPos;

		hwp_errinfo.hwcallouts.push_back(hwcallout_data);
	}

	// Get all available procedures callout record details which are present
	// in error xml for particular error
	for (auto proc_callout : errorInfo->iv_procedureCallouts) {
		ProcedureCallout procedurecallout_data;
		procedurecallout_data.proc_callout =
		    fapi2::plat_ProcedureCallout_tostring(
			proc_callout->iv_procedure);
		procedurecallout_data.callout_priority =
		    fapi2::plat_CalloutPriority_tostring(
			proc_callout->iv_calloutPriority);

		hwp_errinfo.procedures_callout.push_back(procedurecallout_data);
	}

	// Get all available CDG (Callout,Deconfigure and Gard) record details
	// which are present in error xml for particular error
	for (auto cdg : errorInfo->iv_CDGs) {
		CDG_Target cdg_tgt_data;
		fapi2::getTgtEntityPath(cdg->iv_target,
					cdg_tgt_data.target_entity_path);
		cdg_tgt_data.callout = cdg->iv_callout;
		cdg_tgt_data.callout_priority =
		    fapi2::plat_CalloutPriority_tostring(
			cdg->iv_calloutPriority);
		cdg_tgt_data.deconfigure = cdg->iv_deconfigure;
		cdg_tgt_data.guard = cdg->iv_gard;
		cdg_tgt_data.guard_type =
		    fapi2::plat_GardTypeEnum_tostring(cdg->iv_gardType);

		hwp_errinfo.cdg_targets.push_back(cdg_tgt_data);
	}
}

/*
 * @brief Helper function to get hwp ffdc information .
 *
 * @param ffdc used to pass buffer to fill FFDC data
 * @param rc fapirc object
 *
 * @return void
 */
void libekb_get_ffdc_helper(FFDC& ffdc, fapi2::ReturnCode& rc)
{
	if (rc == fapi2::FAPI2_RC_SUCCESS) {
		ffdc.ffdc_type = FFDC_TYPE_NONE;
		ffdc.message =
		    "No FFDC, libekb_get_ffdc() called for success case";
		return;
	}

	if (rc.getCreator() == fapi2::ReturnCode::CREATOR_HWP) {
		ffdc.ffdc_type = FFDC_TYPE_HWP;
		get_HWPErrorInfo(rc, ffdc.hwp_errorinfo);
		ffdc.message = "Collected HWP FFDC";
	} else if (rc.getCreator() == fapi2::ReturnCode::CREATOR_FAPI) {
		ffdc.ffdc_type = FFDC_TYPE_UNSUPPORTED;
		ffdc.message =
		    "Un-Supported type to collect FFDC. Error created by FAPI";
	} else if (rc.getCreator() == fapi2::ReturnCode::CREATOR_PLAT) {
		ffdc.ffdc_type = FFDC_TYPE_UNSUPPORTED;
		ffdc.message =
		    "Un-Supported type to collect FFDC. Error created by PLAT";
	} else {
		ffdc.ffdc_type = FFDC_TYPE_NONE;
		ffdc.message =
		    "Unknown error creator. Failed to collect ffdc for error";
	}
}

void libekb_get_ffdc(FFDC& ffdc)
{
	// Previous application called HWP return code
	fapi2::ReturnCode rc = fapi2::current_err;
	libekb_get_ffdc_helper(ffdc, rc);
	// For clock hwp error happened inside BMC context, the proc
	// target has to be deconfigured
	fapi2::process_HW_callout(ffdc, true);
}

void libekb_get_sbe_ffdc(FFDC& ffdc, const sbeFfdcPacketType& ffdc_pkt,
			 int proc_index)
{
	using namespace fapi2;
	fapi2::ReturnCode rc;

	libekb_log(LIBEKB_LOG_INF,
		   "proc index: %d \t fapirc: 0x%x length: %d\n", proc_index,
		   ffdc_pkt.fapiRc, ffdc_pkt.ffdcLengthInWords);

	if (!ffdc_pkt.ffdcLengthInWords) {
		libekb_log(LIBEKB_LOG_ERR, "Empty sbe ffdc packet, Skipping\n");
		ffdc.ffdc_type = FFDC_TYPE_NONE;
		ffdc.message =
		    "Empty sbe ffdc packet. Failed to collect ffdc for error";
		return;
	}

	// First Word is the RC itself, skip that and point to FFDC blob
	sbeFfdc_t* sbe_ffdc =
	    reinterpret_cast<sbeFfdc_t*>(ffdc_pkt.ffdcData + 1);

	// Get size of FFDC data in bytes. exculde RC size.
	size_t size = (ffdc_pkt.ffdcLengthInWords - 1) * sizeof(uint32_t);

	// Create temporary sbeFfdc_t to store the data after endianess
	// conversion.
	std::vector<sbeFfdc_t> ffdc_endian;

	// get size of sbeFfdc_t structre
	size_t sbe_ffdc_size = sizeof(sbeFfdc_t);

	// endianess conversion.
	for (size_t i = 0; i < size; i += sbe_ffdc_size, sbe_ffdc++) {
		sbeFfdc_t ffdc_data;
		ffdc_data.size = ntohl(sbe_ffdc->size);
		// Special type FFDC size need endianess conversion in data.
		// TODO: Endianess for size "1, 2, 4" need to revisit.
		if ((ffdc_data.size == EI_FFDC_SIZE_TARGET) ||
		    (ffdc_data.size == EI_FFDC_SIZE_BUF) ||
		    (ffdc_data.size == EI_FFDC_SIZE_VBUF) ||
		    (ffdc_data.size == EI_FFDC_MAX_SIZE)) {

			ffdc_data.data = be64toh(sbe_ffdc->data);
		} else {
			ffdc_data.data = sbe_ffdc->data;
		}
		ffdc_endian.push_back(ffdc_data);
	}

	// Convert SBE Error FFDC to FAPI RC
	FAPI_SET_SBE_ERROR(rc, ffdc_pkt.fapiRc, ffdc_endian.data(), proc_index);
	libekb_log(LIBEKB_LOG_INF, " New fapirc: 0x%x\n", rc);

	// update ffdc structre based on new RC
	libekb_get_ffdc_helper(ffdc, rc);
	// For clock hwp error happened inside SBE context, the proc
	// target should not to be deconfigured
	fapi2::process_HW_callout(ffdc, false);
}

bool libekb_switch_pdbg_backend(const std::string& backendString)
{
	libekb_log(LIBEKB_LOG_INF,
		   "Swarnendu-Debug-Msg: Entering libekb_switch_pdbg_backend");
	if (backendString.empty()) {
		libekb_log(LIBEKB_LOG_ERR,
			   "Backend type is not provided for switching");
		return false;
	}
	libekb_log(LIBEKB_LOG_INF,
		   "Swarnendu-Debug-Msg: Switching backend to %s",
		   backendString.c_str());

	enum pdbg_backend backend;
	if (("SBEFIFO" == backendString) || ("sbefifo" == backendString))
		backend = pdbg_backend::PDBG_BACKEND_SBEFIFO;
	else if (("KERNEL" == backendString) || ("kernel" == backendString))
		backend = pdbg_backend::PDBG_BACKEND_KERNEL;
	else if (("FSI" == backendString) || ("fsi" == backendString))
		backend = pdbg_backend::PDBG_BACKEND_FSI;
	else if (("I2C" == backendString) || ("i2c" == backendString))
		backend = pdbg_backend::PDBG_BACKEND_I2C;
	else
		backend = pdbg_backend::PDBG_DEFAULT_BACKEND;

	// First clear the existing dev tree
	if (pdbg_target_root()) {
		pdbg_release_dt_root();
		/* libekb_log(LIBEKB_LOG_INF, "Swarnendu-Debug-Msg: Printing
		targets for each target class after releasing device tree");
		print_targets_for_each_target_class(); */
	}

	if (!pdbg_set_backend(backend, nullptr)) {
		libekb_log(LIBEKB_LOG_ERR, "Can not set the backend to %s",
			   backendString.c_str());
		return false;
	}

	constexpr auto devtree =
	    "/var/lib/phosphor-software-manager/pnor/rw/DEVTREE";
	// PDBG_DTB environment variable set to CEC device tree path
	if (setenv("PDBG_DTB", devtree, 1)) {
		libekb_log(LIBEKB_LOG_ERR,
			   "Failed to set PDBG_DTB. ErrNo: ", strerror(errno));
		return false;
	}

	constexpr auto PDATA_INFODB_PATH =
	    "/usr/share/pdata/attributes_info.db";
	// PDATA_INFODB environment variable set to attributes tool  infodb path
	if (setenv("PDATA_INFODB", PDATA_INFODB_PATH, 1)) {
		libekb_log(
		    LIBEKB_LOG_ERR,
		    "Failed to set PDATA_INFODB: ErrNo: ", strerror(errno));
		return false;
	}

	// initialize the targeting system
	if (!pdbg_targets_init(nullptr)) {
		libekb_log(LIBEKB_LOG_ERR, "pdbg_targets_init failed for %s",
			   backendString.c_str());
		return false;
	}
	auto root = pdbg_target_root();
	if (!root) {
		libekb_log(LIBEKB_LOG_ERR,
			   "Root target can not be aquired after switching "
			   "backend to %s",
			   backendString.c_str());
		return false;
	}
	pdbg_target_probe_all(root);
	return true;
}
struct pdbg_target* getProcFromFailingId(const uint32_t failingUnit)
{
	struct pdbg_target* proc = nullptr;
	pdbg_for_each_class_target("proc", proc)
	{
		if (pdbg_target_index(proc) == failingUnit)
			break;
	}
	if (!proc)
		libekb_log(LIBEKB_LOG_ERR,
			   "No proc target found for failing unit = %d",
			   failingUnit);

	return proc;
}

bool probe_pib_n_fsi_targets(struct pdbg_target* proc)
{
	// PIB target for executing HWP
	char path[16];
	// Probe PIB for HWP execution
	sprintf(path, "/proc%d/pib", pdbg_target_index(proc));
	auto pib = pdbg_target_from_path(nullptr, path);
	if (!pib) {
		libekb_log(LIBEKB_LOG_ERR, "Failed to get PIB target for: ",
			   pdbg_target_path(proc));
		return false;
	}
	if (pdbg_target_probe(pib) != PDBG_TARGET_ENABLED) {
		libekb_log(LIBEKB_LOG_ERR, "Failed to probe PIB target");
		return false;
	}

	// Probe FSI for HWP execution
	sprintf(path, "/proc%d/fsi", pdbg_target_index(proc));
	auto fsi = pdbg_target_from_path(nullptr, path);
	if (!fsi) {
		libekb_log(LIBEKB_LOG_ERR, "Failed to get FIS target for: ",
			   pdbg_target_path(proc));
		return false;
	}
	if (pdbg_target_probe(fsi) != PDBG_TARGET_ENABLED) {
		libekb_log(LIBEKB_LOG_ERR, "Failed to probe FSI target");
		return false;
	}
	return true;
}

bool libekb_get_sbe_ffdc_via_switch_backend(const uint32_t failingUnitId,
					    FFDC& ffdc,
					    struct pdbg_target*& proc)
{
	const std::string prevBackend = "SBEFIFO";
	const std::string newBackend = "KERNEL";

	libekb_log(LIBEKB_LOG_INF, "Swarnendu-Debug-Msg: Entering "
				   "libekb_get_sbe_ffdc_via_switch_backend");
	/**
	 * First switch the backend from SBEFIFO to KERNEL as if we are here
	 * it means that the SEEPROM is in dead state and using the current
	 * backend which is SBEFIFO by default won't yield anything for us
	 */
	if (!libekb_switch_pdbg_backend(newBackend)) {
		libekb_log(LIBEKB_LOG_ERR,
			   "Switching of PDBG backend to %s failed",
			   newBackend.c_str());
		// Try to revert the backend to SBEFIFO before returning.
		auto revert = libekb_switch_pdbg_backend(prevBackend);
		if (!revert) {
			libekb_log(LIBEKB_LOG_ERR,
				   "Reverting of PDBG backend to %s failed",
				   prevBackend.c_str());
			return revert;
		} else {
			proc = getProcFromFailingId(failingUnitId);
			if (!proc) {
				libekb_log(
				    LIBEKB_LOG_ERR,
				    "Can not aquire primary proc target after "
				    "switching back the backned to %s",
				    prevBackend.c_str());
				return false;
			}
		}
		return probe_pib_n_fsi_targets(proc);
	}
	// Find the proc target from the failing unit id
	proc = getProcFromFailingId(failingUnitId);
	if (!proc) {
		// Try to revert the backend to SBEFIFO before returning.
		auto revert = libekb_switch_pdbg_backend(prevBackend);
		if (!revert) {
			libekb_log(LIBEKB_LOG_ERR,
				   "Reverting of PDBG backend to %s failed",
				   prevBackend.c_str());
			return revert;
		} else {
			proc = getProcFromFailingId(failingUnitId);
			if (!proc) {
				libekb_log(LIBEKB_LOG_ERR,
					   "Can not aquire primary proc after "
					   "switching back the backned to %s",
					   prevBackend.c_str());
				return false;
			}
		}
		return probe_pib_n_fsi_targets(proc);
	}

	// Execute SBE extract rc to get the reason code for SEEPROM/SBE boot
	// failure
	P10_EXTRACT_SBE_RC::RETURN_ACTION recovAction;
	// p10_extract_sbe_rc is returning the error along with
	// recovery action, so not checking the fapirc.
	auto fapiRc = p10_extract_sbe_rc(proc, recovAction, true);

	switch (recovAction) {
	case P10_EXTRACT_SBE_RC::RETURN_ACTION::ERROR_RECOVERED: {
		libekb_log(
		    LIBEKB_LOG_INF,
		    "P10_EXTRACT_SBE_RC::RETURN_ACTION = ERROR_RECOVERED");
		break;
	}
	case P10_EXTRACT_SBE_RC::RETURN_ACTION::NO_RECOVERY_ACTION: {
		libekb_log(
		    LIBEKB_LOG_INF,
		    "P10_EXTRACT_SBE_RC::RETURN_ACTION = NO_RECOVERY_ACTION");
		break;
	}
	case P10_EXTRACT_SBE_RC::RETURN_ACTION::RECONFIG_WITH_CLOCK_GARD: {
		libekb_log(LIBEKB_LOG_INF, "P10_EXTRACT_SBE_RC::RETURN_ACTION "
					   "= RECONFIG_WITH_CLOCK_GARD");
		break;
	}
	case P10_EXTRACT_SBE_RC::RETURN_ACTION::REIPL_BKP_BMSEEPROM: {
		libekb_log(
		    LIBEKB_LOG_INF,
		    "P10_EXTRACT_SBE_RC::RETURN_ACTION = REIPL_BKP_BMSEEPROM");
		break;
	}
	case P10_EXTRACT_SBE_RC::RETURN_ACTION::REIPL_BKP_MSEEPROM: {
		libekb_log(
		    LIBEKB_LOG_INF,
		    "P10_EXTRACT_SBE_RC::RETURN_ACTION = REIPL_BKP_MSEEPROM");
		break;
	}
	case P10_EXTRACT_SBE_RC::RETURN_ACTION::REIPL_UPD_MSEEPROM: {
		libekb_log(
		    LIBEKB_LOG_INF,
		    "P10_EXTRACT_SBE_RC::RETURN_ACTION = REIPL_UPD_MSEEPROM");
		break;
	}
	case P10_EXTRACT_SBE_RC::RETURN_ACTION::REIPL_UPD_SEEPROM: {
		libekb_log(
		    LIBEKB_LOG_INF,
		    "P10_EXTRACT_SBE_RC::RETURN_ACTION = REIPL_UPD_SEEPROM");
		break;
	}
	case P10_EXTRACT_SBE_RC::RETURN_ACTION::REIPL_UPD_SPI_CLK_DIV: {
		libekb_log(LIBEKB_LOG_INF, "P10_EXTRACT_SBE_RC::RETURN_ACTION "
					   "= REIPL_UPD_SPI_CLK_DIV");
		break;
	}
	case P10_EXTRACT_SBE_RC::RETURN_ACTION::RESTART_CBS: {
		libekb_log(LIBEKB_LOG_INF,
			   "P10_EXTRACT_SBE_RC::RETURN_ACTION = RESTART_CBS");
		break;
	}
	case P10_EXTRACT_SBE_RC::RETURN_ACTION::RESTART_SBE: {
		libekb_log(LIBEKB_LOG_INF,
			   "P10_EXTRACT_SBE_RC::RETURN_ACTION = RESTART_SBE");
		break;
	}
	default: {
		libekb_log(
		    LIBEKB_LOG_INF,
		    "P10_EXTRACT_SBE_RC::RETURN_ACTION = UNKNOWN_REASON_CODE");
		break;
	}
	}
	/**
	 * Now switch the backend back to SBEFIFO from KERNEL i.e.; to it's
	 * original state before returning
	 */
	if (!libekb_switch_pdbg_backend(prevBackend)) {
		libekb_log(LIBEKB_LOG_ERR,
			   "Switching of PDBG backend back to %s failed",
			   prevBackend.c_str());
		return false;
	} else {
		libekb_log(LIBEKB_LOG_INF,
			   "Switching of PDBG backend back to %s successful",
			   prevBackend.c_str());
		proc = getProcFromFailingId(failingUnitId);
		if (!proc) {
			libekb_log(LIBEKB_LOG_ERR,
				   "Failed to get proc for failing unit ID %d "
				   "after switching back to %s",
				   failingUnitId, prevBackend.c_str());
			return false;
		}
	}
	return probe_pib_n_fsi_targets(proc);
}

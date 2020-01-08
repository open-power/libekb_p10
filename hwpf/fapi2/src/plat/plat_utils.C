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

#include <target.H>
#include <stdint.h>
#include <plat_trace.H>
#include <return_code.H>
#include <error_info.H>
#include <utils.H>
#include <assert.h>

extern "C" {
#include <fdt/fdt_prop.h>
#include <attribute/attribute_format.h>
}

namespace fapi2
{
///
/// @brief Log an error.
///
void logError(
    fapi2::ReturnCode& io_rc,
    fapi2::errlSeverity_t i_sev,
    bool i_unitTestError)
{
}

// will do the same as log error here in fapi2 plat implementation
void createPlatLog(
    fapi2::ReturnCode& io_rc,
    fapi2::errlSeverity_t i_sev)
{
    FAPI_DBG("Called createError()" );
    logError(io_rc, i_sev, false);
}

///
/// @brief Associate an error to PRD PLID.
///
void log_related_error(
    const Target<TARGET_TYPE_ALL>& i_target,
    fapi2::ReturnCode& io_rc,
    const fapi2::errlSeverity_t i_sev,
    const bool i_unitTestError )
{
    FAPI_DBG("Called log_related_error()" );
    // Just commit the log in default implementation
    logError( io_rc, i_sev, i_unitTestError );
} // end log_related_error

///
/// @brief Delay this thread.
///
ReturnCode delay(uint64_t i_nanoSeconds, uint64_t i_simCycles, bool i_fixed)
{
    // void statements to keep the compiler from complaining
    // about unused variables.
    static_cast<void>(i_nanoSeconds);
    static_cast<void>(i_simCycles);
    static_cast<void>(i_fixed);

    // replace with platform specific implementation
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

static void *fdt;

ReturnCode plat_access_attr_SETMACRO(const char *attr, struct pdbg_target *tgt, void *val, size_t size)
{
	struct attr attrib;
	uint8_t *value;
	char *path;
	int len, ret;

	/* NULL targets use pdbg_dt_root */
	if (!tgt) {
	 	/* TODO: This should never happen but we've only got a partial
	 	 * implementation of targetting so far */
	 	printf("NULL target reading attribute not implemented reading %s. Using pdbg_dt_root for the moment.\n", attr);
		tgt = pdbg_target_root();
	}

	path = pdbg_target_path(tgt);
	assert(path);

	/* Maximum header size is 4 words */
	len = size + 16;
	value = (uint8_t *)malloc(len);
	assert(value);

	ret = fdt_prop_read(fdt, path, attr, value, &len);
	if (ret != 0) {
		if (ret == 1)
			printf("Target %s not found\n", path);
		else if (ret == 2)
			printf("Attribute '%s' not found for target '%s'\n", attr, path);

		free(path);
		free(value);
		return FAPI2_RC_FALSE;
	}

	attr_decode(&attrib, value, len);
	free(value);
	if ((unsigned int)attrib.size != size) {
		printf("Wrong size (%zu, expected %d) for attribute '%s'\n", size, attrib.size, attr);
		free(path);
		free(attrib.value);
		return FAPI2_RC_FALSE;
	}

	free(attrib.value);
	attrib.value = (uint8_t *)val;

	attr_encode(&attrib, &value, &len);

	ret = fdt_prop_write(fdt, path, attr, value, len);
	if (ret != 0) {
		if (ret == 1)
			printf("Target %s not found\n", path);
		else if (ret == 2)
			printf("Attribute '%s' not found for target '%s'\n", attr, path);

		free(path);
		return FAPI2_RC_FALSE;
	}

	free(path);
	return FAPI2_RC_SUCCESS;
}

ReturnCode plat_access_attr_GETMACRO(const char *attr, struct pdbg_target *tgt, void *val, size_t size)
{
	struct attr attrib;
	uint8_t *value;
	char *path;
	int len, ret;

	/* NULL targets use pdbg_dt_root */
	if (!tgt) {
	 	/* TODO: This should never happen but we've only got a partial
	 	 * implementation of targetting so far */
	 	printf("NULL target reading attribute %s. Using pdbg_dt_root for the moment.\n", attr);
		tgt = pdbg_target_root();
	}

	if (!fdt) {
		printf("FDT not initialized\n");
		return FAPI2_RC_FALSE;
	}

	path = pdbg_target_path(tgt);
	assert(path);

	/* Maximum header size is 4 words */
	len = size + 16;
	value = (uint8_t *)malloc(len);
	assert(value);

	ret = fdt_prop_read(fdt, path, attr, value, &len);
	if (ret != 0) {
		if (ret == 1)
			printf("Target %s not found\n", path);
		else if (ret == 2)
			printf("Attribute '%s' not found for target '%s'\n", attr, path);

		free(path);
		free(value);
		return FAPI2_RC_FALSE;
	}

	free(path);

	attr_decode(&attrib, value, len);
	free(value);
	if ((unsigned int)attrib.size != size) {
		printf("Wrong size (%zu, expected %d) for attribute '%s'\n", size, attrib.size, attr);
		free(attrib.value);
		return FAPI2_RC_FALSE;
	}

	memcpy(val, attrib.value, size);
	free(attrib.value);

	return FAPI2_RC_SUCCESS;
}

}

void plat_set_fdt(void *fdt)
{
	fapi2::fdt = fdt;
}

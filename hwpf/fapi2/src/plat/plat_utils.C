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
#include <time.h>
#include <errno.h>

extern "C" {
#include <attribute/attribute_api.h>
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

ReturnCode plat_access_attr_SETMACRO(const char *attr, struct pdbg_target *tgt, void *val, size_t size)
{
	const char *path;
	int ret;

	/* NULL targets use pdbg_dt_root */
	if (!tgt) {
	 	/* TODO: This should never happen but we've only got a partial
	 	 * implementation of targetting so far */
	 	printf("NULL target reading attribute not implemented reading %s. Using pdbg_dt_root for the moment.\n", attr);
		tgt = pdbg_target_root();
	}

	path = pdbg_target_path(tgt);
	assert(path);

	ret = attr_write(tgt, attr, val, size);
	if (ret != 0) {
		if (ret == ENOENT)
			printf("Attribute '%s' not found for target '%s'\n", attr, path);
		else if (ret == EMSGSIZE)
			printf("Wrong size %zu for attribute '%s'\n", size, attr);
		else if (ret == EIO)
			printf("Failed to store attribute '%s'\n", attr);

		return FAPI2_RC_FALSE;
	}

	return FAPI2_RC_SUCCESS;
}

ReturnCode plat_access_attr_GETMACRO(const char *attr, struct pdbg_target *tgt, void *val, size_t size)
{
	const char *path;
	int ret;

	/* NULL targets use pdbg_dt_root */
	if (!tgt) {
	 	/* TODO: This should never happen but we've only got a partial
	 	 * implementation of targetting so far */
	 	printf("NULL target reading attribute %s. Using pdbg_dt_root for the moment.\n", attr);
		tgt = pdbg_target_root();
	}

	path = pdbg_target_path(tgt);
	assert(path);

	ret = attr_read(tgt, attr, val, size);
	if (ret != 0) {
		if (ret == ENOENT)
			printf("Attribute '%s' not found for target '%s'\n", attr, path);
		else if (ret == EMSGSIZE)
			printf("Wrong size %zu for attribute '%s'\n", size, attr);

		return FAPI2_RC_FALSE;
	}

	return FAPI2_RC_SUCCESS;
}

}

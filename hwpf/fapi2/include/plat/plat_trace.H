/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: hwpf/fapi2/include/plat/plat_trace.H $                        */
/*                                                                        */
/* IBM CONFIDENTIAL                                                       */
/*                                                                        */
/* EKB Project                                                            */
/*                                                                        */
/* COPYRIGHT 2011,2015                                                    */
/* [+] International Business Machines Corp.                              */
/*                                                                        */
/*                                                                        */
/* The source code for this program is not published or otherwise         */
/* divested of its trade secrets, irrespective of what has been           */
/* deposited with the U.S. Copyright Office.                              */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/**
 *  @file plat_trace.H
 *  @brief Defines the FAPI2 trace macros.
 *
 *  Note that platform code must provide the implementation.
 *
 *  FAPI has provided a default implementation. Platform code must
 *  provide an alternate implementation if needed.
 */

#ifndef FAPI2_PLATTRACE_H_
#define FAPI2_PLATTRACE_H_

#include <stdio.h>
#include <stdint.h>
#include <libekb.H>

// Why not a #define, why is this in the fapi2 namespace?
// To prevent problems with Cronus and the fapi1 definitions.
namespace fapi2
{
static const uint32_t MAX_ECMD_STRING_LEN = 64;
};

// Trace location format, LOG_LEVEL: FUNCTION_NAME:LINE_NO
#define TRACE_LOC_FORMAT_SPEC "%s: %s:%d "

// Making both trace location and caller trace format specifier as
// single argument to pass into libekb_log
#define TRACE_FORMAT_SPEC(LOC, _fmt_) LOC _fmt_ "\n"

// Information traces (go into fast trace buffer that can wrap often)
#define FAPI_TRACE(_level_, _id_, _fmt_, _args_...)                              \
    libekb_log(_level_, TRACE_FORMAT_SPEC(TRACE_LOC_FORMAT_SPEC, _fmt_),         \
               _id_, __func__, __LINE__, ##_args_);

#define FAPI_INF(_fmt_, _args_...) FAPI_TRACE(LIBEKB_LOG_INF, "inf", _fmt_, ##_args_)

// Important traces (go into slow trace buffer that should not wrap often)
#define FAPI_IMP(_fmt_, _args_...) FAPI_TRACE(LIBEKB_LOG_IMP, "imp", _fmt_, ##_args_)

// Error traces (go into slow trace buffer that should not wrap often)
#define FAPI_ERR(_fmt_, _args_...) FAPI_TRACE(LIBEKB_LOG_ERR, "err", _fmt_, ##_args_)

// Debug traces (go into fast trace buffer that can wrap often)
#define FAPI_DBG(_fmt_, _args_...) FAPI_TRACE(LIBEKB_LOG_DBG, "dbg", _fmt_, ##_args_)

// Scan traces
#define FAPI_SCAN(_fmt_, _args_...) FAPI_TRACE(LIBEKB_LOG_SCAN, "scan", _fmt_, ##_args_)

#define FAPI_MFG(_fmt_, _args_...) FAPI_TRACE(LIBEKB_LOG_MFG, "mfg", _fmt_, ##_args_)

#define FAPI_LAB(__fmt_, _args_...) \
    printf(_fmt_, ##_args_);    \
    printf("\n")
#endif // FAPI2_PLATTRACE_H_

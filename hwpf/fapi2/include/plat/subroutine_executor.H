/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: hwpf/fapi2/include/plat/subroutine_executor.H $               */
/*                                                                        */
/* IBM CONFIDENTIAL                                                       */
/*                                                                        */
/* EKB Project                                                            */
/*                                                                        */
/* COPYRIGHT 2016,2017                                                    */
/* [+] International Business Machines Corp.                              */
/*                                                                        */
/*                                                                        */
/* The source code for this program is not published or otherwise         */
/* divested of its trade secrets, irrespective of what has been           */
/* deposited with the U.S. Copyright Office.                              */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
///
/// @file subroutine_executor.H
///
/// @brief Defines the PLAT Subroutine Executor Macro.
///
/// The PLAT Subroutine Executor macro is called by
/// FAPI_CALL_SUBROUTINE when a hardware procedure when
/// a subroutine is needed, typicaly a chipop function.
///
/// Example implementation of plat code

#ifndef SUBROUTINEEXECUTOR_H_
#define SUBROUTINEEXECUTOR_H_

#include <fapi2_subroutine_executor.H>
#include <plat_trace.H>

/**
 * @brief Subroutine Executor macro example code - Platforms will need to
 *        implement as needed for their enviroment.
 *
 * This macro calls a PLAT macro which will do any platform specific work to
 * execute the Subroutine (e.g. dlopening a shared library)
 */
#define FAPI_PLAT_CALL_SUBROUTINE(RC, FUNC, _args...)                          \
    {                                                                          \
        FAPI_DBG("executing FAPI_PLAT_CALL_SUBROUTINE macro");                 \
        RC = FUNC(_args);                                                      \
    }

#endif

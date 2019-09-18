/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: hwpf/fapi2/include/plat/plat_utils.H $                        */
/*                                                                        */
/* IBM CONFIDENTIAL                                                       */
/*                                                                        */
/* EKB Project                                                            */
/*                                                                        */
/* COPYRIGHT 2016,2019                                                    */
/* [+] International Business Machines Corp.                              */
/*                                                                        */
/*                                                                        */
/* The source code for this program is not published or otherwise         */
/* divested of its trade secrets, irrespective of what has been           */
/* deposited with the U.S. Copyright Office.                              */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/**
 * @file plat_utils.H
 * @brief platform definitions for fapi2 targets
 */

#ifndef __FAPI2_PLAT_UTILS__
#define __FAPI2_PLAT_UTILS__

#include <stdint.h>

namespace fapi2
{

// Platforms are expected to define this
static const PlatformType PLATFORM = PLAT_EXAMPLE;

template<TargetType T>
inline ReturnCode platSpecialWakeup( const Target<T>& i_target, bool i_enable)
{
    static_cast<void>(i_enable);
    static_cast<void>(i_target);

    if(is_same<T, TARGET_TYPE_PROC_CHIP>() )
    {
        FAPI_INF("do proc special wakeup stuff");
    }
    else if(is_same<T, TARGET_TYPE_CORE>() )
    {
        FAPI_INF("do core special wakeup stuff");
    }
    else if(is_same<T, TARGET_TYPE_EX>() )
    {
        FAPI_INF("do ex speical wakeup stuff");
    }
    else if(is_same<T, TARGET_TYPE_EQ>() )
    {
        FAPI_INF("do eq special wakeup stuff");
    }
    else
    {
        FAPI_INF("should never get here");
    }

    return FAPI2_RC_SUCCESS;
}

}

#endif

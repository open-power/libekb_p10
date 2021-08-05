/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: hwpf/fapi2/include/plat/plat_mbvpd_access.H $                 */
/*                                                                        */
/* IBM CONFIDENTIAL                                                       */
/*                                                                        */
/* EKB Project                                                            */
/*                                                                        */
/* COPYRIGHT 2017                                                         */
/* [+] International Business Machines Corp.                              */
/*                                                                        */
/*                                                                        */
/* The source code for this program is not published or otherwise         */
/* divested of its trade secrets, irrespective of what has been           */
/* deposited with the U.S. Copyright Office.                              */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/// @file plat_mbvpd_access.H
///
/// @brief Platform Memory Buffer access definitions
///

#ifndef _FAPI2_PLAT_MBVPD_ACCESS_H_
#define _FAPI2_PLAT_MBVPD_ACCESS_H_

#include <fapi2_mbvpd_access.H>

namespace fapi2
{

inline fapi2::ReturnCode
    getMBvpdField(const fapi2::MBvpdRecord i_record,
                  const fapi2::MBvpdKeyword i_keyword,
                  const fapi2::Target<fapi2::TARGET_TYPE_MEMBUF_CHIP>& i_target,
                  uint8_t* const i_pBuffer, size_t& io_fieldSize)
{
    fapi2::ReturnCode l_rc = fapi2::FAPI2_RC_SUCCESS;

    return l_rc;
}

inline fapi2::ReturnCode
    setMBvpdField(const fapi2::MBvpdRecord i_record,
                  const fapi2::MBvpdKeyword i_keyword,
                  const fapi2::Target<fapi2::TARGET_TYPE_MEMBUF_CHIP>& i_target,
                  const uint8_t* const i_pBuffer, const size_t i_fieldSize)
{
    fapi2::ReturnCode l_rc = fapi2::FAPI2_RC_SUCCESS;

    return l_rc;
}

}; // namespace fapi2

#endif

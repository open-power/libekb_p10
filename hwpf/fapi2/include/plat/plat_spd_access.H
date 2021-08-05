/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: hwpf/fapi2/include/plat/plat_spd_access.H $                   */
/*                                                                        */
/* IBM CONFIDENTIAL                                                       */
/*                                                                        */
/* EKB Project                                                            */
/*                                                                        */
/* COPYRIGHT 2016                                                         */
/* [+] International Business Machines Corp.                              */
/*                                                                        */
/*                                                                        */
/* The source code for this program is not published or otherwise         */
/* divested of its trade secrets, irrespective of what has been           */
/* deposited with the U.S. Copyright Office.                              */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/// @file plat_spd_access.H
///
/// @brief Platform spd-access definitions
///

#ifndef _FAPI2_PLAT_SPD_ACCESS_H_
#define _FAPI2_PLAT_SPD_ACCESS_H_

namespace fapi2
{

fapi2::ReturnCode getSPD(const fapi2::Target<fapi2::TARGET_TYPE_DIMM>& i_target,
                         uint8_t* o_blob, size_t& s)
{
    fapi2::ReturnCode l_rc = fapi2::FAPI2_RC_SUCCESS;

    return l_rc;
}

}; // namespace fapi2

#endif

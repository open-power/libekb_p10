/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: hwpf/fapi2/include/plat/multicast.H $                         */
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
#ifndef __FAPI2_MULTICAST__
#define __FAPI2_MULTICAST__

#include <fapi2_multicast.H>

namespace fapi2
{

template<MulticastType M, MulticastGroup G, typename V>
template<MulticastType O, MulticastGroup N>
inline void Multicast<M, G, V>::updateHandle(V& value)
{
    // platform update handle here if needed
}

template<MulticastType M, MulticastGroup G, typename V>
inline bool Multicast<M, G, V>::isMulticast() const
{
    // platform update handle here if needed
    return false;
}

}

#endif

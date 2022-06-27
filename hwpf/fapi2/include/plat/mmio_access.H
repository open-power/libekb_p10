/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: hwpf/fapi2/include/plat/mmio_access.H $                       */
/*                                                                        */
/* IBM CONFIDENTIAL                                                       */
/*                                                                        */
/* EKB Project                                                            */
/*                                                                        */
/* COPYRIGHT 2018,2019                                                    */
/* [+] International Business Machines Corp.                              */
/*                                                                        */
/*                                                                        */
/* The source code for this program is not published or otherwise         */
/* divested of its trade secrets, irrespective of what has been           */
/* deposited with the U.S. Copyright Office.                              */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/// @file i2c_access.H
///
/// @brief I2C access functions that needs to be specialized for
/// platform implementation.
///
/// NOTE : This is just an example implementation for compiling against

#ifndef _FAPI2_MMIO_ACCESS_H_
#define _FAPI2_MMIO_ACCESS_H_

#include <fapi2_mmio_access.H>
#include <plat_mmio_access.H>

#include <iomanip>
#include <iostream>
#include <vector>

namespace fapi2
{

/// @brief Reads data via mmio from the target
template <TargetType K, MulticastType M, typename V>
inline ReturnCode getMMIO(const Target<K, M, V>& i_target,
			  const uint64_t i_mmioAddr, const size_t i_transSize,
			  std::vector<uint8_t>& o_data)
{

	// Platform suggestion:
	// - Verify o_data.size() is a multiple of i_transSize

	o_data.assign(o_data.size(), 0);

	for (size_t i = 0; i < o_data.size(); i++) {
		o_data[i] = i;
	}

	std::cout << std::hex << "   getMMIO "
		  << "target: {" << i_target.getType() << "," << i_target.get()
		  << "}; "
		  << "i_mmioAddr: " << i_mmioAddr << "; "
		  << "i_transSize: " << i_transSize << "; "
		  << "l_byteSize: " << o_data.size() << "; "
		  << "o_data: ";

	for (uint8_t l_byte = 0; l_byte < o_data.size(); l_byte++) {
		std::cout << std::setfill('0') << std::setw(2) << std::hex
			  << +o_data[l_byte];
	}

	std::cout << "; " << std::dec << std::endl;

	return FAPI2_RC_SUCCESS;
}

/// @brief Writes data via mmio to the target.
template <TargetType K, MulticastType M, typename V>
inline ReturnCode putMMIO(const Target<K, M, V>& i_target,
			  const uint64_t i_mmioAddr, const size_t i_transSize,
			  const std::vector<uint8_t>& i_data)
{

	// Platform suggestion:
	// - Verify o_data.size() is a multiple of i_transSize

	std::cout << std::hex << "   putMMIO "
		  << "target: {" << i_target.getType() << "," << i_target.get()
		  << "}; "
		  << "i_mmioAddr: " << i_mmioAddr << "; "
		  << "i_transSize: " << i_transSize << "; "
		  << "l_byteSize: " << i_data.size() << "; "
		  << "i_data: ";

	for (uint8_t l_byte = 0; l_byte < i_data.size(); l_byte++) {
		std::cout << std::setfill('0') << std::setw(2) << std::hex
			  << +i_data[l_byte];
	}

	std::cout << "; " << std::dec << std::endl;

	return FAPI2_RC_SUCCESS;
}

}; // namespace fapi2

#endif // _FAPI2_MMIO_ACCESS_H_

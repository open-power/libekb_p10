/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: hwpf/fapi2/include/plat/i2c_access.H $                        */
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

#ifndef _FAPI2_I2C_ACCESS_H_
#define _FAPI2_I2C_ACCESS_H_

#include <fapi2_i2c_access.H>
#include <plat_i2c_access.H>

#include <iomanip>
#include <iostream>

namespace fapi2
{
///
/// @brief Platform-level implementation of getI2c()
///
/// Example use (seeprom read 8 bytes w/ 2-byte address: 0x01B0):
/// std::vector<uint8_t> addr = {0x01, 0xB0};
/// std::vector<uint8_t> data;
/// size_t len = 8;
/// FAPI_TRY(getI2c(target, len, addr, data));
/// data should contain the 8 bytes starting at address 0x01B0
///
/// Example use (smbus read 5 bytes w/ 1-byte command: 0x02):
/// std::vector<uint8_t> command = {0x02};
/// std::vector<uint8_t> data;
/// size_t len = 5;
/// FAPI_TRY(getI2c(target, len, command, data));
/// data should contain 5 bytes, first byte with the data length(4)
/// remaining four bytes will be the data requested from the command
///
/// @tparam K the type (Kind) of target, from i_target
/// @tparam V the type of the target's Value, from i_target
/// @param[in]  i_target     HW target to operate on.
/// @param[in]  i_get_size   Size that getI2c will read from the HW target.
/// @param[in]  i_data       Buffer that holds data to write to the HW target.
///                          May be empty if no address/command is required
///                          before the read.
/// @param[out] o_data       Buffer that holds data read from HW target.
/// @return fapi2::ReturnCode. FAPI2_RC_SUCCESS if success, else error code.
///
template <TargetType K, MulticastType M, typename V>
inline ReturnCode
    getI2c(const Target<K, M, V>& i_target, const size_t i_get_size,
	   const std::vector<uint8_t>& i_data, std::vector<uint8_t>& o_data)
{
	uint8_t l_size = static_cast<uint8_t>(i_get_size) - 1;

	o_data.clear();
	o_data.push_back(l_size);

	for (uint8_t i = 0; i < l_size; i++) {
		o_data.push_back(i);
	}

	std::cout << std::hex << "   getI2c "
		  << "target: {" << i_target.getType() << "," << i_target.get()
		  << "}; "
		  << "i_get_size: " << i_get_size << "; "
		  << "i_data: ";

	const uint32_t l_mask = 0xff;

	for (const auto l_byte : i_data) {
		std::cout << std::hex << std::setw(2) << std::setfill('0')
			  << (l_mask & l_byte);
	}

	std::cout << "; " << std::dec << std::endl;

	return FAPI2_RC_SUCCESS;
}

///
/// @brief Platform-level implementation of putI2c()
///
/// Example use (seeprom write 4 bytes of zeros w/ 2-byte address: 0x0208):
/// std::vector<uint8_t> addr_data = {0x02, 0x08, 0x00, 0x00, 0x00, 0x00};
/// FAPI_TRY(putI2c(target, addr_data));
///
/// Example use (smbus write 1 data length byte + 4 bytes of zeros w/ 1-byte
/// command: 0x01): std::vector<uint8_t> command_data = {0x01, 0x04, 0x00, 0x00,
/// 0x00, 0x00}; FAPI_TRY(putI2c(target, command_data));
///
/// @tparam K the type (Kind) of target, from i_target
/// @tparam V the type of the target's Value, from i_target
/// @param[in] i_target     HW target to operate on.
/// @param[in] i_data       Buffer that holds data to write to the HW target.
/// @return fapi2::ReturnCode. FAPI2_RC_SUCCESS if success, else error code.
///
template <TargetType K, MulticastType M, typename V>
inline ReturnCode putI2c(const Target<K, M, V>& i_target,
			 const std::vector<uint8_t>& i_data)
{
	std::cout << std::hex << "   putI2c "
		  << "target: {" << i_target.getType() << "," << i_target.get()
		  << "}; "
		  << "i_data: ";

	const uint32_t l_mask = 0xff;

	for (const auto l_byte : i_data) {
		std::cout << std::hex << std::setw(2) << std::setfill('0')
			  << (l_mask & l_byte);
	}

	std::cout << "; " << std::dec << std::endl;

	return FAPI2_RC_SUCCESS;
}

}; // namespace fapi2

#endif // _FAPI2_I2C_ACCESS_H_

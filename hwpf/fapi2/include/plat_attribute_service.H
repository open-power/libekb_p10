// IBM_PROLOG_BEGIN_TAG
/*
 * Copyright 2017 IBM International Business Machines Corp.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * 	http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
// IBM_PROLOG_END_TAG

/**
 *  @file fapiPlatAttributeService.H
 *
 *  @brief Defines the PLAT attribute access macros and defines which macro
 *         handles each attribute.
 *
 *  Note that platform code must provide the code.
 */

/*
 * Change Log ******************************************************************
 * Flag     Defect/Feature  User        Date        Description
 * ------   --------------  ----------  ----------- ----------------------------
 *                          mjjones     06/27/2011  Created.
 */

#ifndef FAPI2PLATATTRIBUTESERVICE_H_
#define FAPI2PLATATTRIBUTESERVICE_H_

extern "C" {
#include <stdint.h>
}

#include <attribute_ids.H>
#include <return_code.H>
#include <target.H>
//#include <fapi2ClientCapi.H>
//#include <fapi2Structs.H>
//#include <fapi2SharedUtils.H>

//#include <ecmdReturnCodes.H>
//#include <ecmdStructs.H>

//#include <iostream>

/* Haven't figured out how to deal with attributes yet */

namespace fapi2
{
ReturnCode plat_access_attr_GETMACRO(const char* attr, struct pdbg_target* tgt,
				     uint32_t size, uint32_t count, void* val);
ReturnCode plat_access_attr_SETMACRO(const char* attr, struct pdbg_target* tgt,
				     uint32_t size, uint32_t count, void* val);
} // namespace fapi2

#include "platform_attrs.h"

#define PLAT_GET_CHIP_EC_FEATURE_OVERRIDE(ID, TARGET, VAL) FAPI2_RC_SUCCESS

/******************************************************************************/
/*                          * Global macros *                                 */
/* These macros are called by the macros above to invoke the appropriate API. */
/* These macros do not need to change when a new attribute is introduced.     */
/******************************************************************************/

/* global get uint8_t 1D array macro */
#define PLAT_ATTR_GET_UINT8_1D_ARRAY(ID, TARGET, VAL)                          \
	_getAttributeArrayShort(ID, TARGET, VAL)
/* global set uint8_t 1D array macro */
#define PLAT_ATTR_SET_UINT8_1D_ARRAY(ID, TARGET, VAL)                          \
	_setAttributeArrayShort(ID, TARGET, VAL)

/* global get uint8_t 2D array macro */
#define PLAT_ATTR_GET_UINT8_2D_ARRAY(ID, TARGET, VAL)                          \
	_getAttributeArrayShort(ID, TARGET, VAL[0])
/* global set uint8_t 2D array macro */
#define PLAT_ATTR_SET_UINT8_2D_ARRAY(ID, TARGET, VAL)                          \
	_setAttributeArrayShort(ID, TARGET, VAL[0])

/* global get uint8_t 3D array macro */
#define PLAT_ATTR_GET_UINT8_3D_ARRAY(ID, TARGET, VAL)                          \
	_getAttributeArrayShort(ID, TARGET, VAL[0][0])
/* global set uint8_t 3D array macro */
#define PLAT_ATTR_SET_UINT8_3D_ARRAY(ID, TARGET, VAL)                          \
	_setAttributeArrayShort(ID, TARGET, VAL[0][0])

/* global get uint8_t 4D array macro */
#define PLAT_ATTR_GET_UINT8_4D_ARRAY(ID, TARGET, VAL)                          \
	_getAttributeArrayShort(ID, TARGET, VAL[0][0][0])
/* global set uint8_t 4D array macro */
#define PLAT_ATTR_SET_UINT8_4D_ARRAY(ID, TARGET, VAL)                          \
	_setAttributeArrayShort(ID, TARGET, VAL[0][0][0])

/* global get uint16_t 1D array macro */
#define PLAT_ATTR_GET_UINT16_1D_ARRAY(ID, TARGET, VAL)                         \
	_getAttributeArrayHalfWord(ID, TARGET, VAL)
/* global set uint16_t 1D array macro */
#define PLAT_ATTR_SET_UINT16_1D_ARRAY(ID, TARGET, VAL)                         \
	_setAttributeArrayHalfWord(ID, TARGET, VAL)

/* global get uint16_t 2D array macro */
#define PLAT_ATTR_GET_UINT16_2D_ARRAY(ID, TARGET, VAL)                         \
	_getAttributeArrayHalfWord(ID, TARGET, VAL[0])
/* global set uint16_t 2D array macro */
#define PLAT_ATTR_SET_UINT16_2D_ARRAY(ID, TARGET, VAL)                         \
	_setAttributeArrayHalfWord(ID, TARGET, VAL[0])

/* global get uint16_t 3D array macro */
#define PLAT_ATTR_GET_UINT16_3D_ARRAY(ID, TARGET, VAL)                         \
	_getAttributeArrayHalfWord(ID, TARGET, VAL[0][0])
/* global set uint16_t 3D array macro */
#define PLAT_ATTR_SET_UINT16_3D_ARRAY(ID, TARGET, VAL)                         \
	_setAttributeArrayHalfWord(ID, TARGET, VAL[0][0])

/* global get uint16_t 4D array macro */
#define PLAT_ATTR_GET_UINT16_4D_ARRAY(ID, TARGET, VAL)                         \
	_getAttributeArrayHalfWord(ID, TARGET, VAL[0][0][0])
/* global set uint16_t 4D array macro */
#define PLAT_ATTR_SET_UINT16_4D_ARRAY(ID, TARGET, VAL)                         \
	_setAttributeArrayHalfWord(ID, TARGET, VAL[0][0][0])

/* global get uint32_t 1D array macro */
#define PLAT_ATTR_GET_UINT32_1D_ARRAY(ID, TARGET, VAL)                         \
	_getAttributeArrayWord(ID, TARGET, VAL)
/* global set uint32_t 1D array macro */
#define PLAT_ATTR_SET_UINT32_1D_ARRAY(ID, TARGET, VAL)                         \
	_setAttributeArrayWord(ID, TARGET, VAL)

/* global get uint32_t 2D array macro */
#define PLAT_ATTR_GET_UINT32_2D_ARRAY(ID, TARGET, VAL)                         \
	_getAttributeArrayWord(ID, TARGET, VAL[0])
/* global set uint32_t 2D array macro */
#define PLAT_ATTR_SET_UINT32_2D_ARRAY(ID, TARGET, VAL)                         \
	_setAttributeArrayWord(ID, TARGET, VAL[0])

/* global get uint32_t 3D array macro */
#define PLAT_ATTR_GET_UINT32_3D_ARRAY(ID, TARGET, VAL)                         \
	_getAttributeArrayWord(ID, TARGET, VAL[0][0])
/* global set uint32_t 3D array macro */
#define PLAT_ATTR_SET_UINT32_3D_ARRAY(ID, TARGET, VAL)                         \
	_setAttributeArrayWord(ID, TARGET, VAL[0][0])

/* global get uint32_t 4D array macro */
#define PLAT_ATTR_GET_UINT32_4D_ARRAY(ID, TARGET, VAL)                         \
	_getAttributeArrayWord(ID, TARGET, VAL[0][0][0])
/* global set uint32_t 4D array macro */
#define PLAT_ATTR_SET_UINT32_4D_ARRAY(ID, TARGET, VAL)                         \
	_setAttributeArrayWord(ID, TARGET, VAL[0][0][0])

/* global get uint64_t 1D array macro */
#define PLAT_ATTR_GET_UINT64_1D_ARRAY(ID, TARGET, VAL)                         \
	_getAttributeArrayDoubleWord(ID, TARGET, VAL)
/* global set uint64_t 1D array macro */
#define PLAT_ATTR_SET_UINT64_1D_ARRAY(ID, TARGET, VAL)                         \
	_setAttributeArrayDoubleWord(ID, TARGET, VAL)

/* global get uint64_t 2D array macro */
#define PLAT_ATTR_GET_UINT64_2D_ARRAY(ID, TARGET, VAL)                         \
	_getAttributeArrayDoubleWord(ID, TARGET, VAL[0])
/* global set uint64_t 2D array macro */
#define PLAT_ATTR_SET_UINT64_2D_ARRAY(ID, TARGET, VAL)                         \
	_setAttributeArrayDoubleWord(ID, TARGET, VAL[0])

/* global get uint64_t 3D array macro */
#define PLAT_ATTR_GET_UINT64_3D_ARRAY(ID, TARGET, VAL)                         \
	_getAttributeArrayDoubleWord(ID, TARGET, VAL[0][0])
/* global set uint64_t 3D array macro */
#define PLAT_ATTR_SET_UINT64_3D_ARRAY(ID, TARGET, VAL)                         \
	_setAttributeArrayDoubleWord(ID, TARGET, VAL[0][0])

/* global get uint64_t 4D array macro */
#define PLAT_ATTR_GET_UINT64_4D_ARRAY(ID, TARGET, VAL)                         \
	_getAttributeArrayDoubleWord(ID, TARGET, VAL[0][0][0])
/* global set uint64_t 4D array macro */
#define PLAT_ATTR_SET_UINT64_4D_ARRAY(ID, TARGET, VAL)                         \
	_setAttributeArrayDoubleWord(ID, TARGET, VAL[0][0][0])

/* global get int macro (uint8_t, 16, 32 and 64) */
#define PLAT_ATTR_GET_GLOBAL_INT(ID, TARGET, VAL)                              \
	_get<ID##_Type>(ID, TARGET, VAL)

/* global set int macro (uint8_t, 16, 32 and 64) */
#define PLAT_ATTR_SET_GLOBAL_INT(ID, TARGET, VAL)                              \
	_set<ID##_Type>(ID, TARGET, VAL)

/******************************************************************************/
// Get Override Macros
/******************************************************************************/
/* global get override uint8_t 1D array macro */
#define PLAT_ATTR_GET_OVERRIDE_UINT8_1D_ARRAY(ID, TARGET, VAL)                 \
	_getAttributeOverrideArrayShort(ID, TARGET, VAL)
/* global get override uint8_t 2D array macro */
#define PLAT_ATTR_GET_OVERRIDE_UINT8_2D_ARRAY(ID, TARGET, VAL)                 \
	_getAttributeOverrideArrayShort(ID, TARGET, VAL[0])
/* global get override uint8_t 3D array macro */
#define PLAT_ATTR_GET_OVERRIDE_UINT8_3D_ARRAY(ID, TARGET, VAL)                 \
	_getAttributeOverrideArrayShort(ID, TARGET, VAL[0][0])
/* global get override uint8_t 4D array macro */
#define PLAT_ATTR_GET_OVERRIDE_UINT8_4D_ARRAY(ID, TARGET, VAL)                 \
	_getAttributeOverrideArrayShort(ID, TARGET, VAL[0][0][0])

/* global get override uint16_t 1D array macro */
#define PLAT_ATTR_GET_OVERRIDE_UINT16_1D_ARRAY(ID, TARGET, VAL)                \
	_getAttributeOverrideArrayHalfWord(ID, TARGET, VAL)
/* global get override uint16_t 2D array macro */
#define PLAT_ATTR_GET_OVERRIDE_UINT16_2D_ARRAY(ID, TARGET, VAL)                \
	_getAttributeOverrideArrayHalfWord(ID, TARGET, VAL[0])
/* global get override uint16_t 3D array macro */
#define PLAT_ATTR_GET_OVERRIDE_UINT16_3D_ARRAY(ID, TARGET, VAL)                \
	_getAttributeOverrideArrayHalfWord(ID, TARGET, VAL[0][0])
/* global get override uint16_t 4D array macro */
#define PLAT_ATTR_GET_OVERRIDE_UINT16_4D_ARRAY(ID, TARGET, VAL)                \
	_getAttributeOverrideArrayHalfWord(ID, TARGET, VAL[0][0][0])

/* global get override uint32_t 1D array macro */
#define PLAT_ATTR_GET_OVERRIDE_UINT32_1D_ARRAY(ID, TARGET, VAL)                \
	_getAttributeOverrideArrayWord(ID, TARGET, VAL)
/* global get override uint32_t 2D array macro */
#define PLAT_ATTR_GET_OVERRIDE_UINT32_2D_ARRAY(ID, TARGET, VAL)                \
	_getAttributeOverrideArrayWord(ID, TARGET, VAL[0])
/* global get override uint32_t 3D array macro */
#define PLAT_ATTR_GET_OVERRIDE_UINT32_3D_ARRAY(ID, TARGET, VAL)                \
	_getAttributeOverrideArrayWord(ID, TARGET, VAL[0][0])
/* global get override uint32_t 4D array macro */
#define PLAT_ATTR_GET_OVERRIDE_UINT32_4D_ARRAY(ID, TARGET, VAL)                \
	_getAttributeOverrideArrayWord(ID, TARGET, VAL[0][0][0])

/* global get override uint64_t 1D array macro */
#define PLAT_ATTR_GET_OVERRIDE_UINT64_1D_ARRAY(ID, TARGET, VAL)                \
	_getAttributeOverrideArrayDoubleWord(ID, TARGET, VAL)
/* global get override uint64_t 2D array macro */
#define PLAT_ATTR_GET_OVERRIDE_UINT64_2D_ARRAY(ID, TARGET, VAL)                \
	_getAttributeOverrideArrayDoubleWord(ID, TARGET, VAL[0])
/* global get override uint64_t 3D array macro */
#define PLAT_ATTR_GET_OVERRIDE_UINT64_3D_ARRAY(ID, TARGET, VAL)                \
	_getAttributeOverrideArrayDoubleWord(ID, TARGET, VAL[0][0])
/* global get override uint64_t 4D array macro */
#define PLAT_ATTR_GET_OVERRIDE_UINT64_4D_ARRAY(ID, TARGET, VAL)                \
	_getAttributeOverrideArrayDoubleWord(ID, TARGET, VAL[0][0][0])

/* global get override int macro (uint8_t, 16, 32 and 64) */
#define PLAT_ATTR_GET_OVERRIDE_GLOBAL_INT(ID, TARGET, VAL)                     \
	_getOverride<ID##_Type>(ID, TARGET, VAL)

/* global get uint8_t 1D array macro */
#define PLAT_ATTR_GET_INT8_1D_ARRAY(ID, TARGET, VAL)                           \
	_getAttributeArraySignedShort(ID, TARGET, VAL)
/* global set uint8_t 1D array macro */
#define PLAT_ATTR_SET_INT8_1D_ARRAY(ID, TARGET, VAL)                           \
	_setAttributeArraySignedShort(ID, TARGET, VAL)

/* global get uint8_t 2D array macro */
#define PLAT_ATTR_GET_INT8_2D_ARRAY(ID, TARGET, VAL)                           \
	_getAttributeArraySignedShort(ID, TARGET, VAL[0])
/* global set uint8_t 2D array macro */
#define PLAT_ATTR_SET_INT8_2D_ARRAY(ID, TARGET, VAL)                           \
	_setAttributeArraySignedShort(ID, TARGET, VAL[0])

/* global get uint8_t 3D array macro */
#define PLAT_ATTR_GET_INT8_3D_ARRAY(ID, TARGET, VAL)                           \
	_getAttributeArraySignedShort(ID, TARGET, VAL[0][0])
/* global set uint8_t 3D array macro */
#define PLAT_ATTR_SET_INT8_3D_ARRAY(ID, TARGET, VAL)                           \
	_setAttributeArraySignedShort(ID, TARGET, VAL[0][0])

/* global get uint8_t 4D array macro */
#define PLAT_ATTR_GET_INT8_4D_ARRAY(ID, TARGET, VAL)                           \
	_getAttributeArraySignedShort(ID, TARGET, VAL[0][0][0])
/* global set uint8_t 4D array macro */
#define PLAT_ATTR_SET_INT8_4D_ARRAY(ID, TARGET, VAL)                           \
	_setAttributeArraySignedShort(ID, TARGET, VAL[0][0][0])

/* global get uint16_t 1D array macro */
#define PLAT_ATTR_GET_INT16_1D_ARRAY(ID, TARGET, VAL)                          \
	_getAttributeArraySignedHalfWord(ID, TARGET, VAL)
/* global set uint16_t 1D array macro */
#define PLAT_ATTR_SET_INT16_1D_ARRAY(ID, TARGET, VAL)                          \
	_setAttributeArraySignedHalfWord(ID, TARGET, VAL)

/* global get uint16_t 2D array macro */
#define PLAT_ATTR_GET_INT16_2D_ARRAY(ID, TARGET, VAL)                          \
	_getAttributeArraySignedHalfWord(ID, TARGET, VAL[0])
/* global set uint16_t 2D array macro */
#define PLAT_ATTR_SET_INT16_2D_ARRAY(ID, TARGET, VAL)                          \
	_setAttributeArraySignedHalfWord(ID, TARGET, VAL[0])

/* global get uint16_t 3D array macro */
#define PLAT_ATTR_GET_INT16_3D_ARRAY(ID, TARGET, VAL)                          \
	_getAttributeArraySignedHalfWord(ID, TARGET, VAL[0][0])
/* global set uint16_t 3D array macro */
#define PLAT_ATTR_SET_INT16_3D_ARRAY(ID, TARGET, VAL)                          \
	_setAttributeArraySignedHalfWord(ID, TARGET, VAL[0][0])

/* global get uint16_t 4D array macro */
#define PLAT_ATTR_GET_INT16_4D_ARRAY(ID, TARGET, VAL)                          \
	_getAttributeArraySignedHalfWord(ID, TARGET, VAL[0][0][0])
/* global set uint16_t 4D array macro */
#define PLAT_ATTR_SET_INT16_4D_ARRAY(ID, TARGET, VAL)                          \
	_setAttributeArraySignedHalfWord(ID, TARGET, VAL[0][0][0])

/* global get uint32_t 1D array macro */
#define PLAT_ATTR_GET_INT32_1D_ARRAY(ID, TARGET, VAL)                          \
	_getAttributeArraySignedWord(ID, TARGET, VAL)
/* global set uint32_t 1D array macro */
#define PLAT_ATTR_SET_INT32_1D_ARRAY(ID, TARGET, VAL)                          \
	_setAttributeArraySignedWord(ID, TARGET, VAL)

/* global get uint32_t 2D array macro */
#define PLAT_ATTR_GET_INT32_2D_ARRAY(ID, TARGET, VAL)                          \
	_getAttributeArraySignedWord(ID, TARGET, VAL[0])
/* global set uint32_t 2D array macro */
#define PLAT_ATTR_SET_INT32_2D_ARRAY(ID, TARGET, VAL)                          \
	_setAttributeArraySignedWord(ID, TARGET, VAL[0])

/* global get uint32_t 3D array macro */
#define PLAT_ATTR_GET_INT32_3D_ARRAY(ID, TARGET, VAL)                          \
	_getAttributeArraySignedWord(ID, TARGET, VAL[0][0])
/* global set uint32_t 3D array macro */
#define PLAT_ATTR_SET_INT32_3D_ARRAY(ID, TARGET, VAL)                          \
	_setAttributeArraySignedWord(ID, TARGET, VAL[0][0])

/* global get uint32_t 4D array macro */
#define PLAT_ATTR_GET_INT32_4D_ARRAY(ID, TARGET, VAL)                          \
	_getAttributeArraySignedWord(ID, TARGET, VAL[0][0][0])
/* global set uint32_t 4D array macro */
#define PLAT_ATTR_SET_INT32_4D_ARRAY(ID, TARGET, VAL)                          \
	_setAttributeArraySignedWord(ID, TARGET, VAL[0][0][0])

/* global get uint64_t 1D array macro */
#define PLAT_ATTR_GET_INT64_1D_ARRAY(ID, TARGET, VAL)                          \
	_getAttributeArraySignedDoubleWord(ID, TARGET, VAL)
/* global set uint64_t 1D array macro */
#define PLAT_ATTR_SET_INT64_1D_ARRAY(ID, TARGET, VAL)                          \
	_setAttributeArraySignedDoubleWord(ID, TARGET, VAL)

/* global get uint64_t 2D array macro */
#define PLAT_ATTR_GET_INT64_2D_ARRAY(ID, TARGET, VAL)                          \
	_getAttributeArraySignedDoubleWord(ID, TARGET, VAL[0])
/* global set uint64_t 2D array macro */
#define PLAT_ATTR_SET_INT64_2D_ARRAY(ID, TARGET, VAL)                          \
	_setAttributeArraySignedDoubleWord(ID, TARGET, VAL[0])

/* global get uint64_t 3D array macro */
#define PLAT_ATTR_GET_INT64_3D_ARRAY(ID, TARGET, VAL)                          \
	_getAttributeArraySignedDoubleWord(ID, TARGET, VAL[0][0])
/* global set uint64_t 3D array macro */
#define PLAT_ATTR_SET_INT64_3D_ARRAY(ID, TARGET, VAL)                          \
	_setAttributeArraySignedDoubleWord(ID, TARGET, VAL[0][0])

/* global get uint64_t 4D array macro */
#define PLAT_ATTR_GET_INT64_4D_ARRAY(ID, TARGET, VAL)                          \
	_getAttributeArraySignedDoubleWord(ID, TARGET, VAL[0][0][0])
/* global set uint64_t 4D array macro */
#define PLAT_ATTR_SET_INT64_4D_ARRAY(ID, TARGET, VAL)                          \
	_setAttributeArraySignedDoubleWord(ID, TARGET, VAL[0][0][0])

/* global get int macro (uint8_t, 16, 32 and 64) */
#define PLAT_ATTR_GET_GLOBAL_INT(ID, TARGET, VAL)                              \
	_get<ID##_Type>(ID, TARGET, VAL)

/* global set int macro (uint8_t, 16, 32 and 64) */
#define PLAT_ATTR_SET_GLOBAL_INT(ID, TARGET, VAL)                              \
	_set<ID##_Type>(ID, TARGET, VAL)

/******************************************************************************/
// Get Override Macros
/******************************************************************************/
/* global get override uint8_t 1D array macro */
#define PLAT_ATTR_GET_OVERRIDE_INT8_1D_ARRAY(ID, TARGET, VAL)                  \
	_getAttributeOverrideArraySignedShort(ID, TARGET, VAL)
/* global get override uint8_t 2D array macro */
#define PLAT_ATTR_GET_OVERRIDE_INT8_2D_ARRAY(ID, TARGET, VAL)                  \
	_getAttributeOverrideArraySignedShort(ID, TARGET, VAL[0])
/* global get override uint8_t 3D array macro */
#define PLAT_ATTR_GET_OVERRIDE_INT8_3D_ARRAY(ID, TARGET, VAL)                  \
	_getAttributeOverrideArraySignedShort(ID, TARGET, VAL[0][0])
/* global get override uint8_t 4D array macro */
#define PLAT_ATTR_GET_OVERRIDE_INT8_4D_ARRAY(ID, TARGET, VAL)                  \
	_getAttributeOverrideArraySignedShort(ID, TARGET, VAL[0][0][0])

/* global get override uint16_t 1D array macro */
#define PLAT_ATTR_GET_OVERRIDE_INT16_1D_ARRAY(ID, TARGET, VAL)                 \
	_getAttributeOverrideArraySignedHalfWord(ID, TARGET, VAL)
/* global get override uint16_t 2D array macro */
#define PLAT_ATTR_GET_OVERRIDE_INT16_2D_ARRAY(ID, TARGET, VAL)                 \
	_getAttributeOverrideArraySignedHalfWord(ID, TARGET, VAL[0])
/* global get override uint16_t 3D array macro */
#define PLAT_ATTR_GET_OVERRIDE_INT16_3D_ARRAY(ID, TARGET, VAL)                 \
	_getAttributeOverrideArraySignedHalfWord(ID, TARGET, VAL[0][0])
/* global get override uint16_t 4D array macro */
#define PLAT_ATTR_GET_OVERRIDE_INT16_4D_ARRAY(ID, TARGET, VAL)                 \
	_getAttributeOverrideArraySignedHalfWord(ID, TARGET, VAL[0][0][0])

/* global get override uint32_t 1D array macro */
#define PLAT_ATTR_GET_OVERRIDE_INT32_1D_ARRAY(ID, TARGET, VAL)                 \
	_getAttributeOverrideArraySignedWord(ID, TARGET, VAL)
/* global get override uint32_t 2D array macro */
#define PLAT_ATTR_GET_OVERRIDE_INT32_2D_ARRAY(ID, TARGET, VAL)                 \
	_getAttributeOverrideArraySignedWord(ID, TARGET, VAL[0])
/* global get override uint32_t 3D array macro */
#define PLAT_ATTR_GET_OVERRIDE_INT32_3D_ARRAY(ID, TARGET, VAL)                 \
	_getAttributeOverrideArraySignedWord(ID, TARGET, VAL[0][0])
/* global get override uint32_t 4D array macro */
#define PLAT_ATTR_GET_OVERRIDE_INT32_4D_ARRAY(ID, TARGET, VAL)                 \
	_getAttributeOverrideArraySignedWord(ID, TARGET, VAL[0][0][0])

/* global get override uint64_t 1D array macro */
#define PLAT_ATTR_GET_OVERRIDE_INT64_1D_ARRAY(ID, TARGET, VAL)                 \
	_getAttributeOverrideArraySignedDoubleWord(ID, TARGET, VAL)
/* global get override uint64_t 2D array macro */
#define PLAT_ATTR_GET_OVERRIDE_INT64_2D_ARRAY(ID, TARGET, VAL)                 \
	_getAttributeOverrideArraySignedDoubleWord(ID, TARGET, VAL[0])
/* global get override uint64_t 3D array macro */
#define PLAT_ATTR_GET_OVERRIDE_INT64_3D_ARRAY(ID, TARGET, VAL)                 \
	_getAttributeOverrideArraySignedDoubleWord(ID, TARGET, VAL[0][0])
/* global get override uint64_t 4D array macro */
#define PLAT_ATTR_GET_OVERRIDE_INT64_4D_ARRAY(ID, TARGET, VAL)                 \
	_getAttributeOverrideArraySignedDoubleWord(ID, TARGET, VAL[0][0][0])

namespace fapi2
{

//******************************************************************************
// Get uint8_t
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _get(const AttributeId i_id, const Target<K, M, V>& i_target,
		uint8_t& o_value)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get uint16_t
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _get(const AttributeId i_id, const Target<K, M, V>& i_target,
		uint16_t& o_value)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get uint32_t
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _get(const AttributeId i_id, const Target<K, M, V>& i_target,
		uint32_t& o_value)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get uint64_t
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _get(const AttributeId i_id, const Target<K, M, V>& i_target,
		uint64_t& o_value)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get Override uint8_t
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _getOverride(const AttributeId i_id, const Target<K, M, V>& i_target,
			uint8_t& o_value)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get Override uint16_t
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _getOverride(const AttributeId i_id, const Target<K, M, V>& i_target,
			uint16_t& o_value)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get Override uint32_t
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _getOverride(const AttributeId i_id, const Target<K, M, V>& i_target,
			uint32_t& o_value)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get Override uint64_t
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _getOverride(const AttributeId i_id, const Target<K, M, V>& i_target,
			uint64_t& o_value)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get override EC Feature (uint8_t)
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _getEcFeatureOverride(const AttributeId i_id,
				 const Target<K, M, V>& i_target,
				 uint8_t& o_value)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 1;
}

//******************************************************************************
// Get uint8_t array
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _getAttributeArrayShort(const AttributeId i_id,
				   const Target<K, M, V>& i_target,
				   uint8_t* o_pValues)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Set uint8_t array
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _setAttributeArrayShort(const AttributeId i_id,
				   const Target<K, M, V>& i_target,
				   uint8_t* i_pValues)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get uint16_t array
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _getAttributeArrayHalfWord(const AttributeId i_id,
				      const Target<K, M, V>& i_target,
				      uint16_t* o_pValues)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Set uint16_t array
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _setAttributeArrayHalfWord(const AttributeId i_id,
				      const Target<K, M, V>& i_target,
				      uint16_t* i_pValues)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get uint32_t array
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _getAttributeArrayWord(const AttributeId i_id,
				  const Target<K, M, V>& i_target,
				  uint32_t* o_pValues)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Set uint32_t array
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _setAttributeArrayWord(const AttributeId i_id,
				  const Target<K, M, V>& i_target,
				  uint32_t* i_pValues)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get uint64_t array
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _getAttributeArrayDoubleWord(const AttributeId i_id,
					const Target<K, M, V>& i_target,
					uint64_t* o_pValues)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Set uint64_t array
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _setAttributeArrayDoubleWord(const AttributeId i_id,
					const Target<K, M, V>& i_target,
					uint64_t* i_pValues)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get Override uint8_t array
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _getAttributeOverrideArrayShort(const AttributeId i_id,
					   const Target<K, M, V>& i_target,
					   uint8_t* o_pValues)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get Override uint16_t array
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _getAttributeOverrideArrayHalfWord(const AttributeId i_id,
					      const Target<K, M, V>& i_target,
					      uint16_t* o_pValues)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get Override uint32_t array
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _getAttributeOverrideArrayWord(const AttributeId i_id,
					  const Target<K, M, V>& i_target,
					  uint32_t* o_pValues)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get Override uint64_t array
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _getAttributeOverrideArrayDoubleWord(const AttributeId i_id,
						const Target<K, M, V>& i_target,
						uint64_t* o_pValues)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Set uint8_t
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _set(const AttributeId i_id, const Target<K, M, V>& i_target,
		uint8_t& i_value)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Set uint16_t
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _set(const AttributeId i_id, const Target<K, M, V>& i_target,
		uint16_t& i_value)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Set uint32_t
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _set(const AttributeId i_id, const Target<K, M, V>& i_target,
		uint32_t& i_value)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Set uint64_t
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _set(const AttributeId i_id, const Target<K, M, V>& i_target,
		const uint64_t& i_value)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get int8_t
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _get(const AttributeId i_id, const Target<K, M, V>& i_target,
		int8_t& o_value)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get int16_t
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _get(const AttributeId i_id, const Target<K, M, V>& i_target,
		int16_t& o_value)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get int32_t
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _get(const AttributeId i_id, const Target<K, M, V>& i_target,
		int32_t& o_value)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get int64_t
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _get(const AttributeId i_id, const Target<K, M, V>& i_target,
		int64_t& o_value)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get Override int8_t
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _getOverride(const AttributeId i_id, const Target<K, M, V>& i_target,
			int8_t& o_value)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get Override int16_t
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _getOverride(const AttributeId i_id, const Target<K, M, V>& i_target,
			int16_t& o_value)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get Override int32_t
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _getOverride(const AttributeId i_id, const Target<K, M, V>& i_target,
			int32_t& o_value)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get Override int64_t
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _getOverride(const AttributeId i_id, const Target<K, M, V>& i_target,
			int64_t& o_value)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get int8_t array
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _getAttributeArraySignedShort(const AttributeId i_id,
					 const Target<K, M, V>& i_target,
					 int8_t* o_pValues)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Set int8_t array
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _setAttributeArraySignedShort(const AttributeId i_id,
					 const Target<K, M, V>& i_target,
					 int8_t* i_pValues)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get int16_t array
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _getAttributeArraySignedHalfWord(const AttributeId i_id,
					    const Target<K, M, V>& i_target,
					    int16_t* o_pValues)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Set int16_t array
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _setAttributeArraySignedHalfWord(const AttributeId i_id,
					    const Target<K, M, V>& i_target,
					    int16_t* i_pValues)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get int32_t array
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _getAttributeArraySignedWord(const AttributeId i_id,
					const Target<K, M, V>& i_target,
					int32_t* o_pValues)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Set int32_t array
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _setAttributeArraySignedWord(const AttributeId i_id,
					const Target<K, M, V>& i_target,
					int32_t* i_pValues)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get int64_t array
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _getAttributeArraySignedDoubleWord(const AttributeId i_id,
					      const Target<K, M, V>& i_target,
					      int64_t* o_pValues)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Set int64_t array
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _setAttributeArraySignedDoubleWord(const AttributeId i_id,
					      const Target<K, M, V>& i_target,
					      int64_t* i_pValues)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get Override int8_t array
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _getAttributeOverrideArraySignedShort(
    const AttributeId i_id, const Target<K, M, V>& i_target, int8_t* o_pValues)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get Override int16_t array
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _getAttributeOverrideArraySignedHalfWord(
    const AttributeId i_id, const Target<K, M, V>& i_target, int16_t* o_pValues)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get Override int32_t array
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _getAttributeOverrideArraySignedWord(const AttributeId i_id,
						const Target<K, M, V>& i_target,
						int32_t* o_pValues)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Get Override int64_t array
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _getAttributeOverrideArraySignedDoubleWord(
    const AttributeId i_id, const Target<K, M, V>& i_target, int64_t* o_pValues)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Set int8_t
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _set(const AttributeId i_id, const Target<K, M, V>& i_target,
		int8_t& i_value)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Set int16_t
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _set(const AttributeId i_id, const Target<K, M, V>& i_target,
		int16_t& i_value)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Set int32_t
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _set(const AttributeId i_id, const Target<K, M, V>& i_target,
		int32_t& i_value)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

//******************************************************************************
// Set int64_t
//******************************************************************************
template <TargetType K, MulticastType M, typename V>
ReturnCode _set(const AttributeId i_id, const Target<K, M, V>& i_target,
		const int64_t& i_value)
{
	//	std::cout << __PRETTY_FUNCTION__ << " not implemented for " <<
	//i_id << "\n" << "type: " << i_target.getType() << " id: " << i_id <<
	//"\n";

	return 0;
}

} // namespace fapi2
#endif // FAPI2PLATATTRIBUTESERVICE_H

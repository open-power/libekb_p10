/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: chips/p10/common/include/plat_target_filter.H $               */
/*                                                                        */
/* OpenPOWER EKB Project                                                  */
/*                                                                        */
/* COPYRIGHT 2018,2020                                                    */
/* [+] International Business Machines Corp.                              */
/*                                                                        */
/*                                                                        */
/* Licensed under the Apache License, Version 2.0 (the "License");        */
/* you may not use this file except in compliance with the License.       */
/* You may obtain a copy of the License at                                */
/*                                                                        */
/*     http://www.apache.org/licenses/LICENSE-2.0                         */
/*                                                                        */
/* Unless required by applicable law or agreed to in writing, software    */
/* distributed under the License is distributed on an "AS IS" BASIS,      */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or        */
/* implied. See the License for the specific language governing           */
/* permissions and limitations under the License.                         */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/**
 * @file plat_target_filter.H
 * @brief platform bit-mask definitions for P10 fapi2 TargetFilter enum
 */

#ifndef __FAPI2_PLAT_TARGET_FILTER__
#define __FAPI2_PLAT_TARGET_FILTER__

#include <stdint.h>

//
// Define TargetFilter enum values for the platform
//
namespace fapi2
{
namespace PlatTargetFilter
{
// These values must contain only 1 bit 'on' so that they can be ORed
// together as composite filters

constexpr uint64_t BIT0 = 0x8000000000000000;
constexpr uint64_t PLAT_TARGET_FILTER_TP = (BIT0 >> 1);		// Pervasive 1
constexpr uint64_t PLAT_TARGET_FILTER_NEST_NORTH = (BIT0 >> 2); // Pervasive 2
constexpr uint64_t PLAT_TARGET_FILTER_NEST_SOUTH = (BIT0 >> 3); // Pervasive 3
constexpr uint64_t PLAT_TARGET_FILTER_PCI0 = (BIT0 >> 8);	// Pervasive 8
constexpr uint64_t PLAT_TARGET_FILTER_PCI1 = (BIT0 >> 9);	// Pervasive 9
constexpr uint64_t PLAT_TARGET_FILTER_MC0 = (BIT0 >> 12);	// Pervasive 12
constexpr uint64_t PLAT_TARGET_FILTER_MC1 = (BIT0 >> 13);	// Pervasive 13
constexpr uint64_t PLAT_TARGET_FILTER_MC2 = (BIT0 >> 14);	// Pervasive 14
constexpr uint64_t PLAT_TARGET_FILTER_MC3 = (BIT0 >> 15);	// Pervasive 15
constexpr uint64_t PLAT_TARGET_FILTER_PAU0 = (BIT0 >> 16);	// Pervasive 16
constexpr uint64_t PLAT_TARGET_FILTER_PAU1 = (BIT0 >> 17);	// Pervasive 17
constexpr uint64_t PLAT_TARGET_FILTER_PAU2 = (BIT0 >> 18);	// Pervasive 18
constexpr uint64_t PLAT_TARGET_FILTER_PAU3 = (BIT0 >> 19);	// Pervasive 19
constexpr uint64_t PLAT_TARGET_FILTER_IOHS0 = (BIT0 >> 24);	// Pervasive 24
constexpr uint64_t PLAT_TARGET_FILTER_IOHS1 = (BIT0 >> 25);	// Pervasive 25
constexpr uint64_t PLAT_TARGET_FILTER_IOHS2 = (BIT0 >> 26);	// Pervasive 26
constexpr uint64_t PLAT_TARGET_FILTER_IOHS3 = (BIT0 >> 27);	// Pervasive 27
constexpr uint64_t PLAT_TARGET_FILTER_IOHS4 = (BIT0 >> 28);	// Pervasive 28
constexpr uint64_t PLAT_TARGET_FILTER_IOHS5 = (BIT0 >> 29);	// Pervasive 29
constexpr uint64_t PLAT_TARGET_FILTER_IOHS6 = (BIT0 >> 30);	// Pervasive 30
constexpr uint64_t PLAT_TARGET_FILTER_IOHS7 = (BIT0 >> 31);	// Pervasive 31
constexpr uint64_t PLAT_TARGET_FILTER_EQ0 = (BIT0 >> 32);	// Pervasive 32
constexpr uint64_t PLAT_TARGET_FILTER_EQ1 = (BIT0 >> 33);	// Pervasive 33
constexpr uint64_t PLAT_TARGET_FILTER_EQ2 = (BIT0 >> 34);	// Pervasive 34
constexpr uint64_t PLAT_TARGET_FILTER_EQ3 = (BIT0 >> 35);	// Pervasive 35
constexpr uint64_t PLAT_TARGET_FILTER_EQ4 = (BIT0 >> 36);	// Pervasive 36
constexpr uint64_t PLAT_TARGET_FILTER_EQ5 = (BIT0 >> 37);	// Pervasive 37
constexpr uint64_t PLAT_TARGET_FILTER_EQ6 = (BIT0 >> 38);	// Pervasive 38
constexpr uint64_t PLAT_TARGET_FILTER_EQ7 = (BIT0 >> 39);	// Pervasive 39

// placeholder for recent hwp changes compile in pub-ekb, will fix with full
// support later
constexpr uint64_t PLAT_TARGET_FILTER_MC = 0xFFFFFFFFFFFFFFFF;

} // namespace PlatTargetFilter

} // namespace fapi2

#endif

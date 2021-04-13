/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: hwpf/fapi2/include/plat/target.H $                            */
/*                                                                        */
/* IBM CONFIDENTIAL                                                       */
/*                                                                        */
/* EKB Project                                                            */
/*                                                                        */
/* COPYRIGHT 2012,2019                                                    */
/* [+] International Business Machines Corp.                              */
/*                                                                        */
/*                                                                        */
/* The source code for this program is not published or otherwise         */
/* divested of its trade secrets, irrespective of what has been           */
/* deposited with the U.S. Copyright Office.                              */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/**
 * @file target.H
 * @brief platform specializations for fapi2 targets
 */

#ifndef __FAPI2_TARGET__
#define __FAPI2_TARGET__

#include <plat_target.H>
#include <fapi2_target.H>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <plat_trace.H>

namespace fapi2
{

template<TargetType K, MulticastType M, typename V>
static constexpr void plat_apply_target_limits(void)
{
    static_assert(!(K & TARGET_TYPE_MULTICAST),
                  "Multicast targets are not supported on this platform");
}

template<TargetType T, MulticastType M, typename V>
inline void Target<T, M, V>::mcUpdateHandle() {};

///
/// @brief Assignment Operator.
/// @param[in] i_right Reference to Target to assign from.
/// @return Reference to 'this' Target
///
template<TargetType K, MulticastType M, typename V>
Target<K, M, V>& Target<K, M, V>::operator=(const Target& i_right)
{
    iv_handle = i_right.iv_handle;
    return *this;
}

///
/// @brief Equality Comparison Operator
/// @param[in] i_right Reference to Target to compare.
/// @return bool. True if equal.
/// @note Platforms need to define this so that the physical
/// targets are determined to be equivilent rather than just the handles
///
template<TargetType K, MulticastType M, typename V>
bool Target<K, M, V>::operator==(const Target& i_right) const
{
    return i_right.iv_handle == iv_handle;
}

///
/// @brief Inquality Comparison Operator
/// @param[in] i_right Reference to Target to compare.
/// @return bool. True if not equal.
/// @note Platforms need to define this so that the physical
/// targets are determined to be equivilent rather than just the handles
///
template<TargetType K, MulticastType M, typename V>
bool Target<K, M, V>::operator!=(const Target& i_right) const
{
    return i_right.iv_handle != iv_handle;
}

///
/// @brief Less Than Comparison Operator
/// @param[in] i_right Reference to Target to compare.
/// @return bool. True if less than i_right.
/// @note Platforms need to define this so that the physical
/// targets are determined to be less than rather than just the handles
///
template<TargetType K, MulticastType M, typename V>
bool Target<K, M, V>::operator<(const Target& i_right) const
{
    return i_right.iv_handle < iv_handle;
}

///
/// @brief Get this target's immediate parent
/// @tparam T The type of the parent
/// @return Target<T> a target representing the parent
///
template<TargetType K, MulticastType M, typename V>
template<TargetType T>
inline Target<T, M, V> Target<K, M, V>::getParent(void) const
{
    // It's forbidden to strip multicast from a target below PROC_CHIP level:
    // Since a multicast might end up expanding to more than one unicast target,
    // users are required to use getChildren if they want to map back to unicast.
    static_assert(!(((K ^ T) & TARGET_TYPE_MULTICAST) && ((T & TARGET_TYPE_CHIPLETS) != TARGET_TYPE_NONE)),
                  "Parent target for a multicast target must also be multicast or PROC_CHIP");

    // For testing
    return Target<T, M, V>(iv_handle);
}

static inline bool filter_ttype(struct pdbg_target *target, uint64_t type)
{
	uint32_t chip_id = 0;

	if (type == -1ULL)
		return true;

	if (pdbg_target_u32_property(target, "index", &chip_id))
		return false;

	/* Pervasive 1 is bit 0/63 */
	if (chip_id && (type & ((uint64_t) 1 << (64 - chip_id))))
		return true;

	return false;
}

template<TargetType T>
inline const char *getChildrenImpl();

template<> inline const char *getChildrenImpl<TARGET_TYPE_PERV>() { return "chiplet"; }
/// TODO This implementaion logic need to be revisited.
template<> inline const char *getChildrenImpl<TARGET_TYPE_IOHS>() { return "iohs"; }
template<> inline const char *getChildrenImpl<TARGET_TYPE_MC>() { return "mc"; }
template<> inline const char *getChildrenImpl<TARGET_TYPE_PEC>() { return "pec"; }
template<> inline const char *getChildrenImpl<TARGET_TYPE_CORE>() { return "core"; }
template<> inline const char *getChildrenImpl<TARGET_TYPE_NMMU>() { return "nmmu"; }
template<> inline const char *getChildrenImpl<TARGET_TYPE_PAUC>() { return "pauc"; }
template<> inline const char *getChildrenImpl<TARGET_TYPE_PAU>() { return "pau"; }

///
/// @brief Get this target's children
/// @tparam T The type of the parent
/// @param[in] i_state The desired TargetState of the children
/// @return std::vector<Target<T> > a vector of present/functional
/// children
/// @warning The children of EX's (cores) are expected to be returned
/// in order. That is, core 0 is std::vector[0].
///
template<TargetType K, MulticastType M, typename V>
template<TargetType T>
inline std::vector<Target<T, M, V> >
Target<K, M, V>::getChildren(const TargetState i_state) const
{
	std::vector<Target<T>> targets;
	struct pdbg_target *target = NULL;
	struct pdbg_target *cur_target = static_cast<struct pdbg_target *>(this->get());

	if (T == fapi2::TARGET_TYPE_PERV)
	{
		// Adding only required hwp consumed child targets
		std::vector<std::string> childname =
			{"iohs", "mc", "pec", "core", "nmmu", "pauc", "pau"};

		for(auto name : childname)
		{
			bool state = true;
			pdbg_for_each_target(name.c_str(), cur_target, target) {
				if (i_state == fapi2::TARGET_STATE_FUNCTIONAL) {
					state = Target(target).isFunctional();
				}
				else if (i_state == fapi2::TARGET_STATE_PRESENT) {
					state = isTargetPresent(Target(target));
				}
				//else default state return all.
				if (state) {
					targets.push_back(target);
				}
			}
		}
	}
	else
	{
		const char *klass = getChildrenImpl<T>();

		pdbg_for_each_target(klass, cur_target, target){
			bool state = true;
			if (i_state == fapi2::TARGET_STATE_FUNCTIONAL) {
				 state = Target(target).isFunctional();
			}
			else if (i_state == TARGET_STATE_PRESENT) {
				state = isTargetPresent(Target(target));
			}
			if (state) {
				targets.push_back(target);
			}
		}
	}
	return targets;
}

// @brief Get this target's children, filtered
// @tparam T The type of the parent
// @tparam T_SELF The type of target on which this is called
// @tparam V the type of the target's Value
// @param[in] i_filter The desired chiplet filter
// @param[in] i_state The desired TargetState of the children
// @return std::vector<Target<T> > a vector of present/functional children

template<TargetType T_SELF, MulticastType M, typename V>
template< TargetType T>
inline std::vector<Target<T, M, V> >
	Target<T_SELF, M, V>::getChildren(const TargetFilter i_filter,
		const TargetState i_state) const
{
	std::vector<Target<T, M, V>> children;

	// C++ wont support partial specialization template.
	// Limit to getting Pervasive children from proc_chip parent for now
	static_assert(((T == fapi2::TARGET_TYPE_PERV) &&
		(T_SELF == fapi2::TARGET_TYPE_PROC_CHIP)),
		"getChildren-Filter only supports getting TARGET_TYPE_PERV children on a TARGET_TYPE_PROC_CHIP");

	FAPI_DBG("i_filter=0x%llX, T_SELF=0x%.8X, T=0x%.8X \n", i_filter,T_SELF, T);

	children = this->getChildren<T>(i_state);

	for(auto iter = children.begin(); iter != children.end();) {
		uint64_t bitMask = 0x0;
		struct pdbg_target * child =
			static_cast<struct pdbg_target *>(iter->get());

		// ATTR_CHIPLET_ID represents the Pervasive Chiplet numbering and is
		// needed to create the l_bitMask to use against i_filter
		uint8_t chiplet_id = 0;

		if(!pdbg_target_get_attribute(child, "ATTR_CHIPLET_ID", 1, 1, &chiplet_id)) {
			FAPI_ERR ("Can not read CHIPLET_ID attribute");
			bitMask = 0xFFFFFFFFFFFFFFFF;
		}
		else
		{
			bitMask = 0x8000000000000000 >> chiplet_id;
		}

		if (i_filter & bitMask)
		{
			FAPI_DBG("keep child chiplet id=0x%.2X", chiplet_id);
			++iter;
		}
		else
		{
			iter = children.erase(iter); // this increments childIter
		}
	}

	return children;
}

template<TargetType K, MulticastType M, typename V>
template< TargetType T, MulticastType O >
inline Target < T | TARGET_TYPE_MULTICAST, O, V >
Target<K, M, V>::getMulticast(const MulticastGroup i_group) const
{
    // C++ does not allow partial specialization of class member functions (please prove me wrong!),
    // so we need to use this static assertion instead. On the upside, the error message is much clearer ;)
    static_assert((K == TARGET_TYPE_PROC_CHIP), "Parent target must be the proc chip");
    static_assert((T & TARGET_TYPE_MULTICASTABLE) != 0,
                  "Requested target type must be part of TARGET_TYPE_MULTICASTABLE");
    static_assert(bitCount<T>::count == 1,
                  "Requested target type must be a single type, TARGET_TYPE_MULTICAST will be added automatically");

    return Target < T | TARGET_TYPE_MULTICAST, O, V > ();
}

template<TargetType K, MulticastType M, typename V>
template< MulticastType O >
inline Target < TARGET_TYPE_CORE | TARGET_TYPE_MULTICAST, O, V >
Target<K, M, V>::getMulticast(const MulticastGroup i_group, const MulticastCoreSelect i_cores) const
{
    // C++ does not allow partial specialization of class member functions (please prove me wrong!),
    // so we need to use this static assertion instead. On the upside, the error message is much clearer ;)
    static_assert((K == TARGET_TYPE_PROC_CHIP), "Parent target must be the proc chip");
    return Target < TARGET_TYPE_CORE | TARGET_TYPE_MULTICAST, O, V > ();
}


///
/// @brief Get the target at the other end of a bus
/// @tparam T The type of the target on the other end
/// @param[out] o_target A target representing the thing on the other end
/// @param[in] i_state The desired TargetState of the other end
/// @return FAPI2_RC_SUCCESS if OK, platforms will return a non-success
/// ReturnCode in the event of failure
/// @note o_target is only valid if return is FAPI2_RC_SUCCESS
///

template<TargetType K, MulticastType M, typename V>
template<TargetType T>
inline fapi2::ReturnCodes
Target<K, M, V>::getOtherEnd(Target<T, M, V>& o_target,
                             const TargetState i_state) const
{
    // To keep the compiler quiet about unused variables
    static_cast<void>(i_state);

    o_target = Target<T, M, V>();

    return FAPI2_RC_SUCCESS;
}

///
/// @brief Is the target functional?
/// @return true if target is functional, false if non-functional
///

template<TargetType K, MulticastType M, typename V>
inline bool
Target<K, M, V>::isFunctional(void) const
{
	uint8_t buf[5];
	struct pdbg_target *target =  static_cast<struct pdbg_target *>(this->get());

	if (!pdbg_target_get_attribute_packed(target, "ATTR_HWAS_STATE", "41", 1, buf)) {
		FAPI_ERR ("Can not read ATTR_HWAS_STATE attribute");
		return false;
	}

	//isFuntional bit is stored in 4th byte and bit 3 position in HWAS_STATE
	return (buf[4] & 0x20);
}

///
/// @brief Returns the chiplet number associated with the Target
/// @return The chiplet number for the Target. 0 is returned if the
/// Target does not have a chiplet number (for ex, the PROC_CHIP Target)
/// @note For logical targets such as the EX, the chiplet number of
/// their immediate parent chiplet is returned
///
template<TargetType K, MulticastType M, typename V>
inline uint8_t
Target<K, M, V>::getChipletNumber(void) const
{
    static_assert((K & TARGET_TYPE_MULTICAST) == 0, "getChipletNumber is not supported for multicast targets");

    struct pdbg_target *target =  static_cast<struct pdbg_target *>(this->get());
    uint8_t chiplet_id = 0;

    if(!pdbg_target_get_attribute(target, "ATTR_CHIPLET_ID", 1, 1, &chiplet_id)) {
         FAPI_ERR ("Can not read CHIPLET_ID attribute");
    }

    return chiplet_id;
}

#ifdef FAPI2_ENABLE_PLATFORM_GET_CORE_SELECT

template<TargetType K, MulticastType M, typename V>
inline MulticastCoreSelect
Target<K, M, V>::_getCoreSelect(void) const
{
    // Platform can return the core select value stored in it's Target handle
    return MCCORE_0;
}

#endif // FAPI2_ENABLE_PLATFORM_GET_CORE_SELECT

///
/// @brief Return the string interpretation of this target
/// @tparam T The type of the target
/// @param[in] i_target Target<T>
/// @param[in] i_buffer buffer to write in to
/// @param[in] i_bsize size of the buffer
/// @return void
/// @post The contents of the buffer is replaced with the string
/// representation of the target
///
template<TargetType T, MulticastType M, typename V >
inline void toString(const Target<T, M, V>& i_target,
                     char* i_buffer, size_t i_bsize)
{
    // FIXME: If ATTR_FAPI_NAME size got changed then below buffer size need
    // to change because, ATTR_FAPI_NAME is non-fapi attribute and currently
    // libekb using size based on platform specific attribute_types.xml from pdata.
    // Note: Size included with NULL.
    size_t fapiname_size = 64;
    char fapiname[fapiname_size] = {0};

    struct pdbg_target* target = static_cast<struct pdbg_target *>(i_target.get());
    if (!pdbg_target_get_attribute(target, "ATTR_FAPI_NAME", 1,
                                   fapiname_size, fapiname)) {
        FAPI_ERR("Could not read ATTR_FAPI_NAME attribute");
        snprintf(i_buffer, i_bsize, "Target 0x%lX/0x%.16lX/0x%X", i_target.get(), T, M);
    }
    else {
        if (i_bsize < fapiname_size) {
            FAPI_INF("Given buffer size[%d] is not enough to hold fapiname[%s] size[%d]",
                     i_bsize, fapiname, fapiname_size);
            memcpy(i_buffer, fapiname, i_bsize);
            if (i_bsize > 0) {
                i_buffer[i_bsize - 1] = '\0';
            }
        }
        else {
            memcpy(i_buffer, fapiname, fapiname_size);
        }
    }
}

///
/// @brief Return the string interpretation of this target
/// @tparam T The type of the target
/// @tparam B The type of the buffer
/// @param[in] i_target A pointer to the Target<T>
/// @param[in] i_buffer buffer to write in to
/// @param[in] i_bsize  size of the buffer
/// @return void
/// @post The contents of the buffer is replaced with the string
/// representation of the target
///
template< TargetType T, MulticastType M, typename V >
inline void toString(const Target<T, M, V>* i_target,
                     char* i_buffer, size_t i_bsize)
{
    toString(*i_target, i_buffer, i_bsize);
}

template<>
template<>
inline Target<TARGET_TYPE_CHIPS> Target<TARGET_TYPE_DIMM>::getParent(void) const
{
	struct pdbg_target *target;

	target = pdbg_target_require_parent("pib", iv_handle);

	return Target<TARGET_TYPE_CHIPS>(target);
}

/* Copied from collect_reg_ffdc.H. We can't just include
 * collect_reg_ffdc.H because that first includes target.H (this file)
 * so we have no way of accessing it's definition of this. So instead
 * we have to redefine it here. */
const fapi2::TargetType PLAT_TARGET_TYPE_PROC_CHIPLETS = fapi2::TARGET_TYPE_EX |
        fapi2::TARGET_TYPE_MCS |
        fapi2::TARGET_TYPE_XBUS |
        fapi2::TARGET_TYPE_CORE |
        fapi2::TARGET_TYPE_EQ |
        fapi2::TARGET_TYPE_MCA |
        fapi2::TARGET_TYPE_MCBIST |
        fapi2::TARGET_TYPE_MI |
        fapi2::TARGET_TYPE_CAPP |
        fapi2::TARGET_TYPE_DMI |
        fapi2::TARGET_TYPE_OBUS |
        fapi2::TARGET_TYPE_OBUS_BRICK |
        fapi2::TARGET_TYPE_SBE |
        fapi2::TARGET_TYPE_PPE |
        fapi2::TARGET_TYPE_PERV |
        fapi2::TARGET_TYPE_PEC |
        fapi2::TARGET_TYPE_PHB |
        fapi2::TARGET_TYPE_MC |
        fapi2::TARGET_TYPE_OMI |
        fapi2::TARGET_TYPE_MEM_PORT;

template<>
template<>
inline Target<TARGET_TYPE_CHIPS> Target<PLAT_TARGET_TYPE_PROC_CHIPLETS>::getParent(void) const
{
	struct pdbg_target *target;

	target = pdbg_target_require_parent("pib", iv_handle);

	return Target<TARGET_TYPE_CHIPS>(target);
}

/// @brief Get an equivalent pdbg class type
/// Note: Only enabled for Processor type.
template<TargetType T>
inline const char* getTargetClass()
{
	static_assert((T == TARGET_TYPE_PROC_CHIP),
                  " Target Type support not available");
	return "proc";
}

///
/// @brief Get an enumerated target of a specific type
/// @tparam T The type of the target
/// @param[in] ordinal representing the ordinal number of
/// the desired target
/// @return Target<T> the target requested
///
template<TargetType T, MulticastType M, typename V>
inline Target<T, M, V> getTarget(uint64_t ordinal)
{
	const char *class_type = getTargetClass<T>();
	struct pdbg_target *target;
	uint32_t fapi_position = 0;

	pdbg_for_each_class_target(class_type, target)
	{
		if(!pdbg_target_get_attribute(target, "ATTR_FAPI_POS", 4, 1, &fapi_position)) {
			FAPI_ERR ("Can not read FAPI_POS attribute");
			assert(false);
		}
		if (ordinal == fapi_position)
		{
			return Target<T, M, V>(target);
		}
	}

        //Error Case No Matching target found.
	FAPI_ERR("getTarget(): No matching Target Found Class: %s  Ordinal: %.8X ",
				class_type, ordinal);
	assert(false);

	//To keep compiler happy.
	return Target<T, M, V>(target);
}

inline bool isTargetPresent(struct pdbg_target *target)
{
        uint8_t buf[5];

        if (!pdbg_target_get_attribute_packed(target, "ATTR_HWAS_STATE", "41", 1, buf)) {
                FAPI_ERR ("Can not read ATTR_HWAS_STATE attribute");
                return false;
        }

        //isPresent bit is stored in 4th byte and bit 2 position in HWAS_STATE
        return (buf[4] & 0x40);
}

///
/// @brief Return the entity of given target
/// @tparam T The type of the target
/// @param[in] i_target Target<T>
/// @param[in] i_buffer buffer to write entity path
/// @return void
/// @post The contents of the buffer is replaced with the entity path
/// of the target
///
template<TargetType T, MulticastType M, typename V >
inline void getTgtEntityPath(const Target<T, M, V>& i_target,
                             std::vector<uint8_t>& i_buffer)
{
    // FIXME: If ATTR_PHYS_BIN_PATH size got changed then below buffer size need
    // to change because, ATTR_PHYS_BIN_PATH is non-fapi attribute and currently
    // libekb using size based on platform specific attribute_types.xml from pdata.
    // Note: Size included with NULL.
    size_t tgt_entitypath_size = 21;
    uint8_t tgt_entitypath[tgt_entitypath_size] = {0};

    struct pdbg_target* target = static_cast<struct pdbg_target *>(i_target.get());
    if (!pdbg_target_get_attribute(target, "ATTR_PHYS_BIN_PATH", 1,
                                   tgt_entitypath_size, tgt_entitypath)) {
        FAPI_ERR("Could not read ATTR_PHYS_BIN_PATH attribute");
        return;
    }

    for (unsigned int i = 0; i < tgt_entitypath_size; ++i)
    {
        i_buffer.emplace_back(tgt_entitypath[i]);
    }
}
}

#endif

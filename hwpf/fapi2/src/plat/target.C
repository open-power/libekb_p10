#include <plat_target.H>
#include <fapi2_target.H>

namespace fapi2
{

// Create specific target
// TARGET_TYPE_SYSTEM
template<>
Target<TARGET_TYPE_SYSTEM, MULTICAST_OR, plat_target_handle_t>::Target()
{
	iv_handle = pdbg_target_root();
}

}

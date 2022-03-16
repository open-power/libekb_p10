#ifndef __FAPI2_PLAT_ERROR__
#define __FAPI2_PLAT_ERROR__

#include "libekb.H"

namespace fapi2
{

/**
 * @brief Used to special handling of hw callout.
 *
 * The defined api is used to modify the callout and guard info
 * specific to each failures with hwcallout
 *
 * @param[in,out] ffdc ffdc data which need to be updated if it is clock failure
 * @param[in] deconfRefTarget indicates whether reference target need to be deconfigured or not
 *
 * @return void
 */
void process_HW_callout(FFDC &ffdc, const bool deconfRefTarget);
}

#endif

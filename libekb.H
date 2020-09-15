#ifndef __LIBEKB_H__
#define __LIBEKB_H__

#include <vector>
#include <string>
#include <utility>

#define LIBEKB_LOG_ERR   0
#define LIBEKB_LOG_INF   1
#define LIBEKB_LOG_IMP   2
#define LIBEKB_LOG_MFG   3
#define LIBEKB_LOG_SCAN  4
#define LIBEKB_LOG_DBG   5

extern "C" {
#include <stdarg.h>

typedef void (*libekb_log_func_t)(void *private_data, const char *fmt, va_list ap);

int libekb_init(void);

void libekb_set_logfunc(libekb_log_func_t fn, void *private_data);
void libekb_set_loglevel(int loglevel);
void libekb_log(int loglevel, const char *fmt, ...);
}

/*
 * @brief To get hardware callout details
 *
 * This is used to get required hardware information to callout
 * if any failures happended.
 */
struct HWCallout
{
    // To get hardware id which is defined in hwp error xml
    std::string hwid;

    // To get defined priority in error xml for callout hardware
    // based on priority
    std::string callout_priority;

    // To get entity path of hardware (target) which is defined
    // in POWER cec device tree
    std::vector<uint8_t> target_entity_path;

    // To get clock position and it used for identify clock position
    // for processor
    uint8_t clkPos;
};

/*
 * @brief To get procedure callout details
 *
 * This is used to get required procedure information to callout
 * if any failures happended.
 */
struct ProcedureCallout
{
    // To get proecdure info which is defined in error xml to callout
    std::string proc_callout;

    // To get defined priority in error xml for callout procedures
    // based on priority
    std::string callout_priority;
};

/*
 * @brief To get target which is required callout, deconfigure and guard
 *
 */
struct CDG_Target
{
    // To get entity path of hardware (target) which is defined
    // in POWER cec device tree
    std::vector<uint8_t> target_entity_path;

    // To indicate callout is require or not
    // true - required
    // false - not required
    bool callout;

    // To get callout priority if callout is true
    std::string callout_priority;

    // To indicate deconfigure is require or not
    // true - required
    // false - not required
    bool deconfigure;

    // To indicate guard hardware (target) is require or not
    // true - required
    // false - not required
    bool guard;

    // To get guard type which is defined in error xml
    std::string guard_type;
};

/*
 * @brief Hardware procedure error info which is defined in error xml
 */
struct HWP_ErrorInfo
{
    // To get hwp return code which is defined in error xml for
    // each error
    std::string rc;

    // To get return code desciption
    std::string rc_desc;

    // To get available FFDCData for particular hwp failures which are
    // defined in error xml
    // pair<variable|attribute_Name, Value>
    std::vector<std::pair<std::string, std::string>> ffdcs_data;

    // To get list of hardware callout info
    std::vector<HWCallout> hwcallouts;

    // To get list of procedure callout info
    std::vector<ProcedureCallout> procedures_callout;

    // TO get list of target to do callout, deconfigure and guard
    std::vector<CDG_Target> cdg_targets;
};

/*
 * @brief Used to get type of ffdc
 */
enum FFDC_TYPE
{
    // No ffdc
    FFDC_TYPE_NONE            = 0,

    // Unsupported ffdc by libekb
    FFDC_TYPE_UNSUPPORTED     = 1,

    // FFDC is created for hardware procedure failures
    FFDC_TYPE_HWP             = 2
};

/*
 * @brief First Failure Data Collection
 */
struct FFDC
{
    // To get FFDC type i.e who is created during execution of hwp
    FFDC_TYPE ffdc_type;

    // To get detailed message which will used for trace
    std::string message;

    // To get detailed hardware procedure ffdc
    // @note use if ffdc_type is HWP
    HWP_ErrorInfo hwp_errorinfo;
};

/*
 * @brief Used to collect first failure data collection
 *
 * This api is used to collect failure data for libekb failures.
 *
 * @param ffdc used to pass buffer to fill FFDC data
 *
 * @retrun void
 */
void libekb_get_ffdc(FFDC& ffdc);

#endif /* __LIBEKB_H__ */

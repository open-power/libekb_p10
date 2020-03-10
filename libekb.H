#ifndef __LIBEKB_H__
#define __LIBEKB_H__

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

#endif /* __LIBEKB_H__ */

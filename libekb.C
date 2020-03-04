extern "C" {
#include <stdio.h>
#include <assert.h>
#include <stdarg.h>

#include <libpdbg.h>
}

#include "plat_trace.H"
#include "utils.H"

#include "libekb.H"

static libekb_log_func_t __libekb_log_fn;
static void *__libekb_log_priv;
static int __libekb_log_level;

struct {
	int libekb_loglevel;
	int pdbg_loglevel;
} libekb_pdbg_log_map[] = {
	{ LIBEKB_LOG_ERR,  PDBG_ERROR },
	{ LIBEKB_LOG_INF,  PDBG_INFO },
	{ LIBEKB_LOG_IMP,  PDBG_DEBUG },
	{ LIBEKB_LOG_MFG,  PDBG_DEBUG },
	{ LIBEKB_LOG_SCAN, PDBG_DEBUG },
	{ LIBEKB_LOG_DBG,  PDBG_DEBUG },
	{ -1, -1 },
};

static int libekb_to_pdbg_loglevel(int libekb_loglevel)
{
	int i;

	for (i=0; libekb_pdbg_log_map[i].libekb_loglevel != -1; i++) {
		if (libekb_pdbg_log_map[i].libekb_loglevel == libekb_loglevel)
			return libekb_pdbg_log_map[i].pdbg_loglevel;
	}

	return PDBG_ERROR;
}

static void libekb_log_default(void *priv, const char *fmt, va_list ap)
{
	vfprintf(stdout, fmt, ap);
}

static void libekb_pdbg_log(int loglevel, const char *fmt, va_list ap)
{
	if (!__libekb_log_fn)
		return;

	__libekb_log_fn(__libekb_log_priv, fmt, ap);
}

int libekb_init(void)
{
	if (!pdbg_targets_init(NULL)) {
		return -1;
	}

	pdbg_set_logfunc(libekb_pdbg_log);
	pdbg_set_loglevel(PDBG_DEBUG);

	libekb_set_logfunc(libekb_log_default, NULL);
	libekb_set_loglevel(LIBEKB_LOG_DBG);

	return 0;
}

void libekb_set_logfunc(libekb_log_func_t fn, void *private_data)
{
	__libekb_log_fn = fn;
	__libekb_log_priv = private_data;
}

void libekb_set_loglevel(int loglevel)
{
	int pdbg_loglevel;

	if (loglevel < LIBEKB_LOG_ERR)
		loglevel = LIBEKB_LOG_ERR;

	if (loglevel > LIBEKB_LOG_DBG)
		loglevel = LIBEKB_LOG_DBG;

	__libekb_log_level = loglevel;

	pdbg_loglevel = libekb_to_pdbg_loglevel(loglevel);
	pdbg_set_loglevel(pdbg_loglevel);
}

void libekb_log(int loglevel, const char *fmt, ...)
{
	va_list ap;

	if (!__libekb_log_fn)
		return;

	if (loglevel > __libekb_log_level)
		return;

	va_start(ap, fmt);
	__libekb_log_fn(__libekb_log_priv, fmt, ap);
	va_end(ap);
}

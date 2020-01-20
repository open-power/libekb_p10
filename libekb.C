extern "C" {
#include <stdio.h>
#include <assert.h>

#include <libpdbg.h>
}

#include "plat_trace.H"
#include "utils.H"

#include "libekb.H"

int libekb_init(void)
{
	if (!pdbg_targets_init(NULL)) {
		return -1;
	}

	return 0;
}

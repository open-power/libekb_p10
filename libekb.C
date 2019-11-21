extern "C" {
#include <stdio.h>
#include <assert.h>

#include <libpdbg.h>
}

#include "plat_trace.H"
#include "utils.H"

#include "libekb.H"

int libekb_init(void *fdt)
{
	assert(fdt);

	plat_set_fdt(fdt);

	if (!pdbg_set_backend(PDBG_BACKEND_KERNEL, NULL))
		return -1;

	if (!pdbg_targets_init(fdt)) {
		return -1;
	}

	return 0;
}

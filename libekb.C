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
	struct pdbg_dtb dtb;

	if (!pdbg_targets_init(NULL)) {
		return -1;
	}

	pdbg_default_dtb(&dtb, NULL);
	plat_set_fdt(dtb.system);

	return 0;
}

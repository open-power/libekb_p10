AM_MAKEFLAGS = --no-print-directory

ACLOCAL_AMFLAGS = -Im4
ARFLAGS = crDPST

EKB = $(srcdir)/ekb

ATTRIB_DIR = $(srcdir)/hwpf/fapi2/include/attributes
ATTRIB_HEADER = \
	$(ATTRIB_DIR)/attribute_ids.H \
	$(ATTRIB_DIR)/attribute_plat_check.H \
	$(ATTRIB_DIR)/fapi2AttrOverrideData.H \
	$(ATTRIB_DIR)/fapi2AttrOverrideEnums.H \
	$(ATTRIB_DIR)/fapi2AttrSyncData.H \
	$(ATTRIB_DIR)/fapi2_chip_ec_feature.H

ATTRIB_XML = \
	$(EKB)/hwpf/fapi2/xml/attribute_info/chip_attributes.xml \
	$(EKB)/hwpf/fapi2/xml/attribute_info/common_attributes.xml \
	$(EKB)/hwpf/fapi2/xml/attribute_info/scratch_attributes.xml \
	$(EKB)/hwpf/fapi2/xml/attribute_info/system_attributes.xml \
	$(EKB)/hwpf/fapi2/xml/attribute_info/unit_attributes.xml \
\
	$(EKB)/chips/p10/procedures/xml/attribute_info/memory_spd_attributes.xml \
	$(EKB)/chips/p10/procedures/xml/attribute_info/p10_bars_attributes.xml \
	$(EKB)/chips/p10/procedures/xml/attribute_info/p10_chip_ec_attributes.xml \
	$(EKB)/chips/p10/procedures/xml/attribute_info/p10_clock_attributes.xml \
	$(EKB)/chips/p10/procedures/xml/attribute_info/p10_freq_attributes.xml \
	$(EKB)/chips/p10/procedures/xml/attribute_info/p10_hcode_image_build_attributes.xml \
	$(EKB)/chips/p10/procedures/xml/attribute_info/p10_io_attributes.xml \
	$(EKB)/chips/p10/procedures/xml/attribute_info/p10_ipl_attributes.xml \
	$(EKB)/chips/p10/procedures/xml/attribute_info/p10_ipl_customize_attributes.xml \
	$(EKB)/chips/p10/procedures/xml/attribute_info/p10_memory_bars_attributes.xml \
	$(EKB)/chips/p10/procedures/xml/attribute_info/p10_nest_attributes.xml \
	$(EKB)/chips/p10/procedures/xml/attribute_info/p10_omi_init.xml \
	$(EKB)/chips/p10/procedures/xml/attribute_info/p10_omi_setup_bars.xml \
	$(EKB)/chips/p10/procedures/xml/attribute_info/p10_pervasive_attributes.xml \
	$(EKB)/chips/p10/procedures/xml/attribute_info/p10_qme_attributes.xml \
	$(EKB)/chips/p10/procedures/xml/attribute_info/p10_runn_attributes.xml \
	$(EKB)/chips/p10/procedures/xml/attribute_info/p10_sbe_load_bootloader_attributes.xml \
	$(EKB)/chips/p10/procedures/xml/attribute_info/pm_hwp_attributes.xml \
	$(EKB)/chips/p10/procedures/xml/attribute_info/pm_plat_attributes.xml \
	$(EKB)/chips/p10/procedures/xml/attribute_info/p10_sbe_attributes.xml


$(ATTRIB_HEADER): $(ATTRIB_XML)
	@$(MKDIR_P) $(ATTRIB_DIR)
	$(EKB)/hwpf/fapi2/tools/parseAttributeInfo.pl --output-dir=$(ATTRIB_DIR) $(ATTRIB_XML)

$(ATTRIB_DIR)/platform_attrs.h: $(ATTRIB_DIR)/attribute_plat_check.H
	@$(MKDIR_P) $(ATTRIB_DIR)
	grep "#ifndef \(.*\)" $< | sed -e "s/#ifndef \(.*\)_\(.*\)/#ifndef \1_\2\n#define \1_\2(id, tgt, val) plat_access_attr_\2(\"\1\", tgt, \&val, sizeof(fapi2::\1_Type))\n#endif/" > $@

ERROR_INFO_XML = $(EKB)/chips/p10/procedures/xml/error_info/*.xml
ERROR_INFO_DIR = $(srcdir)/hwpf/fapi2/include/error_info
ERROR_INFO_HEADER = \
	$(ERROR_INFO_DIR)/hwp_error_info.H \
	$(ERROR_INFO_DIR)/hwp_ffdc_classes.H \
       	$(ERROR_INFO_DIR)/hwp_return_codes.H \
       	$(ERROR_INFO_DIR)/set_sbe_error_funcs.H \
	$(ERROR_INFO_DIR)/set_sbe_error.H

$(ERROR_INFO_HEADER): $(ERROR_INFO_XML)
	@$(MKDIR_P) $(ERROR_INFO_DIR)
	$(EKB)/hwpf/fapi2/tools/parseErrorInfo.pl --output-dir=$(ERROR_INFO_DIR) $(ERROR_INFO_XML)

HWPF_HEADER = \
	$(srcdir)/hwpf/fapi2/include/hwp_executor.H \
	$(srcdir)/hwpf/fapi2/include/plat_attribute_service.H \
	$(srcdir)/hwpf/fapi2/include/return_code_defs.H \
	$(srcdir)/hwpf/fapi2/include/plat/hw_access.H \
	$(srcdir)/hwpf/fapi2/include/plat/i2c_access.H \
	$(srcdir)/hwpf/fapi2/include/plat/mmio_access.H \
	$(srcdir)/hwpf/fapi2/include/plat/multicast.H \
	$(srcdir)/hwpf/fapi2/include/plat/plat_error_scope.H \
	$(srcdir)/hwpf/fapi2/include/plat/plat_hw_access.H \
	$(srcdir)/hwpf/fapi2/include/plat/plat_i2c_access.H \
	$(srcdir)/hwpf/fapi2/include/plat/plat_mbvpd_access.H \
	$(srcdir)/hwpf/fapi2/include/plat/plat_mmio_access.H \
	$(srcdir)/hwpf/fapi2/include/plat/plat_spd_access.H \
	$(srcdir)/hwpf/fapi2/include/plat/plat_target.H \
	$(srcdir)/hwpf/fapi2/include/plat/plat_trace.H \
	$(srcdir)/hwpf/fapi2/include/plat/plat_utils.H \
	$(srcdir)/hwpf/fapi2/include/plat/plat_vpd_access.H \
	$(srcdir)/hwpf/fapi2/include/plat/subroutine_executor.H \
	$(srcdir)/hwpf/fapi2/include/plat/target.H \
	$(srcdir)/hwpf/fapi2/include/plat/vpd_access.H

p10_attributes.db: $(ATTRIB_XML) $(srcdir)/scripts/attribute.py
	$(AM_V_GEN)$(srcdir)/scripts/attribute.py parse $@ $(ATTRIB_XML)

BUILT_SOURCES = \
	$(ATTRIB_HEADER) \
	$(ATTRIB_DIR)/platform_attrs.h \
	$(ERROR_INFO_HEADER) \
	$(ERROR_INFO_DIR)/hwp_error_info.H

if BUILD_DB
data_DATA = p10_attributes.db
endif

include Makefile.proc.am

OPTFLAGS = -Os -O2
LOCALCFLAGS = $(OPTFLAGS) -g -Wall -std=gnu11 $(TARGET_ENDIAN)

# Our own platform include files (hwpf/fapi2/include/plat) shoud
# appear before the ekb ones in this list as we need the compiler to
# choose some of ours. Specifically return_code_defs.H.
LOCALCXXFLAGS = $(OPTFLAGS) -Wall -std=gnu++11 \
		-fpermissive -fno-exceptions -fno-rtti \
		$(TARGET_ENDIAN) \
		-DFAPI2_NO_FFDC \
		-I$(srcdir) \
		-I$(srcdir)/src \
		-I$(srcdir)/hwpf/fapi2/include \
		-I$(srcdir)/hwpf/fapi2/include/attributes \
		-I$(srcdir)/hwpf/fapi2/include/error_info \
		-I$(srcdir)/hwpf/fapi2/include/plat \
		-I$(srcdir)/ekb/hwpf/fapi2/include \
		-I$(srcdir)/ekb/chips/p10/common/include \
		-I$(srcdir)/ekb/chips/common/utils/scomt \
		$(PROC_INCLUDE_CFLAGS)

lib_LTLIBRARIES = libekb.la
nobase_include_HEADERS = \
	$(EKB_HEADER) \
	$(ATTRIB_HEADER) \
	$(ATTRIB_DIR)/platform_attrs.h \
	$(ERROR_INFO_HEADER) \
	$(HWPF_HEADER)
include_HEADERS = libekb.H

libekb_la_SOURCES = $(PROCEDURES) \
		    $(EKB_HEADER) \
		    libekb.C \
		    libekb.H \
		    hwpf/fapi2/src/fapi2_utils.C \
		    hwpf/fapi2/src/plat/plat_utils.C \
		    $(ATTRIB_HEADER) \
		    $(ATTRIB_DIR)/platform_attrs.h \
		    $(ERROR_INFO_HEADER) \
		    $(HWPF_HEADER)

libekb_la_CXXFLAGS = $(LOCALCXXFLAGS)

$(PROCEDURES): $(ATTRIB_HEADER) \
	       $(ATTRIB_DIR)/platform_attrs.h \
	       $(ERROR_INFO_HEADER)

#		   ekb/chips/p10/xip/p10_xip_image.C \
#		   ekb/chips/p10/utils/imageProcs/p10_dd_container.c \
#		   ekb/chips/common/utils/imageProcs/common_ringId.C \
#		   ekb/chips/p10/utils/imageProcs/p10_ringId.C \
#		   ekb/chips/p10/utils/imageProcs/p10_tor.C \
#		   ekb/chips/p10/utils/imageProcs/p10_scan_compression.C \
#		   ekb/chips/p10/utils/p10_putRingUtils.C

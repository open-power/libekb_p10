AC_INIT([libekb],[1.2])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AM_SILENT_RULES([yes])
AC_CONFIG_MACRO_DIR([m4])
AC_SUBST(SONAME_CURRENT, 1)
AC_SUBST(SONAME_REVISION, 0)
AC_SUBST(SONAME_AGE, 0)


case "$host" in
	arm*-*-*) ARCH="arm" ;;
	powerpc64-*-*) ARCH="ppc64" ;;
	powerpc64le-*-*) ARCH="ppc64le" ;;
	x86_64) ARCH="x86_64" ;;
	*) ARCH=$(uname -m) ;;
esac

if test "$ARCH" = "x86_64" ; then
	AC_MSG_NOTICE([Building on X86])
	TARGET_ENDIAN="-DHAVE_LITTLE_ENDIAN"
elif test "$ARCH" = "arm" ; then
	AC_MSG_NOTICE([Building on ARM])
	TARGET_ENDIAN="-DHAVE_LITTLE_ENDIAN"
elif test "$ARCH" = "ppc64" ; then
	AC_MSG_NOTICE([Building on PPC64])
	TARGET_ENDIAN="-DHAVE_BIG_ENDIAN"
elif test "$ARCH" = "ppc64le" ; then
	AC_MSG_NOTICE([Building on PPC64LE])
	TARGET_ENDIAN="-DHAVE_LITTLE_ENDIAN"
else
	AC_MSG_ERROR([libekb cannot be built on $ARCH platform])
fi
AC_SUBST([TARGET_ENDIAN])
AM_CONDITIONAL([BUILD_DB], [test x"$ARCH" != "xarm"])

AC_PROG_CC
AC_PROG_CXX
AM_PROG_AS
AM_PROG_AR
LT_INIT
AC_CHECK_TOOL([OBJCOPY],[objcopy])

AC_CHECK_LIB([pdbg], [pdbg_targets_init], [LIBS="-lpdbg -lfdt $LIBS"], [], [-lfdt])
if test x"$ac_cv_lib_pdbg_pdbg_targets_init" != xyes ; then
	AC_MSG_ERROR([Unable to find pdbg library])
fi

m4_syscmd([make -f Makefile.generate > Makefile.proc.am])

AC_CONFIG_FILES([Makefile])
AC_CONFIG_HEADERS([config.h])
AC_LANG(C++)

AC_OUTPUT

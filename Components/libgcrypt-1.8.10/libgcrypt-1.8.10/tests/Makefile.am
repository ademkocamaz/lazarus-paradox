# Copyright (C) 2001, 2002, 2003, 2005 Free Software Foundation, Inc.
#
# This file is part of Libgcrypt.
#
# Libgcrypt is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as
# published by the Free Software Foundation; either version 2.1 of
# the License, or (at your option) any later version.
#
# Libgcrypt is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA

## Process this file with automake to produce Makefile.in

# Note: Please keep these tests in sync with those in testdrv.c.
# We will eventually switch over to the the new driver but as of now
# the driver is only used for cross-compiling.
tests_bin = \
        version t-secmem mpitests t-sexp t-convert \
	t-mpi-bit t-mpi-point curves t-lock \
	prime basic keygen pubkey hmac hashtest t-kdf keygrip \
	fips186-dsa aeswrap pkcs1v2 random dsa-rfc6979 t-ed25519 t-cv25519

tests_bin_last = benchmark bench-slope

tests_sh = basic-disable-all-hwf

tests_sh_last = hashtest-256g

TESTS = $(tests_bin) $(tests_sh) $(tests_bin_last) $(tests_sh_last)

# Force sequential run of some tests.
bench-slope.log:    benchmark.log
hashtest-256g.log:  bench-slope.log


TESTS_ENVIRONMENT = GCRYPT_IN_REGRESSION_TEST=1


# Need to include ../src in addition to top_srcdir because gcrypt.h is
# a built header.
AM_CPPFLAGS = -I../src -I$(top_srcdir)/src
AM_CFLAGS = $(GPG_ERROR_CFLAGS)
AM_LDFLAGS = -no-install

standard_ldadd = \
	../src/libgcrypt.la $(DL_LIBS) \
        ../compat/libcompat.la

EXTRA_PROGRAMS = testapi pkbench
noinst_PROGRAMS = testdrv $(tests_bin) $(tests_bin_last) \
                  fipsdrv rsacvt genhashdata gchash
noinst_HEADERS = t-common.h

CLEANFILES = testdrv-build

EXTRA_DIST = README rsa-16k.key cavs_tests.sh cavs_driver.pl \
	     pkcs1v2-oaep.h pkcs1v2-pss.h pkcs1v2-v15c.h pkcs1v2-v15s.h \
	     t-ed25519.inp stopwatch.h hashtest-256g.in \
	     sha3-224.h sha3-256.h sha3-384.h sha3-512.h \
	     blake2b.h blake2s.h \
	     basic-disable-all-hwf.in basic_all_hwfeature_combinations.sh

LDADD = $(standard_ldadd) $(GPG_ERROR_LIBS)
t_lock_LDADD = $(standard_ldadd) $(GPG_ERROR_MT_LIBS)
t_lock_CFLAGS = $(GPG_ERROR_MT_CFLAGS)
testdrv_LDADD = $(LDADD_FOR_TESTS_KLUDGE)

# Build a version of the test driver for the build platform.
testdrv-build: testdrv.c
	$(CC_FOR_BUILD) $(CFLAGS_FOR_BUILD) $(LDFLAGS_FOR_BUILD) \
	  $(CPPFLAGS_FOR_BUILD) -DTESTDRV_EXEEXT=\"$(EXEEXT)\" \
          -o $@ $(srcdir)/testdrv.c

if HAVE_W32_SYSTEM
xtestsuite_libs = ../src/.libs/libgcrypt-20.dll \
                  $(prefix)/bin/libgpg-error*-0.dll
xtestsuite_driver = .libs/testdrv.exe
else
xtestsuite_libs = ../src/.libs/libgcrypt.so*
xtestsuite_driver = testdrv
endif

# xcheck uses our new testdrv instead of the automake test runner.
.PHONY: xcheck xtestsuite
xcheck: testdrv$(EXEEXT)
	srcdir=$(srcdir) ./testdrv$(EXEEXT) --verbose

# Make a tarballs with all the tests.
xtestsuite: testdrv$(EXEEXT) testdrv-build $(TESTS)
	+(set -e; \
         name="$(PACKAGE_TARNAME)-tests-$(PACKAGE_VERSION)";\
	 xname="$$name/$(host)" ;\
	 rm -rf $$name; mkdir $$name ; mkdir $$xname ;\
	 cp -L $(xtestsuite_driver) \
           $$(srcdir=$(srcdir) ./testdrv-build --files|sort|uniq) $$xname/ ;\
         cp -P $(xtestsuite_libs) $$xname/ ;\
	 touch $$xname/libgcrypt-standalone-tests ;\
         $(AMTAR) czf "$(PACKAGE_TARNAME)-tests-$(PACKAGE_VERSION)".tar.gz \
             $$name ;\
	 )

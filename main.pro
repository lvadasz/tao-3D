# ******************************************************************************
#  main.pro                                                         Tao project
# ******************************************************************************
# File Description:
# Main Qt build file for Tao
# ******************************************************************************
# This software is property of Taodyne SAS - Confidential
# Ce logiciel est la propriété de Taodyne SAS - Confidentiel
# (C) 2010 Jerome Forissier <jerome@taodyne.com>
# (C) 2010 Christophe de Dinechin <christophe@taodyne.com>
# (C) 2010 Taodyne SAS
# ******************************************************************************

# Usage:
#
# 1. Generate Makefiles with:
#
#   (MacOSX)  qmake -r -spec macx-g++  [options]
#   (Windows) qmake -r -spec win32-g++ [options]
#   (Linux)   qmake -r -spec linux-g++ [options]
#
#   Options:
#
#   DEFINES+=CFG_NOGIT
#     Build without Git support for Tao documents (Git is still used for module
#     update)
#   DEFINES+=CFG_NOSTEREO
#     Build without support for stereoscopic displays
#   DEFINES+=CFG_NOSRCEDIT
#     Build without document source editor
#   DEFINES+=CFG_NOMODPREF
#     Do not include the module page in the preference dialog
#   DEFINES+=CFG_MDI
#     Allow several documents to be open simultaneously (Multiple Document
#     Interface)
#   DEFINES+=NVALGRIND
#     Build libxlr without valgrind hooks. Normally not needed, even for release
#     builds because according to the valgrind documentation, the overhead is
#     negligible.
#   DEFINES+=XLR_GC_LIFO
#     (Debug) Tell the libxlr memory allocator to use a LIFO policy, i.e., do not
#     reuse freed objects immediately. May help valgrind detect more errors.
#   DEFINES+=CFG_NODISPLAYLINK
#     (MacOSX) Do not use a Core Video display link to refresh the display, but
#     a QBasicTimer (like other platforms).
#
#   modules=none
#     Do not build any Tao module
#   modules=all
#     Build all Tao modules (default and optional ones)
#   modules=+my_module
#     Add my_module to default module list
#   modules=-my_module
#     Remove my_modules from default module list
#   modules="all -my_module"
#     Build all modules except my_module
#   modules="none +my_module"
#     Build only my_module
#
# 2. To build:
#
#   $ make             # build everything
#   $ make install     # install Tao locally under ./install/
#   $ make sdk         # copy files needed for module development under ./sdk/
#   $ make clean
#   $ make distclean   # clean + remove Makefiles
#   $ make help        # this text
#
# Note: Packaging scripts are under ./packaging/
# --End Usage

# Include global definitions and rules.
include(main.pri)

TEMPLATE = subdirs
SUBDIRS  = libxlr tao modules ssh_ask_pass tests doc templates packaging

win32:SUBDIRS += detach

tao.depends = libxlr
modules.depends = tao
tests.depends = tao
templates.depends = tao

# The following is artificial, it's just so that we don't start building the
# doc until the main build has actually completed.
doc.depends = tao libxlr modules ssh_ask_pass

sdk.commands = \$(MAKE) -f Makefile.sdk
sdk.depends = FORCE
QMAKE_EXTRA_TARGETS += sdk

# Print the help text above (delimited by lines with 'Usage')
help.commands = @awk \'f{print p} /Usage/&&f++{exit} {p=\$\$0}\' $$_PRO_FILE_
QMAKE_EXTRA_TARGETS += help

# Extend distclean target to also delete directories created by "make install"
# and "make sdk"
distclean_inst_sdk.commands = rm -rf ./install ./sdk
distclean.depends = distclean_inst_sdk
QMAKE_EXTRA_TARGETS += distclean distclean_inst_sdk

# ******************************************************************************
#  monjori.pro                                                      Tao project
# ******************************************************************************
# File Description:
# Project file for document template: Monjori

TEMPLATE = subdirs

include(../templates.pri)

files.path  = $$APPINST/templates/monjori
files.files = template.ini monjori.ddd monjori.png

INSTALLS += files

SIGN_XL_SOURCES = monjori.ddd
include(../sign_template.pri)

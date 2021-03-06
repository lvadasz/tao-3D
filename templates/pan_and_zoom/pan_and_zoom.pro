# ******************************************************************************
#  movie.pro                                                       Tao project
# ******************************************************************************
# File Description:
# Project file for document template: Movie 

TEMPLATE = subdirs

include(../templates.pri)

files.path  = $$APPINST/templates/pan_and_zoom
files.files = template.ini pan_and_zoom.ddd pan_and_zoom.jpg fr.xl

images.path = $$APPINST/templates/pan_and_zoom/images
images.files = images/*

INSTALLS += files images

SIGN_XL_SOURCES = pan_and_zoom.ddd fr.xl
include(../sign_template.pri)

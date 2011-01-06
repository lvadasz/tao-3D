# ******************************************************************************
# tao.pro                                                            Tao project
# ******************************************************************************
# File Description:
# Main Qt build file for Tao
# ******************************************************************************
# This document is released under the GNU General Public License.
# See http://www.gnu.org/copyleft/gpl.html and Matthew 25:22 for details
# (C) 1992-2010 Christophe de Dinechin <christophe@taodyne.com>
# (C) 2010 Catherine Burvelle <cathy@taodyne.com>
# (C) 2010 Lionel Schaffhauser <lionel@taodyne.com>
# (C) 2010 Jerome Forissier <jerome@taodyne.com>
# (C) 2010 Taodyne SAS
# ******************************************************************************

include(../main.pri)

TEMPLATE = app
TARGET = Tao
VERSION = "0.0.3"    # Windows: version is in tao.rc
INC = . \
    include \
    include/tao \
    xlr/xlr/include
DEPENDPATH += $$INC
INCLUDEPATH += $$INC
win32:LIBS += -L../libxlr/release -L../libxlr/debug  # REVISIT
LIBS += -L../libxlr -lxlr
QT += webkit \
    network \
    opengl \
    svg \
    phonon

QMAKE_CFLAGS += -Werror
QMAKE_CXXFLAGS += -Werror
QMAKE_CXXFLAGS_RELEASE += -g \
    \$(CXXFLAGS_\$%)

DEFINES += DEBUG
macx {
    DEFINES += CONFIG_MACOSX
    XLRDIR = Contents/MacOS
    ICON = tao.icns
    QMAKE_INFO_PLIST = Info.plist
    QMAKE_CFLAGS += -mmacosx-version-min=10.5 # Avoid warning with font_file_manager_macos.mm
}
win32 {
    DEFINES += CONFIG_MINGW
    RC_FILE  = tao.rc
}
linux-g++* {
    DEFINES += CONFIG_LINUX
    LIBS += -lXss
}

# Input
HEADERS += widget.h \
    window.h \
    application.h \
    frame.h \
    svg.h \
    texture.h \
    include/tao/coords.h \
    include/tao/coords3d.h \
    color.h \
    gl_keepers.h \
    drawing.h \
    shapes.h \
    text_drawing.h \
    shapes3d.h \
    path3d.h \
    table.h \
    chooser.h \
    binpack.h \
    glyph_cache.h \
    attributes.h \
    lighting.h \
    transforms.h \
    layout.h \
    page_layout.h \
    space_layout.h \
    justification.h \
    justification.hpp \
    apply_changes.h \
    normalize.h \
    activity.h \
    selection.h \
    manipulator.h \
    menuinfo.h \
    widget_surface.h \
    process.h \
    repository.h \
    git_backend.h \
    tao_utf8.h \
    tao_tree.h \
    font.h \
    drag.h \
    pull_from_dialog.h \
    remote_selection_frame.h \
    undo.h \
    clone_dialog.h \
    ansi_textedit.h \
    error_message_dialog.h \
    group_layout.h \
    resource_mgt.h \
    tree_cloning.h \
    font_file_manager.h \
    splash_screen.h \
    branch_selection_combobox.h \
    fetch_dialog.h \
    merge_dialog.h \
    commit_selection_combobox.h \
    history_dialog.h \
    selective_undo_dialog.h \
    documentation.h \
    uri.h \
    open_uri_dialog.h \
    new_document_wizard.h \
    fetch_push_dialog_base.h \
    commit_table_widget.h \
    commit_table_model.h \
    checkout_dialog.h \
    push_dialog.h \
    preferences_dialog.h \
    preferences_pages.h \
    history_playback.h \
    history_frame.h \
    diff_dialog.h \
    diff_highlighter.h \
    module_manager.h \
    portability.h \
    tao_main.h \
    history_playback_tool.h \
    tool_window.h \
    branch_selection_tool.h \
    git_toolbar.h \
    include/tao/module_api.h \
    include/tao/module_info.h \
    module_renderer.h \
    xl_source_edit.h \
    xl_highlighter.h \
    layout_cache.h
SOURCES += tao_main.cpp \
    widget.cpp \
    window.cpp \
    frame.cpp \
    svg.cpp \
    widget_surface.cpp \
    texture.cpp \
    drawing.cpp \
    shapes.cpp \
    text_drawing.cpp \
    shapes3d.cpp \
    path3d.cpp \
    table.cpp \
    chooser.cpp \
    binpack.cpp \
    glyph_cache.cpp \
    attributes.cpp \
    lighting.cpp \
    transforms.cpp \
    layout.cpp \
    page_layout.cpp \
    space_layout.cpp \
    apply_changes.cpp \
    normalize.cpp \
    activity.cpp \
    selection.cpp \
    manipulator.cpp \
    gl_keepers.cpp \
    menuinfo.cpp \
    process.cpp \
    repository.cpp \
    git_backend.cpp \
    application.cpp \
    font.cpp \
    drag.cpp \
    pull_from_dialog.cpp \
    remote_selection_frame.cpp \
    undo.cpp \
    clone_dialog.cpp \
    ansi_textedit.cpp \
    error_message_dialog.cpp \
    group_layout.cpp \
    resource_mgt.cpp \
    tree_cloning.cpp \
    font_file_manager.cpp \
    splash_screen.cpp \
    branch_selection_combobox.cpp \
    fetch_dialog.cpp \
    merge_dialog.cpp \
    commit_selection_combobox.cpp \
    history_dialog.cpp \
    selective_undo_dialog.cpp \
    documentation.cpp \
    uri.cpp \
    open_uri_dialog.cpp \
    new_document_wizard.cpp \
    fetch_push_dialog_base.cpp \
    commit_table_widget.cpp \
    commit_table_model.cpp \
    checkout_dialog.cpp \
    push_dialog.cpp \
    preferences_dialog.cpp \
    preferences_pages.cpp \
    history_playback.cpp \
    history_frame.cpp \
    diff_dialog.cpp \
    diff_highlighter.cpp \
    module_manager.cpp \
    portability.cpp \
    tool_window.cpp \
    branch_selection_tool.cpp \
    history_playback_tool.cpp \
    git_toolbar.cpp \
    module_api_p.cpp \
    module_renderer.cpp \
    xl_source_edit.cpp \
    xl_highlighter.cpp \
    layout_cache.cpp
CXXTBL_SOURCES += graphics.cpp \
    formulas.cpp

!macx {
    HEADERS += GL/glew.h \
        GL/glxew.h \
        GL/wglew.h
    SOURCES += GL/glew.c
    DEFINES += GLEW_STATIC
}
macx {
    OBJECTIVE_SOURCES += font_file_manager_macos.mm
    LIBS += -framework \
        ApplicationServices
}
RESOURCES += tao.qrc

# Others
OTHER_FILES += xl.syntax \
    xl.stylesheet \
    short.stylesheet \
    html.stylesheet \
    debug.stylesheet \
    dbghtml.stylesheet \
    bytecode.stylesheet \
    xlr/xlr/builtins.xl \
    tao.xl \
    tutorial.ddd \
    git.stylesheet \
    traces.tbl \
    graphics.tbl

# Copy the support files to the target directory
xlr_support.path = $${DESTDIR}/$${XLRDIR}
xlr_support.files += $${OTHER_FILES}
QMAKE_BUNDLE_DATA += xlr_support
FORMS += pull_from_dialog.ui \
    remote_selection_frame.ui \
    clone_dialog.ui \
    error_message_dialog.ui \
    merge_dialog.ui \
    history_dialog.ui \
    open_uri_dialog.ui \
    fetch_push_dialog.ui \
    history_frame.ui \
    diff_dialog.ui

# Automatic embedding of Git version
QMAKE_CLEAN += version.h
PRE_TARGETDEPS += version.h
revtarget.target = version.h
revtarget.commands = ./updaterev.sh
revtarget.depends = $$SOURCES \
    $$HEADERS \
    $$FORMS
QMAKE_EXTRA_TARGETS += revtarget

# What to install
xl_files.path  = $$APPINST
xl_files.files = xlr/xlr/builtins.xl \
    tao.xl \
    xl.syntax \
    xl.stylesheet \
    git.stylesheet \
    tutorial.ddd
CONFIG(debug, debug|release):xl_files.files += xlr/xlr/debug.stylesheet
fonts.path  = $$APPINST/fonts
fonts.files = fonts/*
INSTALLS    += xl_files fonts
macx {
  # Workaround install problem: on Mac, the standard way of installing (the 'else'
  # part of this block) starts by recursively deleting $$target.path/Tao.app.
  # This is bad since we have previously stored libraries there :(
  app.path    = $$INSTROOT
  app.extra   = \$(INSTALL_DIR) Tao.app $$INSTROOT
  INSTALLS   += app
} else {
  target.path = $$INSTROOT
  INSTALLS   += target
}

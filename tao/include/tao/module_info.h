#ifndef TAO_MODULE_INFO_H
#define TAO_MODULE_INFO_H
// ****************************************************************************
//  module_info.h                                                  Tao project
// ****************************************************************************
//
//   File Description:
//
//    Public interface to Tao module information
//
//
//
//
//
//
//
// ****************************************************************************
// This document is released under the GNU General Public License.
// See http://www.gnu.org/copyleft/gpl.html and Matthew 25:22 for details
//  (C) 1992-2010 Christophe de Dinechin <christophe@taodyne.com>
//  (C) 2010 Jerome Forissier <jerome@taodyne.com>
//  (C) 2010 Taodyne SAS
// ****************************************************************************

#include <string>

namespace Tao {


struct ModuleInfo
// ------------------------------------------------------------------------
//   Information about a module
// ------------------------------------------------------------------------
{
    ModuleInfo() {}
    ModuleInfo(std::string id, std::string path) : id(id), path(path) {}

    std::string id;
    std::string path;
    std::string name;
    std::string desc;
    std::string icon;
    std::string ver;
    std::string author;
    std::string website;
    std::string importName;
};

}

#endif // TAO_MODULE_INFO_H
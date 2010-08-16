#ifndef PUBLISH_TO_DIALOG_H
#define PUBLISH_TO_DIALOG_H
// ****************************************************************************
//  publish_to_dialog.h                                            Tao project
// ****************************************************************************
//
//   File Description:
//
//    The class to display the "Publish to" dialog box
//
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
//  (C) 2010 Jerome Forissier <jerome@taodyne.com>
//  (C) 2010 Taodyne SAS
// ****************************************************************************

#include "fetch_push_dialog_base.h"

namespace Tao {

class PublishToDialog : public FetchPushDialogBase
{
    Q_OBJECT

public:
    PublishToDialog(Repository *repo, QWidget *parent = 0);

public slots:
    virtual void accept();
};

}

#endif // PUBLISH_TO_DIALOG_H
#ifndef BRANCH_SELECTION_COMBOBOX_H
#define BRANCH_SELECTION_COMBOBOX_H

// ****************************************************************************
//  branch_selection_combobox.h                                    Tao project
// ****************************************************************************
//
//   File Description:
//
//    A class to display a combobox that allows users to:
//      * select an existing repository branch
//      * rename a branch
//      * delete a branch
//      * create a new branch
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

#include <QComboBox>
#include <QWidget>
#include <QString>

namespace Tao {

struct Repository;

class BranchSelectionComboBox : public QComboBox
{
    Q_OBJECT

public:
    BranchSelectionComboBox(QWidget *parent = 0);

public:
    QString branch();
    void    refresh();

public slots:
    void    setRepository(Repository *repo, QString preferredBranch = "");

signals:
    void    noneSelected();
    void    branchSelected(QString name);

protected slots:
    void    on_activated(QString selected);

private:
    bool    populate();
    bool    populateAndSelect(QString sel = "", bool doEmit = true);
    QString addNewBranch();
    QString renameBranch();

private:
    enum ComboItemKind
    // ------------------------------------------------------------------------
    //    Values to identify each entry of the name combo box
    // ------------------------------------------------------------------------
    {
        CIK_None,   // The "<None>" item
        CIK_Name,   // Any valid branch name
        CIK_AddNew, // The "New branch..." item
        CIK_Delete, // The "Delete <name>" item
        CIK_Rename, // The "Rename <name>" item
    };

private:
    Repository * repo;
    QString      prevSelected;
};

}

#endif // BRANCH_SELECTION_COMBOBOX_H
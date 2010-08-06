// ****************************************************************************
//  table.cpp                       (C) 1992-2009 Christophe de Dinechin (ddd) 
//                                                                 XL2 project 
// ****************************************************************************
// 
//   File Description:
// 
//    Table-style layout for drawable elements
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
// ****************************************************************************
// * File       : $RCSFile$
// * Revision   : $Revision$
// * Date       : $Date$
// ****************************************************************************

#include "table.h"
#include "layout.h"
#include "graphics.h"
#include "runtime.h"
#include "widget.h"

TAO_BEGIN

Table::Table(Widget *w, Real_p x, Real_p y, uint r, uint c)
// ----------------------------------------------------------------------------
//    Constructor
// ----------------------------------------------------------------------------
    : Layout(w), x(x), y(y), rows(r), columns(c), row(0), column(0),
      margins(0,0,5,5), columnWidth(), rowHeight(),
      fill(NULL), border(NULL)
{}


Table::~Table()
// ----------------------------------------------------------------------------
//   Destructor
// ----------------------------------------------------------------------------
{
    std::vector<Drawing *>::iterator it;
    for (it = items.begin(); it != items.end(); it++)
        delete *it;
    items.clear();
}


void Table::Draw(Layout *where)
// ----------------------------------------------------------------------------
//   Draw all the table items
// ----------------------------------------------------------------------------
{
    Compute(where);

    coord   cellX, cellY, cellW, cellH;
    coord   x0 = double(x) - bounds.Width()/2;
    coord   y0 = double(y) - bounds.Height()/2;
    coord   px = bounds.lower.x + x0;
    coord   py = bounds.upper.y + y0;
    uint    r, c;
    Widget *widget = where->Display();
    std::vector<Drawing *>::iterator i = items.begin();
    TreeList::iterator fillI = cellFill.begin();
    TreeList::iterator borderI = cellBorder.begin();
    XL::LocalSave<Table *> saveTable(widget->table, this);
    Tree *fillCode = fill;
    Tree *borderCode = border;

    for (r = 0; r < rows; r++)
    {
        px = bounds.lower.x + x0;
        if (r < rowHeight.size())
            py -= rowHeight[r];
        py -= margins.Height();
        row = r;
        for (c = 0; c < columns; c++)
        {
            bool atEnd = i == items.end();

            Drawing *d = atEnd ? NULL : *i++;
            Vector3 pos(px - margins.lower.x + columnOffset[c],
                        py - margins.lower.y + rowOffset[r], 0);
            column = c;

            cellW = columnWidth[c] + margins.Width();
            cellH = rowHeight[r] + margins.Height();
            cellX = px + cellW/2;
            cellY = py + cellH/2;
            cellBox = Box(cellX-cellW/2, cellY-cellH/2, cellW, cellH);

            if (Layout *cell = dynamic_cast<Layout *>(d))
            {
                XL::LocalSave<Point3> zeroOffset(offset, Point3());
                Box3 bb = d->Space(this);
                pos.x += (columnWidth[c]-bb.Width() ) * cell->alongX.centering;
                pos.y += (rowHeight[r]-bb.Height()) * cell->alongY.centering;
            }

            if (fillI != cellFill.end())
                fillCode = *fillI++;
            if (fillCode)
                widget->drawTree(this, fillCode);
            if (d)
            {
                XL::LocalSave<Point3> saveOffset(offset, pos + where->offset);
                d->Draw(this);
            }
            if (borderI != cellBorder.end())
                borderCode = *borderI++;
            if (borderCode)
                widget->drawTree(this, borderCode);

            if (c < columnWidth.size())
                px += columnWidth[c];
            px += margins.Width();
        }
    }
}


void Table::DrawSelection(Layout *where)
// ----------------------------------------------------------------------------
//   Draw the selection for all the table items
// ----------------------------------------------------------------------------
{
    Compute(where);

    coord   cellX, cellY, cellW, cellH;
    coord   x0 = double(x) - bounds.Width()/2;
    coord   y0 = double(y) - bounds.Height()/2;
    coord   px = bounds.lower.x + x0;
    coord   py = bounds.upper.y + y0;
    uint    r, c;
    Widget *widget = where->Display();
    std::vector<Drawing *>::iterator i = items.begin();
    XL::LocalSave<Table *> saveTable(widget->table, this);

    for (r = 0; r < rows; r++)
    {
        px = bounds.lower.x + x0;
        if (r < rowHeight.size())
            py -= rowHeight[r];
        py -= margins.Height();
        row = r;
        for (c = 0; c < columns; c++)
        {
            bool atEnd = i == items.end();

            Drawing *d = atEnd ? NULL : *i++;
            Vector3 pos(px - margins.lower.x + columnOffset[c],
                        py - margins.lower.y + rowOffset[r], 0);
            column = c;

            cellW = columnWidth[c] + margins.Width();
            cellH = rowHeight[r] + margins.Height();
            cellX = px + cellW/2;
            cellY = py + cellH/2;
            cellBox = Box(cellX-cellW/2, cellY-cellH/2, cellW, cellH);

            if (Layout *cell = dynamic_cast<Layout *>(d))
            {
                XL::LocalSave<Point3> zeroOffset(offset, Point3());
                Box3 bb = d->Space(this);
                pos.x += (columnWidth[c]-bb.Width() ) * cell->alongX.centering;
                pos.y += (rowHeight[r]-bb.Height()) * cell->alongY.centering;
            }

            if (d)
            {
                XL::LocalSave<Point3> saveOffset(offset, where->offset + pos);
                d->DrawSelection(this);
            }

            if (c < columnWidth.size())
                px += columnWidth[c];
            px += margins.Width();
        }
    }
}


void Table::Identify(Layout *where)
// ----------------------------------------------------------------------------
//   Identify all the table items
// ----------------------------------------------------------------------------
{
    Compute(where);

    coord   cellX, cellY, cellW, cellH;
    coord   x0 = double(x) - bounds.Width()/2;
    coord   y0 = double(y) - bounds.Height()/2;
    coord   px = bounds.lower.x + x0;
    coord   py = bounds.upper.y + y0;
    uint    r, c;
    Widget *widget = where->Display();
    std::vector<Drawing *>::iterator i = items.begin();
    XL::LocalSave<Table *> saveTable(widget->table, this);

    for (r = 0; r < rows; r++)
    {
        px = bounds.lower.x + x0;
        if (r < rowHeight.size())
            py -= rowHeight[r];
        py -= margins.Height();
        row = r;
        for (c = 0; c < columns; c++)
        {
            bool atEnd = i == items.end();

            Drawing *d = atEnd ? NULL : *i++;
            Vector3 pos(px - margins.lower.x + columnOffset[c],
                        py - margins.lower.y + rowOffset[r], 0);
            column = c;

            cellW = columnWidth[c] + margins.Width();
            cellH = rowHeight[r] + margins.Height();
            cellX = px + cellW/2;
            cellY = py + cellH/2;
            cellBox = Box(cellX-cellW/2, cellY-cellH/2, cellW, cellH);

            if (Layout *cell = dynamic_cast<Layout *>(d))
            {
                XL::LocalSave<Point3> zeroOffset(offset, Point3());
                Box3 bb = d->Space(this);
                pos.x += (columnWidth[c]-bb.Width() ) * cell->alongX.centering;
                pos.y += (rowHeight[r]-bb.Height()) * cell->alongY.centering;
            }

            if (d)
            {
                XL::LocalSave<Point3> saveOffset(offset, where->offset + pos);
                d->Identify(this);
            }

            if (c < columnWidth.size())
                px += columnWidth[c];
            px += margins.Width();
        }
    }
}


Box3 Table::Bounds(Layout *where)
// ----------------------------------------------------------------------------
//   Compute the bounds of the table
// ----------------------------------------------------------------------------
{
    Compute(where);
    Vector3 boff(-bounds.Width()/2, -bounds.Height()/2, 0);
    return bounds + where->offset + boff;
}


Box3 Table::Space(Layout *where)
// ----------------------------------------------------------------------------
//   Compute the bounds of the table
// ----------------------------------------------------------------------------
{
    return Bounds(where);
}


void Table::Add(Drawing *d)
// ----------------------------------------------------------------------------
//    Add an element to a table
// ----------------------------------------------------------------------------
{
    Layout::Add(d);
    cellFill.push_back(fill);
    cellBorder.push_back(border);
    columnWidth.clear();
    rowHeight.clear();
}


void Table::Compute(Layout *where)
// ----------------------------------------------------------------------------
//   Compute column widths and row heights
// ----------------------------------------------------------------------------
{
    Inherit(where);
    if (columnWidth.size() == columns && rowHeight.size() == rows)
        return;

    uint r, c;
    std::vector<Drawing *>::iterator i = items.begin();
    std::vector<Box3> rowBB, colBB;

    // Compute the actual column width and heights
    columnWidth.clear();
    columnWidth.resize(columns);
    colBB.resize(columns);
    columnOffset.clear();
    columnOffset.resize(columns);

    rowHeight.clear();
    rowHeight.resize(rows);
    rowBB.resize(rows);
    rowOffset.clear();
    rowOffset.resize(rows);

    // Set initial (empty) bounding box for rows and columns
    for (r = 0; r < rows; r++)
        rowBB[r] |= Point3(0,0,0);
    for (c = 0; c < columns; c++)
        colBB[c] |= Point3(0,0,0);

    // Compute actual row and column bounding box
    for (r = 0; r < rows; r++)
    {
        if (i == items.end())
            break;
        for (c = 0; c < columns; c++)
        {
            if (i == items.end())
                break;
            Drawing *d = *i++;
            Inherit(where);
            XL::LocalSave<Point3> zeroOffset(offset, Point3());
            Box3 bb = d->Space(this);
            double lowX = colBB[c].lower.x;
            double lowY = rowBB[r].lower.y;
            if (lowX < 0)
                columnOffset[c] = -lowX;
            if (lowY < 0)
                rowOffset[r] = -lowY;
            rowBB[r] |= bb;
            colBB[c] |= bb;
        }
    }

    // Compute the bounding box
    Box3 bb;
    bb |= Point3(0,0,0);
    for (c = 0; c < columns; c++)
    {
        columnWidth[c] = colBB[c].Width();
        bb.upper.x += columnWidth[c] + margins.Width();
    }
    for (r = 0; r < rows; r++)
    {
        rowHeight[r] = rowBB[r].Height();
        bb.upper.y += rowHeight[r] + margins.Height();
    }
    bounds = bb;

    // Restore original state for the caller
    Inherit(where);
}

TAO_END
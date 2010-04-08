// ****************************************************************************
//  shapes.cpp                                                     Tao project
// ****************************************************************************
//
//   File Description:
//
//     Drawing of elementary geometry shapes on a 2D layout
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
//  (C) 1992-2010 Christophe de Dinechin <christophe@taodyne.com>
//  (C) 2010 Lionel Schaffhauser <lionel@taodyne.com>
//  (C) 2010 Taodyne SAS
// ****************************************************************************

#include "shapes.h"
#include "layout.h"
#include "attributes.h"
#include "path3d.h"
#include <GL/glew.h>
#include <QtOpenGL>
#include <QPainterPath>

TAO_BEGIN

// ============================================================================
//
//    Common utilities for drawing shapes
//
// ============================================================================

bool Shape::setTexture(Layout *where)
// ----------------------------------------------------------------------------
//   Get the texture from the layout
// ----------------------------------------------------------------------------
{
    if (where->fillTexture)
    {
        glBindTexture(GL_TEXTURE_2D, where->fillTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_MULTISAMPLE);
    }
    else
    {
        glDisable(GL_TEXTURE_2D);
    }

    return where->fillTexture ? true : false;
}


bool Shape::setFillColor(Layout *where)
// ----------------------------------------------------------------------------
//    Set the fill color and texture according to the layout attributes
// ----------------------------------------------------------------------------
{
    // Check if we have a non-transparent fill color
    if (where)
    {
        Color &color = where->fillColor;
        if (color.alpha > 0.0)
        {
            glColor4f(color.red, color.green, color.blue, color.alpha);
            where->PolygonOffset();
            return true;
        }
    }
    return false;
}


bool Shape::setLineColor(Layout *where)
// ----------------------------------------------------------------------------
//    Set the outline color according to the layout attributes
// ----------------------------------------------------------------------------
{
    // Check if we have a non-transparent outline color
    if (where)
    {
        Color &color = where->lineColor;
        if (color.alpha > 0.0)
        {
            glColor4f(color.red, color.green, color.blue, color.alpha);
            where->PolygonOffset();
            return true;
        }
    }
    return false;
}


void Shape::Draw(GraphicPath &path)
// ----------------------------------------------------------------------------
//    Draw the shape in a path
// ----------------------------------------------------------------------------
{
    (void) path;
}


void Shape::Draw(Layout *where)
// ----------------------------------------------------------------------------
//    Draw the shape using a path
// ----------------------------------------------------------------------------
{
    GraphicPath path;
    Draw(path);
    path.Draw(where);
}



// ============================================================================
//
//   Shape drawing routines
//
// ============================================================================

void Rectangle::Draw(GraphicPath &path)
// ----------------------------------------------------------------------------
//   Draw a rectangle
// ----------------------------------------------------------------------------
{
    path.moveTo(Point3(bounds.lower.x, bounds.lower.y, 0));
    path.lineTo(Point3(bounds.upper.x, bounds.lower.y, 0));
    path.lineTo(Point3(bounds.upper.x, bounds.upper.y, 0));
    path.lineTo(Point3(bounds.lower.x, bounds.upper.y, 0));
    path.close();
}


void IsoscelesTriangle::Draw(GraphicPath &path)
// ----------------------------------------------------------------------------
//   Draw an isosceles triangle
// ----------------------------------------------------------------------------
{
    path.moveTo(Point3(bounds.lower.x, bounds.lower.y, 0));
    path.lineTo(Point3(bounds.upper.x, bounds.lower.y, 0));
    path.lineTo(Point3((bounds.upper.x + bounds.lower.x)/2, bounds.upper.y, 0));
    path.close();
}


void RightTriangle::Draw(GraphicPath &path)
// ----------------------------------------------------------------------------
//   Draw a right triangle
// ----------------------------------------------------------------------------
{
    path.moveTo(Point3(bounds.lower.x, bounds.lower.y, 0));
    path.lineTo(Point3(bounds.upper.x, bounds.lower.y, 0));
    path.lineTo(Point3(bounds.lower.x, bounds.upper.y, 0));
    path.close();
}


void RoundedRectangle::Draw(GraphicPath &path)
// ----------------------------------------------------------------------------
//   Draw a rounded rectangle
// ----------------------------------------------------------------------------
{
    QPainterPath qt;
    if (radiusX > bounds.Width() / 2)
        radiusX = bounds.Width() / 2;
    if (radiusY > bounds.Height() / 2)
        radiusY = bounds.Height() / 2;
    qt.addRoundedRect(bounds.lower.x, bounds.lower.y,
                      bounds.Width(), bounds.Height(),
                      radiusX, radiusY);
    path.addQtPath(qt);
}


void Ellipse::Draw(GraphicPath &path)
// ----------------------------------------------------------------------------
//   Draw an ellipse inside the bounds
// ----------------------------------------------------------------------------
{
    QPainterPath qt;
    qt.addEllipse(bounds.lower.x, bounds.lower.y,
                  bounds.Width(), bounds.Height());
    path.addQtPath(qt);
}


void EllipseArc::Draw(GraphicPath &path)
// ----------------------------------------------------------------------------
//    Draw an arc of ellipse
// ----------------------------------------------------------------------------
{
    QPainterPath qt;
    Point center = bounds.Center();
    qt.moveTo(center.x, center.y);
    qt.arcTo(bounds.lower.x, bounds.lower.y,
             bounds.Width(), bounds.Height(),
             start, sweep);
    qt.closeSubpath();
    path.addQtPath(qt);
}


void Arrow::Draw(Layout *where)
// ----------------------------------------------------------------------------
//    We need correct tesselation
// ----------------------------------------------------------------------------
{
    GraphicPath path;
    Draw(path);
    setTexture(where);
    if (setFillColor(where))
        path.Draw(where, GL_POLYGON, GLU_TESS_WINDING_POSITIVE);
    if (setLineColor(where))
        // REVISIT: If lines is thick, use a QPainterPathStroker
        path.Draw(where, GL_LINE_STRIP);
}


void Arrow::Draw(GraphicPath &path)
// ----------------------------------------------------------------------------
//   Draw an arrow
// ----------------------------------------------------------------------------
{
    coord aax, aay;
    int sw = bounds.Width() > 0? 1: -1;
    int sh = bounds.Height() > 0? 1: -1;

    if (ax > sw*bounds.Width()) 
        aax = bounds.Width();
    else
        aax = sw*ax;
    
    if (ax < 0.0) 
        aax = 0.0;

    if (ary > 1.0) 
        aay = bounds.Height();
    else
        aay = ary*bounds.Height();
    
    if (ary < 0.0) 
        aay = 0.0;
 
    coord x0 = bounds.Left();
    coord x1 = bounds.Right();
    coord xa1 = x1 - aax;

    coord y0 = bounds.Bottom();
    coord yc = (bounds.Bottom() + bounds.Top())/2;
    coord y1 = bounds.Top();
    coord ya0 = yc - aay/2;
    coord ya1 = yc + aay/2;

    path.moveTo(Point3(x0,  ya0, 0));
    path.lineTo(Point3(xa1, ya0, 0));
    path.lineTo(Point3(xa1, y0,  0));
    path.lineTo(Point3(x1,  yc,  0));
    path.lineTo(Point3(xa1, y1,  0));
    path.lineTo(Point3(xa1, ya1, 0));
    path.lineTo(Point3(x0,  ya1, 0));
    path.close();
}


void DoubleArrow::Draw(Layout *where)
// ----------------------------------------------------------------------------
//    We need correct tesselation
// ----------------------------------------------------------------------------
{
    GraphicPath path;
    Draw(path);
    setTexture(where);
    if (setFillColor(where))
        path.Draw(where, GL_POLYGON, GLU_TESS_WINDING_POSITIVE);
    if (setLineColor(where))
        // REVISIT: If lines is thick, use a QPainterPathStroker
        path.Draw(where, GL_LINE_STRIP);
}


void DoubleArrow::Draw(GraphicPath &path)
// ----------------------------------------------------------------------------
//   Draw a double arrow
// ----------------------------------------------------------------------------
{
    coord x0 = bounds.lower.x;
    coord x1 = bounds.upper.x;
    coord xa0 = x0 + a.x;
    coord xa1 = x1 - a.x;

    coord y0 = bounds.lower.y;
    coord yc = (bounds.lower.y + bounds.upper.y)/2;
    coord y1 = bounds.upper.y;
    coord ya0 = yc - a.y/2;
    coord ya1 = yc + a.y/2;

    path.moveTo(Point3(x0,  yc,  0));
    path.lineTo(Point3(xa0, y0,  0));
    path.lineTo(Point3(xa0, ya0, 0));
    path.lineTo(Point3(xa1, ya0, 0));
    path.lineTo(Point3(xa1, y0,  0));
    path.lineTo(Point3(x1,  yc,  0));
    path.lineTo(Point3(xa1, y1,  0));
    path.lineTo(Point3(xa1, ya1, 0));
    path.lineTo(Point3(xa0, ya1, 0));
    path.lineTo(Point3(xa0, y1,  0));
    path.close();
}


void StarPolygon::Draw(Layout *where)
// ----------------------------------------------------------------------------
//    We need correct tesselation when q != 1
// ----------------------------------------------------------------------------
{
    GraphicPath path;
    Draw(path);
    if (q == 1)
    {
        // Regular polygon, no need to tesselate
        path.Draw(where);
    }
    else
    {
        setTexture(where);
        if (setFillColor(where))
            path.Draw(where, GL_POLYGON,
                      q > 0 ? GLU_TESS_WINDING_POSITIVE : GLU_TESS_WINDING_ODD);
        if (setLineColor(where))
            // REVISIT: If lines is thick, use a QPainterPathStroker
            path.Draw(where, GL_LINE_STRIP);
    }
}


void StarPolygon::Draw(GraphicPath &path)
// ----------------------------------------------------------------------------
//   Draw a regular polygon or a star
// ----------------------------------------------------------------------------
{
    scale  w1     = bounds.Width()/2;
    scale  h1     = bounds.Height()/2;
    Point3 center = bounds.Center();
    coord  cx     = center.x;
    coord  cy     = center.y;

    if (q > 0)
    {
        scale  R_r    = cos(q * M_PI/p) / cos((q-1) * M_PI/p);
        scale  w2     = w1 * R_r;
        scale  h2     = h1 * R_r;
        double a      = 0;
        double da     = M_PI/p;

        for (int i = 0; i < p; i++)
        {
            double x1 = cx + w1 * sin(a);
            double y1 = cy + h1 * cos(a);
            a += da;
            double x2 = cx + w2 * sin(a);
            double y2 = cy + h2 * cos(a);
            a += da;

            if (i)
                path.lineTo(Point3(x1, y1, 0));
            else
                path.moveTo(Point3(x1, y1, 0));
            
            path.lineTo(Point3(x2, y2, 0));

            
        }
        path.close();
    }
    else
    {
        double a      = 0;
        double da     = 2 * M_PI * q / p;
        
        for (int i = 0; i <= p; i++)
        {
            if (2*i == p)
            {
                path.close();
                a += da/2;
            }

            double x1 = cx + w1 * sin(a);
            double y1 = cy + h1 * cos(a);
            a += da;

            if (i == 0 || 2*i == p)
            {
                path.moveTo(Point3(x1, y1, 0));
            }
            else
            {
                path.lineTo(Point3(x1, y1, 0));
            }
        }
        path.close();
    }
}


void Star::Draw(Layout *where)
// ----------------------------------------------------------------------------
//    We need correct tesselation when radius ratio != 1
// ----------------------------------------------------------------------------
{
    GraphicPath path;
    Draw(path);
    if (r == 1.0)
    {
        // Regular polygon, no need to tesselate
        path.Draw(where);
    }
    else
    {
        setTexture(where);
        if (setFillColor(where))
            path.Draw(where, GL_POLYGON, GLU_TESS_WINDING_POSITIVE);
        if (setLineColor(where))
            // REVISIT: If lines is thick, use a QPainterPathStroker
            path.Draw(where, GL_LINE_STRIP);
    }
}


void Star::Draw(GraphicPath &path)
// ----------------------------------------------------------------------------
//   Draw a regular polygon or a star
// ----------------------------------------------------------------------------
{
    scale  w1     = bounds.Width()/2;
    scale  h1     = bounds.Height()/2;
    Point3 center = bounds.Center();
    coord  cx     = center.x;
    coord  cy     = center.y;

    scale  w2     = w1 * r;
    scale  h2     = h1 * r;
    double a      = 0;
    double da     = M_PI/p;

    for (int i = 0; i < p; i++)
    {
        double x1 = cx + w1 * sin(a);
        double y1 = cy + h1 * cos(a);
        a += da;
        double x2 = cx + w2 * sin(a);
        double y2 = cy + h2 * cos(a);
        a += da;

        if (i)
            path.lineTo(Point3(x1, y1, 0));
        else
            path.moveTo(Point3(x1, y1, 0));
        
        path.lineTo(Point3(x2, y2, 0));

    }
    path.close();
}


TAO_END

#ifndef LIGHTING_H
#define LIGHTING_H
// ****************************************************************************
//  lighting.h                                                      Tao project
// ****************************************************************************
//
//   File Description:
//
//     Lighting attributes
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

#include "drawing.h"
#include "color.h"
#include "attributes.h"
#include <vector>
#include <GL/glew.h>
#include <QGLShaderProgram>

TAO_BEGIN

struct Lighting : Attribute
// ----------------------------------------------------------------------------
//   Base class for all lighting attributes
// ----------------------------------------------------------------------------
{
    Lighting(): Attribute() {}
};


struct LightId : Lighting
// ----------------------------------------------------------------------------
//   Select which light we are using
// ----------------------------------------------------------------------------
{
    LightId(uint id, bool enable): Lighting(), id(id), enable(enable) {}
    virtual void Draw(Layout *where);
    uint id;
    bool enable;
};


struct Light : Lighting
// ----------------------------------------------------------------------------
//   Light attribute (glLight)
// ----------------------------------------------------------------------------
{
    typedef std::vector<GLfloat> Arguments;
    Light(GLenum f, Arguments &a): Lighting(), function(f), args(a) {}
    Light(GLenum f, GLfloat a): Lighting(), function(f), args()
    {
        args.push_back(a);
    }
    Light(GLenum f, GLfloat x, GLfloat y, GLfloat z):
        Lighting(), function(f), args()
    {
        args.push_back(x);
        args.push_back(y);
        args.push_back(z);
    }
    Light(GLenum f, GLfloat r, GLfloat g, GLfloat b, GLfloat a):
        Lighting(), function(f), args()
    {
        args.push_back(r);
        args.push_back(g);
        args.push_back(b);
        args.push_back(a);
    }
    virtual void Draw(Layout *where);
    GLenum      function;
    Arguments   args;
};


struct Material : Light
// ----------------------------------------------------------------------------
//   Material attribute (glMaterial)
// ----------------------------------------------------------------------------
{
    Material(GLenum fc, GLenum f, GLfloat a): Light(f, a), face(fc) {}
    Material(GLenum fc, GLenum f, GLfloat a, GLfloat b, GLfloat c, GLfloat d)
        : Light(f, a, b, c, d), face(fc) {}
    virtual void Draw(Layout *where);
    GLenum      face;
};


struct ShaderProgramInfo : XL::Info
// ----------------------------------------------------------------------------
//   Hold info associated to a tree
// ----------------------------------------------------------------------------
{
    ShaderProgramInfo(QGLShaderProgram *program): program(program) {}
    ~ShaderProgramInfo() { delete program; }
    typedef QGLShaderProgram *data_t;
    operator data_t() { return program; }
    QGLShaderProgram *program;
};


struct ShaderProgram : Lighting
// ----------------------------------------------------------------------------
//   Activate a shader program
// ----------------------------------------------------------------------------
{
    ShaderProgram(QGLShaderProgram *program): program(program) {}
    virtual void Draw(Layout *where);
    QGLShaderProgram *program;
};

TAO_END

#endif // LIGHTING_H

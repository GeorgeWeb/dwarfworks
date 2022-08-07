// begin PCH
#include "dwpch.h"
// end PCH

#include "Platform/OpenGL/OpenGLDriver.h"

using namespace Dwarfworks;
using namespace OpenGL;

inline void Driver::CreateVertexArrays(GLsizei n, GLuint *arrays)
{
    glGenVertexArrays(n, arrays);
}

inline void Driver::EnableVertexArrayAttrib(GLuint vaobj, GLuint index)
{
    (void) (vaobj);
    glEnableVertexAttribArray(index);
}

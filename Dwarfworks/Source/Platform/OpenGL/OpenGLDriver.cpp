// begin PCH
#include "dwpch.h"
// end PCH

#include "OpenGLDriver.h"

using namespace Dwarfworks;

namespace OpenGL
{
#if !PLATFORM_MACOS
inline void Driver::CreateVertexArrays(GLsizei n, GLuint *arrays)
{
    glCreateVertexArrays(n, arrays);
}
#endif

#if !PLATFORM_MACOS
inline void Driver::EnableVertexArrayAttrib(GLuint vaobj, GLuint index)
{
    glEnableVertexArrayAttrib(vaobj, index);
}
#endif

} // namespace OpenGL

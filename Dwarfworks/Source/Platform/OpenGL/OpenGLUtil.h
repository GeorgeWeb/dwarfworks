#ifndef PLATFORM_OPENGL_OPENGL_UTIL_H
#define PLATFORM_OPENGL_OPENGL_UTIL_H

#include "OpenGLError.h"

#include "glad/glad.h"

namespace Dwarfworks
{
namespace OpenGL
{
    /**
     * @brief Create a Vertex Array objects.
     * Returns n previously unused vertex array object names in arrays, each representing a new vertex array object
     * initialized to the default state.
     * @param n Number of vertex array objects to create.
     * @param arrays Specifies an array in which names of the new vertex array objects are stored.
     */
    inline void CreateVertexArrays(GLsizei n, GLuint *arrays)
    {
#if PLATFORM_MACOS
        glGenVertexArrays(n, arrays);
#else
        glCreateVertexArrays(n, arrays);
#endif
    }

    /**
     * @brief Enable or disable a generic vertex attribute array.
     *
     * @param vaobj Specifies the name of the vertex array object for glDisableVertexArrayAttrib and
     * glEnableVertexArrayAttrib functions.
     * @param index Specifies the index of the generic vertex attribute to be enabled or disabled.
     */
    inline void EnableVertexArrayAttrib(GLuint vaobj, GLuint index)
    {
#if PLATFORM_MACOS
        (void) (vaobj);
        glEnableVertexAttribArray(index); // egh ?
#else
        glEnableVertexArrayAttrib(vaobj, index);
#endif
    }

} // namespace OpenGL
}; // namespace Dwarfworks

#endif // PLATFORM_OPENGL_OPENGL_UTIL_H

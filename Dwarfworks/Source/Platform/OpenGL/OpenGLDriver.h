#pragma once

#include "Dwarfworks/Core/Core.h"

#include "glad/glad.h"

namespace Dwarfworks
{
namespace OpenGL
{
    /**
     * @brief Abstraction of the OpenGL Driver
     *
     */
    class ENGINE_API Driver final
    {
      public:
        Driver();

        /**
         * @brief Create a Vertex Array objects.
         * Returns n previously unused vertex array object names in arrays, each representing a new vertex array object
         * initialized to the default state.
         * @param n Number of vertex array objects to create.
         * @param arrays Specifies an array in which names of the new vertex array objects are stored.
         */
        void CreateVertexArrays(GLsizei n, GLuint *arrays);

        /**
         * @brief Enable or disable a generic vertex attribute array.
         *
         * @param vaobj Specifies the name of the vertex array object for glDisableVertexArrayAttrib and
         * glEnableVertexArrayAttrib functions.
         * @param index Specifies the index of the generic vertex attribute to be enabled or disabled.
         */
        void EnableVertexArrayAttrib(GLuint vaobj, GLuint index);

      private:
    };

} // namespace OpenGL
} // namespace Dwarfworks

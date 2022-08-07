// begin PCH
#include "dwpch.h"
// end PCH

#include "OpenGLLoader.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

using namespace Dwarfworks;

GLADOpenGLLoader::GLADOpenGLLoader() : m_LoadProcess {reinterpret_cast<GLADloadproc>(glfwGetProcAddress)}
{
}

GLADOpenGLLoader::~GLADOpenGLLoader()
{
    // reset the function pointer
    m_LoadProcess = nullptr;
}

bool GLADOpenGLLoader::LoadOpenGLFunctions()
{
    // auto loadProc = reinterpret_cast<GLADloadproc>(glfwGetProcAddress);
    bool success = gladLoadGLLoader(m_LoadProcess);

    // If the glfw loader fails or is unavailable, try using glad's built-in loader.
    if (!success)
    {
        success = gladLoadGL();
    }

    return success;
}
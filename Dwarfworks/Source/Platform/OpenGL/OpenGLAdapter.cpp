// begin PCH
#include "dwpch.h"
// end PCH

#include "OpenGLAdapter.h"

using namespace Dwarfworks;

OpenGLAdapter::OpenGLAdapter() : m_OpenGLDriver {CreateScope<OpenGL::Driver>()}
{
}

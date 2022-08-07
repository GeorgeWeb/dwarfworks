// begin PCH
#include "dwpch.h"
// end PCH

#include "MacWindow.h"

#include "Dwarfworks/Core/Core.h"

// events
#include "Dwarfworks/Event/ApplicationEvent.h"
#include "Dwarfworks/Event/KeyEvent.h"
#include "Dwarfworks/Event/MouseEvent.h"

// renderer context
#include "Dwarfworks/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_COCOA
DISABLE_WARNING_PUSH
DISABLE_WARNING_MULTIPLE_METHOD_NAMES
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"
DISABLE_WARNING_POP

using namespace Dwarfworks;

void MacWindow::OnUpdate()
{
    glfwPollEvents();
    // TODO: In the future, change the API so this is called like:
    // m_Context->GetSwapChain().Present();
    m_Context->FlipSwapChainBuffers();
}

std::uint32_t MacWindow::GetWidth() const
{
    return m_Data.Width;
}

std::uint32_t MacWindow::GetHeight() const
{
    return m_Data.Height;
}

void MacWindow::SetVSyncEnabled(bool enable)
{
    // set the interval synchronization time for a frame to be
    // called for rendering depending on v-sync being enabled
    const int32_t interval = enable ? 1 : 0;
    glfwSwapInterval(interval);
    m_Data.VSync = enable;
}

bool MacWindow::IsVSyncEnabled() const
{
    return m_Data.VSync;
}

void* MacWindow::Get() const
{
    return m_Window;
}

void MacWindow::SetEventCallback(const EventCallbackFn& callback)
{
    m_Data.EventCallback = callback;
}

// *** //

class MacWindow::MacWindowImpl final
{
};

MacWindow::MacWindow(const WindowProps& props) : m_Pimpl(CreateScope<MacWindowImpl>())
{
    Initialize(props);
}

MacWindow::~MacWindow()
{
    Shutdown();
    // release the native handle
    // MacWindowImpl::~MacWindowImpl();
};

void* MacWindow::GetNative() const
{
    // return m_Pimpl->GetNative();
    return nullptr;
}

// Temp.
static bool s_IsGLFWInitialized {false};

void MacWindow::Initialize(const WindowProps& props)
{
    m_Data.Title  = props.Title;
    m_Data.Width  = props.Width;
    m_Data.Height = props.Height;
    DW_CORE_INFO("Window {0} ({1}, {2})", props.Title, props.Width, props.Height);

    if (!s_IsGLFWInitialized)
    {
        // TODO: glfwTerminate() on system shutdown (not on window close!)
        auto success = glfwInit();
        DW_CORE_ASSERT(success, "Could not initialize GLFW!");
        // temporary until abstracted away in a GLFWErrorCallback function
        glfwSetErrorCallback(
            [](int error, const char* description) { DW_CORE_ERROR("GLFW Error ({0}): {1}", error, description); });
        s_IsGLFWInitialized = true;
    }

    switch (Renderer::GetAPI())
    {
        default: DW_CORE_ASSERT(false, "Unknown RendererAPI!"); break;
        case RendererAPI::API::OpenGL: {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MinimumSupportedOpenGLVersionMajor);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MinimumSupportedOpenGLVersionMinor);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef DW_DEBUG
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
        }
        break;
    }

    // create the window
    const auto width  = static_cast<int>(props.Width);
    const auto height = static_cast<int>(props.Height);
    const auto title  = m_Data.Title.c_str();
    m_Window          = glfwCreateWindow(width, height, title, nullptr, nullptr);
    // set the native handle
    // m_Pimpl->Initialize(m_Window);

    m_Context = GraphicsContext::Create(m_Window);
    m_Context->Initialize();

    // set the custom window data to the GLFWwindow
    glfwSetWindowUserPointer(m_Window, &m_Data);
    m_Data.VSync = false; // v-sync is OFF by default

    // ------------------
    // set GLFW callbacks
    // ------------------

    // window close
    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
        auto& data  = *(static_cast<WindowState*>(glfwGetWindowUserPointer(window)));
        auto  event = WindowCloseEvent {};
        // set the window close callback
        data.EventCallback(event);
    });

    // window resize
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
        auto& data = *(static_cast<WindowState*>(glfwGetWindowUserPointer(window)));

        const auto wndWidth  = static_cast<uint32_t>(width);
        const auto wndHeight = static_cast<uint32_t>(height);

        // update the window dimensions
        data.Width  = wndWidth;
        data.Height = wndHeight;

        // set the window size callback
        auto event = WindowResizeEvent(wndWidth, wndHeight);
        DW_CORE_WARN("Window: {0} x {1}", wndWidth, wndHeight);
        data.EventCallback(event);
    });

    // make sure the viewport matches the new window dimensions
    glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
        auto& data = *(static_cast<WindowState*>(glfwGetWindowUserPointer(window)));

        const auto fbWidth  = static_cast<uint32_t>(width);
        const auto fbHeight = static_cast<uint32_t>(height);

        // set the framebuffer size callback
        auto event = FramebufferResizeEvent(fbWidth, fbHeight);
        DW_CORE_WARN("Framebuffer: {0} x {1}", fbWidth, fbHeight);
        data.EventCallback(event);
    });

    // key action
    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        auto& data = *(static_cast<WindowState*>(glfwGetWindowUserPointer(window)));

        switch (action)
        {
            case GLFW_PRESS: {
                auto event = KeyPressedEvent(key, 0);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE: {
                auto event = KeyReleasedEvent(key);
                data.EventCallback(event);
                break;
            }
            case GLFW_REPEAT: {
                // temporarily set to 1, but should consider extracting the exact number
                // of repeats in future iteration of this function
                auto event = KeyPressedEvent(key, 1);
                data.EventCallback(event);
                break;
            }
        }
    });

    // character type action
    glfwSetCharCallback(m_Window, [](GLFWwindow* window, uint32_t charater) {
        auto& data  = *(static_cast<WindowState*>(glfwGetWindowUserPointer(window)));
        auto  event = KeyTypedEvent(charater);
        data.EventCallback(event);
    });

    // mouse button action
    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
        auto& data = *(static_cast<WindowState*>(glfwGetWindowUserPointer(window)));

        switch (action)
        {
            case GLFW_PRESS: {
                auto event = MouseButtonPressedEvent(button);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE: {
                auto event = MouseButtonReleasedEvent(button);
                data.EventCallback(event);
                break;
            }
        }
    });

    // mouse scroll action
    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
        auto& data = *(static_cast<WindowState*>(glfwGetWindowUserPointer(window)));

        const auto xOffsetFloat = static_cast<float>(xOffset);
        const auto yOffsetFloat = static_cast<float>(yOffset);
        auto       event        = MouseScrolledEvent(xOffsetFloat, yOffsetFloat);
        data.EventCallback(event);
    });

    // mouse cursor move action
    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
        auto& data = *(static_cast<WindowState*>(glfwGetWindowUserPointer(window)));

        const auto xPosFloat = static_cast<float>(xPos);
        const auto yPosFloat = static_cast<float>(yPos);
        auto       event     = MouseMovedEvent(xPosFloat, yPosFloat);
        data.EventCallback(event);
    });
}

void MacWindow::Shutdown()
{
    // release the gfx context
    if (m_Context)
        delete m_Context;

    // release the glfw window
    glfwDestroyWindow(m_Window);
}

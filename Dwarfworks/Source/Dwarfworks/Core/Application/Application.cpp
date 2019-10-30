// begin PCH
#include "dwpch.h"
// end PCH

#include "Application.h"
#include "Dwarfworks/Core/Input/Input.h"
#include "Dwarfworks/Graphics/Renderer.h"
#include "Dwarfworks/Math/Math.h"

#ifdef ENABLE_VISUAL_TESTING
#include "Tests/OpenGLClearColorTest.h"
#include "Tests/OpenGLInfoTest.h"
#include "Tests/OpenGLRenderTriangleTest.h"
#include "Tests/ShaderManagerTest.h"
#include "Tests/TestMenu.h"
#endif

namespace Dwarfworks {

std::atomic<Application*> Application::s_Instance = nullptr;
std::mutex Application::s_Mutex;

Application::Application() : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) {
  DW_CORE_ASSERT(!s_Instance, "Instance of Application already exists!");
  // set the single instance to point to the existing application
  s_Instance = this;

  // Create the Application Window
  auto window = IWindow::Create();
  m_Window.reset(std::move(window));
  // Set the Window event handling for this Application
  m_Window->SetEventCallback(DW_BIND_EVENT_FN(Application::OnEvent));

  // Create Application DebugUI Layer
  m_DebugUILayer = CreateRef<DebugUILayer>();
  PushOverlay(m_DebugUILayer.get());

#ifdef ENABLE_VISUAL_TESTING
  // Create Test Menu
  INIT_TEST_MENU(m_TestMenu, m_CurrentTest);
  // Register Tests
  REGISTER_TEST(Tests::OpenGLInfoTest, "OpenGL Info", m_TestMenu);
  REGISTER_TEST(Tests::OpenGLClearColorTest, "OpenGL Clear Color", m_TestMenu);
  REGISTER_TEST(Tests::OpenGLRenderTriangleTest, "Render Triangle", m_TestMenu);
  REGISTER_TEST(Tests::ShaderManagerTest, "Shader manager", m_TestMenu);
  // Set Current Test Layer to Test Menu
  m_CurrentTest = m_TestMenu.get();
  m_LayerStack.PushLayer(m_CurrentTest);
#endif

  // --------------------------------------- //
  // Buffers (Vertex, Index) and VertexArray //
  // --------------------------------------- //

  // vertex array
  m_VertexArray.reset(VertexArray::Create());

  // vertices
  float vertices[3 * 7] = {
      -0.5f, -0.5f, 0.0f,      // vertex: bottom left
      0.8f, 0.2f, 0.8f, 1.0f,  // color: bottom left
                               // ---
      0.5f, -0.5f, 0.0f,       // vertex: bottom right
      0.2f, 0.3f, 0.8f, 1.0f,  // color: bottom right
                               // ---
      0.0f, 0.5f, 0.0f,        // vertex: top
      0.8f, 0.8f, 0.2f, 1.0f   // color: top
  };

  // vertex buffer
  uint32_t vbSize = sizeof(vertices);
  Ref<VertexBuffer> vertexBuffer;
  vertexBuffer.reset(VertexBuffer::Create(vertices, vbSize));

  // vertex buffer layout
  BufferLayout vbLayout = {{ShaderDataType::Float3, "a_Position"},
                           {ShaderDataType::Float4, "a_Color"}};

  vertexBuffer->SetLayout(vbLayout);
  m_VertexArray->AddVertexBuffer(vertexBuffer);

  // indices
  uint32_t indices[3] = {0, 1, 2};

  // index buffer
  const auto ibCount = sizeof(indices) / sizeof(uint32_t);
  Ref<IndexBuffer> indexBuffer;
  indexBuffer.reset(IndexBuffer::Create(indices, ibCount));

  m_VertexArray->SetIndexBuffer(indexBuffer);

  // square vertex array
  m_SquareVA.reset(VertexArray::Create());

  // square vertices
  float squareVertices[3 * 4] = {
      -0.75f, -0.75f, 0.0f,  // bottom left
      0.75f,  -0.75f, 0.0f,  // bottom right
      0.75f,  0.75f,  0.0f,  // top right
      -0.75f, 0.75f,  0.0f   // top left
  };

  uint32_t squareVbSize = sizeof(squareVertices);
  Ref<VertexBuffer> squareVB;
  squareVB.reset(VertexBuffer::Create(squareVertices, squareVbSize));

  // vertex buffer layout
  BufferLayout squareVbLayout = {{ShaderDataType::Float3, "a_Position"}};

  squareVB->SetLayout(squareVbLayout);
  m_SquareVA->AddVertexBuffer(squareVB);

  // square indices
  uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};

  // square index buffer
  const auto squareIbCount = sizeof(squareIndices) / sizeof(uint32_t);
  Ref<IndexBuffer> squareIB;
  squareIB.reset(IndexBuffer::Create(squareIndices, squareIbCount));

  m_SquareVA->SetIndexBuffer(squareIB);

  // --------------------------- //
  // Shaders and Shader Programs //
  // --------------------------- //

  // vertex shader
  std::string vertSrc = R"(
	#version 330 core

	layout (location = 0) in vec3 a_Position;
	layout (location = 1) in vec4 a_Color;

	uniform mat4 u_ViewProjection;

	out vec4 v_Color;

	void main() {
	  v_Color = a_Color;

	  vec4 vertexPosition = vec4(a_Position, 1.0);
	  gl_Position = u_ViewProjection * vertexPosition;
	}
  )";

  // fragment shader
  std::string fragSrc = R"(
	#version 330 core
	layout(location = 0) out vec4 color;
   
	in vec4 v_Color;

	void main() {
	  color = v_Color;
	}
  )";

  // shader program
  m_Shader.reset(new Shader(vertSrc, fragSrc));

  // blue square vertex shader
  std::string blueVertSrc = R"(
	#version 330 core

	layout (location = 0) in vec3 a_Position;

	uniform mat4 u_ViewProjection;

	void main() {
	  vec4 vertexPosition = vec4(a_Position, 1.0);
	  gl_Position = u_ViewProjection * vertexPosition;
	}
  )";

  // blue square fragment shader
  std::string blueFragSrc = R"(
	#version 330 core
	layout(location = 0) out vec4 color;

	void main() {
	  color = vec4(0.2, 0.3, 0.7, 1.0);
	}
  )";

  // blue square shader program
  m_BlueShader.reset(new Shader(blueVertSrc, blueFragSrc));
}

#ifdef ENABLE_VISUAL_TESTING
Application::~Application() = default;  // TODO: cleanup
#else
Application::~Application() = default;
#endif

void Application::Run() {
  // the main loop
  while (IsRunning()) {
    // lower level render commands

    // clear color (and depth) buffer
    RenderCommand::SetClearColor({0.2f, 0.2f, 0.2f, 1.0f});
    RenderCommand::Clear();

    // higher level renderer calls

    m_Camera.SetPosition({0.5f, 0.5f, 0.0f});
    m_Camera.SetRotation(45.0f);

    // render scene
    Renderer::BeginScene(m_Camera);

    Renderer::Submit(m_BlueShader, m_SquareVA);
    Renderer::Submit(m_Shader, m_VertexArray);

    Renderer::EndScene();

    // TODO:
    // Renderer::Flush();

    // update layers
#ifdef ENABLE_VISUAL_TESTING
    if (m_CurrentTest) {
      m_CurrentTest->OnUpdate();
    }
    for (auto appLayer : m_LayerStack) {
      if (appLayer != m_CurrentTest && appLayer != m_TestMenu.get()) {
        appLayer->OnUpdate();
      }
    }
#else
    for (auto appLayer : m_LayerStack) {
      appLayer->OnUpdate();
    }
#endif

    // render layers
#ifdef ENABLE_VISUAL_TESTING
    if (m_CurrentTest) {
      m_CurrentTest->OnRender();
    }
    for (auto appLayer : m_LayerStack) {
      if (appLayer != m_CurrentTest && appLayer != m_TestMenu.get()) {
        appLayer->OnRender();
      }
    }
#else
    for (auto appLayer : m_LayerStack) {
      appLayer->OnRender();
    }
#endif

    // render DebugUI layer
    m_DebugUILayer->Begin();
#ifdef ENABLE_VISUAL_TESTING
    if (m_CurrentTest) {
      if (m_CurrentTest != m_TestMenu.get() && ImGui::Button("<< Back")) {
        delete m_CurrentTest;
        m_CurrentTest = m_TestMenu.get();
      }
      m_CurrentTest->OnDebugUIRender();
    }
    for (auto appLayer : m_LayerStack) {
      if (appLayer != m_CurrentTest && appLayer != m_TestMenu.get()) {
        appLayer->OnDebugUIRender();
      }
    }
#else
    for (auto appLayer : m_LayerStack) {
      appLayer->OnDebugUIRender();
    }
#endif
    m_DebugUILayer->End();

    // update window
    m_Window->OnUpdate();
  }
}  // namespace Dwarfworks

void Application::OnEvent(Event& event) {
  // listen for upcoming events and register them
  EventManager eventManager(event);
  // dispatch the event and call its function if it matches the registered event
  eventManager.Dispatch<WindowCloseEvent>(
      DW_BIND_EVENT_FN(Application::OnWindowClosed));

  // call events in reverse order from most top to most bottom layer
#ifdef ENABLE_VISUAL_TESTING
  std::for_each(m_LayerStack.rbegin(), m_LayerStack.rend(), [&](auto layer) {
    if (layer != m_CurrentTest && layer != m_TestMenu.get()) {
      layer->OnEvent(event);
      if (event.IsHandled) return;
    }
  });
#else
  std::for_each(m_LayerStack.rbegin(), m_LayerStack.rend(), [&](auto layer) {
    layer->OnEvent(event);
    if (event.IsHandled) return;
  });
#endif
}

void Application::PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); }

void Application::PushOverlay(Layer* layer) { m_LayerStack.PushOverlay(layer); }

bool Application::OnWindowClosed(WindowCloseEvent& event) {
#ifdef ENABLE_VISUAL_TESTING
  // free Test layers
  if (m_CurrentTest) {
    // TODO: Describe!
    m_LayerStack.PopLayer(m_CurrentTest);
    // TODO: Describe!
    if (m_CurrentTest != m_TestMenu.get()) {
      delete m_CurrentTest;
    }
    m_CurrentTest = nullptr;
    // TODO: Describe!
    m_LayerStack.PopLayer(m_TestMenu.get());
  }
#endif
  // free DebugUI Overlay
  m_LayerStack.PopOverlay(m_DebugUILayer.get());
  // stop running
  m_IsRunning = false;
  return true;
}

}  // namespace Dwarfworks

#ifndef PLAYGROUND_LAYER_H_
#define PLAYGROUND_LAYER_H_

#include <Dwarfworks.h>

#include "imgui/imgui.h"

// Temporary
#include "Platform/OpenGL/OpenGLShader.h"

class Playground : public Dwarfworks::Layer {
 public:
  Playground()
      : Layer("Playground"), m_CameraController(1280.0f / 720.0f, true) {
    // --------------------------------------- //
    // Buffers (Vertex, Index) and VertexArray //
    // --------------------------------------- //

	// BEGIN TRIANGLE

    // vertex array
    m_TriangleVA = Dwarfworks::VertexArray::Create();

    // vertices
    float triangleVertices[3 * 7] = {
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
    uint32_t tiangleVbSize = sizeof(triangleVertices);
    Dwarfworks::Ref<Dwarfworks::VertexBuffer> triangleVB;
	triangleVB = Dwarfworks::VertexBuffer::Create(triangleVertices, tiangleVbSize);

    // vertex buffer layout
#define USE_INIT_LIST_LAYOUT 0
#if USE_INIT_LIST_LAYOUT
    Dwarfworks::BufferLayout vbLayout = {
        {Dwarfworks::ShaderDataType::Float3, "a_Position"},
        {Dwarfworks::ShaderDataType::Float4, "a_Color"}};
#else
	Dwarfworks::BufferLayout vbLayout;
	vbLayout.Append<Dwarfworks::ShaderDataType::Float3>("a_Position");
	vbLayout.Append<Dwarfworks::ShaderDataType::Float4>("a_Color");
#endif

	triangleVB->SetLayout(vbLayout);
    m_TriangleVA->AddVertexBuffer(triangleVB);

    // indices
    uint32_t triangleIndices[3] = {0, 1, 2};

    // index buffer
    const auto ibCount = sizeof(triangleIndices) / sizeof(uint32_t);
    Dwarfworks::Ref<Dwarfworks::IndexBuffer> triangleIB;
	triangleIB = Dwarfworks::IndexBuffer::Create(triangleIndices, ibCount);

    m_TriangleVA->SetIndexBuffer(triangleIB);

	// END OF TRIANGLE

	// BEGIN SQUARE

    // square vertex array
    m_SquareVA = Dwarfworks::VertexArray::Create();

    // square vertices
    float squareVertices[3 * 4] = {
        -0.75f, -0.75f, 0.0f,  // bottom left
        0.75f,  -0.75f, 0.0f,  // bottom right
        0.75f,  0.75f,  0.0f,  // top right
        -0.75f, 0.75f,  0.0f   // top left
    };

    uint32_t squareVbSize = sizeof(squareVertices);
    Dwarfworks::Ref<Dwarfworks::VertexBuffer> squareVB;
    squareVB = Dwarfworks::VertexBuffer::Create(squareVertices, squareVbSize);

    // vertex buffer layout
    Dwarfworks::BufferLayout squareVbLayout = {
        {Dwarfworks::ShaderDataType::Float3, "a_Position"}};

    squareVB->SetLayout(squareVbLayout);
    m_SquareVA->AddVertexBuffer(squareVB);

    // square indices
    uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};

    // square index buffer
    const auto squareIbCount = sizeof(squareIndices) / sizeof(uint32_t);
    Dwarfworks::Ref<Dwarfworks::IndexBuffer> squareIB;
    squareIB = Dwarfworks::IndexBuffer::Create(squareIndices, squareIbCount);

    m_SquareVA->SetIndexBuffer(squareIB);

	// END OF SQUARE

	// BEGIN CUBE

	// square vertex array
	m_CubeVA = Dwarfworks::VertexArray::Create();

	// square vertices
	float cubeVertices[3 * 8] = {
		// front
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		// back
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f
	};

	uint32_t cubeVbSize = sizeof(cubeVertices);
	Dwarfworks::Ref<Dwarfworks::VertexBuffer> cubeVB;
	cubeVB = Dwarfworks::VertexBuffer::Create(cubeVertices, cubeVbSize);

	// vertex buffer layout
	Dwarfworks::BufferLayout cubeVbLayout = {
		{Dwarfworks::ShaderDataType::Float3, "a_Position"}};

	cubeVB->SetLayout(cubeVbLayout);
	m_CubeVA->AddVertexBuffer(cubeVB);

	// square indices
	uint32_t cubeIndices[3 * 12] = { 
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	// square index buffer
	const auto cubeIbCount = sizeof(cubeIndices) / sizeof(uint32_t);
	Dwarfworks::Ref<Dwarfworks::IndexBuffer> cubeIB;
	cubeIB = Dwarfworks::IndexBuffer::Create(cubeIndices, cubeIbCount);

	m_CubeVA->SetIndexBuffer(cubeIB);

	// END OF CUBE

    // --------------------------- //
    // Shaders and Shader Programs //
    // --------------------------- //

    // vertex shader
    std::string vertSrc = R"(
	#version 330 core

	layout (location = 0) in vec3 a_Position;
	layout (location = 1) in vec4 a_Color;

	uniform mat4 u_ViewProjection;
	uniform mat4 u_Transform;

	out vec4 v_Color;

	void main() {
	  v_Color = a_Color;

	  vec4 vertexPosition = vec4(a_Position, 1.0);
	  gl_Position = u_ViewProjection * u_Transform * vertexPosition;
	}
  )";

    // fragment shader
    std::string fragSrc = R"(
	#version 330 core

	layout(location = 0) out vec4 color;
   
	in vec4 v_Color;

	void main()
	{
	  color = v_Color;
	}
  )";

    // shader program
    m_Shader = Dwarfworks::Shader::Create(vertSrc, fragSrc);

    // blue square vertex shader
    std::string flatColorVertSrc = R"(
	#version 330 core

	layout (location = 0) in vec3 a_Position;

	uniform mat4 u_ViewProjection;
	uniform mat4 u_Transform;

	void main()
	{
	  vec4 vertexPosition = vec4(a_Position, 1.0);
	  gl_Position = u_ViewProjection * u_Transform * vertexPosition;
	}
  )";

    // blue square fragment shader
    std::string flatColorFragSrc = R"(
	#version 330 core

	layout(location = 0) out vec4 color;

	uniform vec3 u_Color;

	void main()
	{
	  color = vec4(u_Color, 1.0);
	}
  )";

    // blue square shader program
    m_FlatColorShader = Dwarfworks::Shader::Create(flatColorVertSrc, flatColorFragSrc);
  }

  virtual void OnUpdate(Dwarfworks::Timestep deltaTime) override {
    // clear buffers (TODO: Move to a function that takes care of this!)
    Dwarfworks::RenderCommand::SetClearColor({0.2f, 0.2f, 0.2f, 1.0f});
    Dwarfworks::RenderCommand::Clear();

    // Poll user input
    // ---------------

    // Animate objects
    // ---------------

    // update camera
    m_CameraController.OnUpdate(deltaTime);
  }

  virtual void OnRender() override {
    // render scene
    Dwarfworks::Renderer::BeginScene(m_CameraController.GetCamera());

    static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

    std::dynamic_pointer_cast<Dwarfworks::OpenGLShader>(m_FlatColorShader)
        ->Bind();
    std::dynamic_pointer_cast<Dwarfworks::OpenGLShader>(m_FlatColorShader)
        ->UploadUniformFloat3("u_Color", m_SquareColor);

    // Square Grid
    for (int y = 0; y < 20; y++) {
      for (int x = 0; x < 20; x++) {
        glm::vec3 pos(x * .175f, y * .175f, 0.0f);
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
        Dwarfworks::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
      }
    }

	// Cube
	std::dynamic_pointer_cast<Dwarfworks::OpenGLShader>(m_FlatColorShader)
		->Bind();
	std::dynamic_pointer_cast<Dwarfworks::OpenGLShader>(m_FlatColorShader)
		->UploadUniformFloat3("u_Color", m_CubeColor);
	Dwarfworks::Renderer::Submit(m_FlatColorShader, m_CubeVA);

    // Triangle
	std::dynamic_pointer_cast<Dwarfworks::OpenGLShader>(m_Shader)
		->Bind();
    Dwarfworks::Renderer::Submit(m_Shader, m_TriangleVA);

    Dwarfworks::Renderer::EndScene();
  }

  virtual void OnDebugUIRender() override {
    ImGui::Begin((GetName() + " editor").c_str());
    ImGui::Text("Add stuff here ...");
    ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
  }

  virtual void OnEvent(Dwarfworks::Event& event) override {
    // handle camera events
    m_CameraController.OnEvent(event);

    Dwarfworks::EventManager eventManager(event);
    eventManager.Dispatch<Dwarfworks::KeyPressedEvent>([&](auto& keyEvent) {
      switch (keyEvent.GetKeyCode()) {
          // exit layer
        case Dwarfworks::KeyCodes::ESCAPE: {
          DW_INFO("Pressed 'ESC'");
          break;
        }
        default:
          DW_TRACE("Pressed {0}", static_cast<char>(keyEvent.GetKeyCode()));
          break;
      }
      return false;  // blocking, true for non-blocking
    });
  }

 private:
  Dwarfworks::Ref<Dwarfworks::Shader> m_Shader;
  Dwarfworks::Ref<Dwarfworks::Shader> m_FlatColorShader;

  Dwarfworks::Ref<Dwarfworks::VertexArray> m_TriangleVA;
  Dwarfworks::Ref<Dwarfworks::VertexArray> m_SquareVA;
  Dwarfworks::Ref<Dwarfworks::VertexArray> m_CubeVA;

  Dwarfworks::OrthographicCameraController m_CameraController;

  glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.7f};
  glm::vec3 m_CubeColor = { 0.3f, 0.6f, 0.3f };
};

#endif  // PLAYGROUND_LAYER_H_

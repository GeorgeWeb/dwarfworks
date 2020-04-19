#ifndef PLAYGROUND_LAYER_H_
#define PLAYGROUND_LAYER_H_

// Engine
#include <Dwarfworks.h>
// Application entry point
#include <Dwarfworks/Core/EntryPoint.h>

// Debug gui
#include <imgui/imgui.h>

// Temporary (should get abstracted out of here cause
#include <Platform/OpenGL/OpenGLShader.h>

// For testing purposes
#define ASPECT_RATIO_16_10 1
#define BUFFERLAYOUT_INITLIST_CONSTRUCT 0

class Playground : public Dwarfworks::Layer {
#if ASPECT_RATIO_16_10
	static constexpr auto s_ScreenWidth = 1440u;
	static constexpr auto s_ScreenHeight = 900u;
#else
	static constexpr auto s_ScreenWidth = 1366u;
	static constexpr auto s_ScreenHeight = 768u;
#endif
	static constexpr auto s_AspectRatio = static_cast<float>(s_ScreenWidth) / s_ScreenHeight;
	static constexpr auto s_CanRotate = true;
 public:
  Playground()
      : Layer("Playground"),
		m_CameraController(s_AspectRatio, s_CanRotate) {
    // --------------------------------------- //
    // Buffers (Vertex, Index) and VertexArray //
    // --------------------------------------- //

	// BEGIN TRIANGLE

    // vertex array
    m_TriangleVA = Dwarfworks::VertexArray::Create();

    // vertices
    float triangleVertices[3 * (3 + 4)] = {
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
#if BUFFERLAYOUT_INITLIST_CONSTRUCT
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
#if BUFFERLAYOUT_INITLIST_CONSTRUCT
    Dwarfworks::BufferLayout squareVbLayout = {
        {Dwarfworks::ShaderDataType::Float3, "a_Position"}};
#else
	Dwarfworks::BufferLayout squareVbLayout;
	squareVbLayout.Append<Dwarfworks::ShaderDataType::Float3>("a_Position");
#endif

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
		-0.75f, -0.75f,  0.75f,
		 0.75f, -0.75f,  0.75f,
		 0.75f,  0.75f,  0.75f,
		-0.75f,  0.75f,  0.75f,
		// back
		-0.75f, -0.75f, -0.75f,
		 0.75f, -0.75f, -0.75f,
		 0.75f,  0.75f, -0.75f,
		-0.75f,  0.75f, -0.75f
	};

	uint32_t cubeVbSize = sizeof(cubeVertices);
	Dwarfworks::Ref<Dwarfworks::VertexBuffer> cubeVB;
	cubeVB = Dwarfworks::VertexBuffer::Create(cubeVertices, cubeVbSize);

	// vertex buffer layout
#if BUFFERLAYOUT_INITLIST_CONSTRUCT
	Dwarfworks::BufferLayout cubeVbLayout = {
		{Dwarfworks::ShaderDataType::Float3, "a_Position"}};
#else
	Dwarfworks::BufferLayout cubeVbLayout;
	cubeVbLayout.Append<Dwarfworks::ShaderDataType::Float3>("a_Position");
#endif

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

	uniform vec4 u_Color;

	void main()
	{
	  color = vec4(u_Color);
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

	glm::mat4 transform(1.0f); // identity default

    std::dynamic_pointer_cast<Dwarfworks::OpenGLShader>(m_FlatColorShader)
        ->Bind();
    // Square Grid
    for (int y = 0; y < 20; y++) {
      for (int x = 0; x < 20; x++) {
        auto squarePos = glm::vec3(x * 0.175f, y * 0.175f, 0.0f);
		auto squareScale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
        transform = glm::translate(glm::mat4(1.0f), squarePos) * squareScale;
		std::dynamic_pointer_cast<Dwarfworks::OpenGLShader>(m_FlatColorShader)
			->UploadUniformFloat4("u_Color", (x % 2 == 0) ? m_BlueColor : m_RedColor);
        Dwarfworks::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
      }
    }

	// Cube
	transform = glm::translate(glm::mat4(1.0f), glm::vec3(-1.25f, 0.75f, 0.0f));
	std::dynamic_pointer_cast<Dwarfworks::OpenGLShader>(m_FlatColorShader)
		->Bind();
	std::dynamic_pointer_cast<Dwarfworks::OpenGLShader>(m_FlatColorShader)
		->UploadUniformFloat4("u_Color", m_GreenColor);
	Dwarfworks::Renderer::Submit(m_FlatColorShader, m_CubeVA, transform);

    // Triangle
	transform = glm::translate(glm::mat4(1.0f), glm::vec3(-1.25f, 2.5f, 0.0f));
	std::dynamic_pointer_cast<Dwarfworks::OpenGLShader>(m_Shader)
		->Bind();
    Dwarfworks::Renderer::Submit(m_Shader, m_TriangleVA, transform);

    Dwarfworks::Renderer::EndScene();
  }

  virtual void OnDebugUIRender() override {
    ImGui::Begin((GetName() + " editor").c_str());
    ImGui::Text("Square Grid Properties");
    ImGui::ColorEdit3("Square Color 1", glm::value_ptr(m_BlueColor));
	ImGui::ColorEdit3("Square Color 2", glm::value_ptr(m_RedColor));
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

  glm::vec4 m_BlueColor = { 0.2f, 0.3f, 0.8f, 1.0f };
  glm::vec4 m_RedColor = { 0.8f, 0.2f, 0.3f, 1.0f };
  glm::vec4 m_GreenColor = { 0.2f, 0.8f, 0.3f, 1.0f };
};

#endif  // PLAYGROUND_LAYER_H_

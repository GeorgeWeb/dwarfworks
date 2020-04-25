#ifndef PLAYGROUND_LAYER_H_
#define PLAYGROUND_LAYER_H_

// Engine
#include <Dwarfworks.h>
// Application entry point
#include <Dwarfworks/Core/EntryPoint.h>

// Debug gui
#include <imgui/imgui.h>

// For testing purposes
#define BUFFERLAYOUT_INITLIST_CONSTRUCT 1
#define ASPECT_RATIO_16_10 1

class Playground : public Dwarfworks::Layer {
  using ShaderTable = std::map<const std::string, Dwarfworks::Ref<Dwarfworks::Shader>>;
  using Texture2DTable = std::map<const std::string, Dwarfworks::Ref<Dwarfworks::Texture2D>>;

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
    float triangleVertices[(3 + 4) * 3] = {
        -0.5f, -0.5f, 0.0f,      // point: bottom left
        0.8f, 0.2f, 0.8f, 1.0f,  // color: bottom left

        0.5f, -0.5f, 0.0f,       // point: bottom right
        0.2f, 0.3f, 0.8f, 1.0f,  // color: bottom right

        0.0f, 0.5f, 0.0f,        // point: top
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
    float squareVertices[(3 + 2) * 4] = {
        -0.75f, -0.75f, 0.0f,  // point: bottom left
		0.0f, 0.0f,			   // tex coord: bottom left

        0.75f,  -0.75f, 0.0f,  // point: bottom right
		1.0, 0.0f,			   // tex coord: bottom right

        0.75f,  0.75f,  0.0f,  // point: top right
		1.0f, 1.0f,			   // tex coord: top right

        -0.75f, 0.75f,  0.0f,  // point: top left
		0.0f, 1.0f			   // tex coord: top left
    };

    uint32_t squareVbSize = sizeof(squareVertices);
    Dwarfworks::Ref<Dwarfworks::VertexBuffer> squareVB;
    squareVB = Dwarfworks::VertexBuffer::Create(squareVertices, squareVbSize);

    // vertex buffer layout
    squareVB->SetLayout({
		{Dwarfworks::ShaderDataType::Float3, "a_Position"},
		{Dwarfworks::ShaderDataType::Float2, "a_TexCoord"} 
	});
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
	cubeVB->SetLayout({
		{Dwarfworks::ShaderDataType::Float3, "a_Position" }
	});
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

	// TODO:
	// Create UniformBuffer class
	//
	// UniformBuffer should serve as a base class to handle uniform buffer objects (UBO)
	// Then for things like ViewProjection Matrix and Transform Matrix, we can
	// pass them as a UBO defined as struct in the shader and keep them persistent per
	// Vertex shader calls rather than binding new uniform copies repetitively for each VS.
	//
	// With this approach we can even automate that with a TransformUniformBuffer child class
	// that will multiply the Transform Matrix with the ViewProjection Matrix and we only
	// need to bind the TransformUniformBuffer for a Drawable that we'll hold a reference to.
	//
	// Consider rewording Uniform to Constant for a more robust and abstract API purposes
	// because UBOs in OpenGL/Vulkan are not the same in Direct3D - they are Constant buffers.

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
	m_Shaders["basic"] = Dwarfworks::Shader::Create(vertSrc, fragSrc);

    // flat color vertex shader
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

    // flat color fragment shader
    std::string flatColorFragSrc = R"(
	#version 330 core

	layout(location = 0) out vec4 color;

	uniform vec4 u_Color;

	void main()
	{
	  color = vec4(u_Color);
	}
	)";

    // flat color shader program
	m_Shaders["flat_color"] = Dwarfworks::Shader::Create(flatColorVertSrc, flatColorFragSrc);

	// texture vertex shader
	std::string textureVertSrc = R"(
	#version 330 core

	layout (location = 0) in vec3 a_Position;
	layout (location = 1) in vec2 a_TexCoord;

	uniform mat4 u_ViewProjection;
	uniform mat4 u_Transform;

	out vec2 v_TexCoord;

	void main()
	{
	  v_TexCoord = a_TexCoord;
	  vec4 vertexPosition = vec4(a_Position, 1.0);
	  gl_Position = u_ViewProjection * u_Transform * vertexPosition;
	}
	)";

	// texture fragment shader
	std::string textureFragSrc = R"(
	#version 330 core

	layout(location = 0) out vec4 color;

	in vec2 v_TexCoord;

	uniform sampler2D u_Texture;

	void main()
	{
	  color = texture(u_Texture, v_TexCoord);
	}
	)";

	// texture shader program
	m_Shaders["texture"] = Dwarfworks::Shader::Create(textureVertSrc, textureFragSrc);
	// Load texture
	m_Textures["checkerboard"] = Dwarfworks::Texture2D::Create("Assets/Textures/Checkerboard.png");
	
	// Upload texture sampler2D uniform
	m_Shaders["texture"]->Bind();
	m_Shaders["texture"]->SetInt("u_Texture", 0);
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
    // Begin scene rendering
    Dwarfworks::Renderer::BeginScene(m_CameraController.GetCamera());

	// Get references to the shaders
	auto& basicShader = m_Shaders["basic"];
	auto& flatColorShader = m_Shaders["flat_color"];
	auto& textureShader = m_Shaders["texture"];

	// Get references to the textures
	auto& checkerboardTexture = m_Textures["checkerboard"];

	// Initialize transform matrix
	glm::mat4 transform(1.0f); // identity default

	// Square Grid
	flatColorShader->Bind();
    for (int y = 0; y < 20; y++) {
      for (int x = 0; x < 20; x++) {
        auto squarePos = glm::vec3(x * 0.175f, y * 0.175f, 0.0f);
		auto squareScale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
        transform = glm::translate(glm::mat4(1.0f), squarePos) * squareScale;
		flatColorShader->SetFloat4("u_Color", (x % 2 == 0) ? blueColor : redColor);
        Dwarfworks::Renderer::Submit(flatColorShader, m_SquareVA, transform);
      }
    }

	// Textured Square
	textureShader->Bind();
	textureShader->SetFloat4("u_Color", whiteColor);
	transform = glm::translate(glm::mat4(1.0f), glm::vec3(-1.25f, 0.75f, 0.0f));
	checkerboardTexture->Bind();
	Dwarfworks::Renderer::Submit(textureShader, m_SquareVA, transform);

	// Cube (3D)
#if 0 // when 3D works enable this
	flatColorShader->Bind();
	transform = glm::translate(glm::mat4(1.0f), glm::vec3(-1.25f, 0.75f, 0.0f));
	m_FlatColorShader->SetFloat4("u_Color", m_GreenColor);
	Dwarfworks::Renderer::Submit(m_FlatColorShader, m_CubeVA, transform);
#endif

    // Triangle
	basicShader->Bind();
	transform = glm::translate(glm::mat4(1.0f), glm::vec3(-1.25f, 2.5f, 0.0f));
    Dwarfworks::Renderer::Submit(basicShader, m_TriangleVA, transform);

	// End scene rendering
    Dwarfworks::Renderer::EndScene();
  }

  virtual void OnDebugUIRender() override {
    ImGui::Begin((GetName() + " editor").c_str());
    ImGui::Text("Square Grid Properties");
    ImGui::ColorEdit4("Square Color 1", glm::value_ptr(blueColor));
	ImGui::ColorEdit4("Square Color 2", glm::value_ptr(redColor));
	ImGui::Text("Textured Square Properties");
	ImGui::ColorEdit4("Color", glm::value_ptr(whiteColor));
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
      return false; // is blocking (true for non-blocking)
    });
  }

 private:
  // camera
  Dwarfworks::OrthographicCameraController m_CameraController;

  // shaders
  ShaderTable m_Shaders;

  // textures
  Texture2DTable m_Textures;

  // meshes
  Dwarfworks::Ref<Dwarfworks::VertexArray> m_TriangleVA;
  Dwarfworks::Ref<Dwarfworks::VertexArray> m_SquareVA;
  Dwarfworks::Ref<Dwarfworks::VertexArray> m_CubeVA;

  // lights
  // TBD
  
  // temporary
  static inline glm::vec4 blueColor = { 0.2f, 0.3f, 0.8f, 1.0f };
  static inline glm::vec4 redColor = { 0.8f, 0.2f, 0.3f, 1.0f };
  static inline glm::vec4 greenColor = { 0.2f, 0.8f, 0.3f, 1.0f };
  static inline glm::vec4 whiteColor = { 1.0f, 1.0f, 1.0f, 1.0f };
};

#endif  // PLAYGROUND_LAYER_H_

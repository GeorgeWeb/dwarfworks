#include <Dwarfworks.h>

#include "imgui/imgui.h"

class Playground : public Dwarfworks::Layer {
 public:
  Playground()
      : Layer("Playground"), m_CameraController(1280.0f / 720.0f, true) {
    // --------------------------------------- //
    // Buffers (Vertex, Index) and VertexArray //
    // --------------------------------------- //

    // vertex array
    m_VertexArray = Dwarfworks::VertexArray::Create();

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
    auto vertexBuffer = Dwarfworks::VertexBuffer::Create(vertices, vbSize);

    // vertex buffer layout
    auto vbLayout = Dwarfworks::BufferLayout{
        {Dwarfworks::ShaderDataType::Float3, "a_Position"},
        {Dwarfworks::ShaderDataType::Float4, "a_Color"}};

    vertexBuffer->SetLayout(vbLayout);
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    // indices
    uint32_t indices[3] = {0, 1, 2};

    // index buffer
    const auto ibCount = sizeof(indices) / sizeof(uint32_t);
    auto indexBuffer = Dwarfworks::IndexBuffer::Create(indices, ibCount);

    m_VertexArray->SetIndexBuffer(indexBuffer);

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
    auto squareVB =
        Dwarfworks::VertexBuffer::Create(squareVertices, squareVbSize);

    // vertex buffer layout
    auto squareVbLayout = Dwarfworks::BufferLayout{
        {Dwarfworks::ShaderDataType::Float3, "a_Position"}};

    squareVB->SetLayout(squareVbLayout);
    m_SquareVA->AddVertexBuffer(squareVB);

    // square indices
    uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};

    // square index buffer
    const auto squareIbCount = sizeof(squareIndices) / sizeof(uint32_t);
    auto squareIB =
        Dwarfworks::IndexBuffer::Create(squareIndices, squareIbCount);

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

	void main() {
	  color = v_Color;
	}
  )";

    // shader program
    m_Shader = Dwarfworks::Shader::Create(vertSrc, fragSrc);

    // blue square vertex shader
    std::string flatVertSrc = R"(
	#version 330 core

	layout (location = 0) in vec3 a_Position;

	uniform mat4 u_ViewProjection;
	uniform mat4 u_Transform;

	void main() {
	  vec4 vertexPosition = vec4(a_Position, 1.0);
	  gl_Position = u_ViewProjection * u_Transform * vertexPosition;
	}
  )";

    // blue square fragment shader
    std::string flatFragSrc = R"(
	#version 330 core

	layout(location = 0) out vec4 color;

	uniform vec3 u_Color;

	void main() {
	  color = vec4(u_Color, 1.0f);
	}
  )";

    // blue square shader program
    m_FlatColorShader = Dwarfworks::Shader::Create(flatVertSrc, flatFragSrc);
  }

  virtual void OnUpdate(Dwarfworks::Timestep deltaTime) override {
    // clear buffers (TODO: Move to a function that takes care of this!)
    Dwarfworks::RenderCommand::SetClearColor({0.15f, 0.15f, 0.15f, 1.0f});
    Dwarfworks::RenderCommand::Clear();

    // move square horizontally
    if (Dwarfworks::Input::IsKeyPressed(Dwarfworks::KeyCodes::LEFT)) {
      m_TrianglePosition.x -= m_TriangleMoveSpeed * deltaTime;
    } else if (Dwarfworks::Input::IsKeyPressed(Dwarfworks::KeyCodes::RIGHT)) {
      m_TrianglePosition.x += m_TriangleMoveSpeed * deltaTime;
    }
    // move square vertically
    if (Dwarfworks::Input::IsKeyPressed(Dwarfworks::KeyCodes::UP)) {
      m_TrianglePosition.y += m_TriangleMoveSpeed * deltaTime;
    } else if (Dwarfworks::Input::IsKeyPressed(Dwarfworks::KeyCodes::DOWN)) {
      m_TrianglePosition.y -= m_TriangleMoveSpeed * deltaTime;
    }

    // update camera
    m_CameraController.OnUpdate(deltaTime);
  }

  virtual void OnRender() override {
    // begin scene rendering
    Dwarfworks::Renderer::BeginScene(m_CameraController.GetCamera());

    static glm::mat4 transform;  // the transform (model) matrix
    static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

    // square
    static glm::vec3 redColor(0.8f, 0.2f, 0.3f);
    static glm::vec3 blueColor(0.2f, 0.3f, 0.8f);

    // auto flatColorMaterial = Dwarfworks::Material::Create(m_FlatColorShader);
    // auto blueMaterialInstance =
    // Dwarfworks::MaterialInstance::Create(flatColorMaterial);
    // blueMaterialInstance->SetFloat3("u_Color", blueColor);
    // m_SquareMesh->SetMaterial(flatColorMaterialInstance);

    std::dynamic_pointer_cast<Dwarfworks::OpenGLShader>(m_FlatColorShader)
        ->Bind();
    std::dynamic_pointer_cast<Dwarfworks::OpenGLShader>(m_FlatColorShader)
        ->UploadUniformFloat3("u_Color", m_SquareColor);

    constexpr float spanX = 0.175f;
    constexpr float spanY = 0.175f;
    for (auto y = 0; y < 20; ++y) {
      for (auto x = 0; x < 20; ++x) {
        glm::vec3 position(x * spanX, y * spanY, 0.0f);
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), position);
        // TRS: T * R * S
        transform = translate * scale;
        // submit the square for rendering
        Dwarfworks::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
      }
    }

    // triangle
    // auto redMaterialInstance =
    // Dwarfworks::MaterialInstance::Create(flatColorMaterial);
    // m_TriangleMesh->SetMaterial(redMaterialInstance);
    // redMaterialInstance->SetFloat3("u_Color", redColor);

    transform = glm::translate(glm::mat4(1.0f), m_TrianglePosition);
    Dwarfworks::Renderer::Submit(m_Shader, m_VertexArray, transform);

    // end scene rendering
    Dwarfworks::Renderer::EndScene();
  }

  virtual void OnDebugUIRender() override {
    ImGui::Begin((GetName() + " editor").c_str());
    ImGui::Text("Settings:");
    // ...
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
  Dwarfworks::OrthographicCameraController m_CameraController;

  // TEMPORARY
  // ---------
  Dwarfworks::Ref<Dwarfworks::Shader> m_Shader;
  Dwarfworks::Ref<Dwarfworks::VertexArray> m_VertexArray;

  Dwarfworks::Ref<Dwarfworks::Shader> m_FlatColorShader;
  Dwarfworks::Ref<Dwarfworks::VertexArray> m_SquareVA;

  glm::vec3 m_TrianglePosition = {0.0f, 0.0f, 0.0f};
  const float m_TriangleMoveSpeed = 1.0f;

  // default square color
  glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};
};

class Sandbox final : public Dwarfworks::Application {
 public:
  Sandbox() : Application(), m_Playground(new Playground) {
    PushLayer(m_Playground);
    DW_INFO("Added {0} layer", m_Playground->GetName());
  }

  virtual ~Sandbox() override = default;

 private:
  Dwarfworks::Layer* m_Playground;
};

Dwarfworks::Scope<Dwarfworks::Application> Dwarfworks::CreateApplication() {
  return Dwarfworks::CreateScope<Sandbox>();
}

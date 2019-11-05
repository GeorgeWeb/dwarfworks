#ifndef PLAYGROUND_LAYER_H_
#define PLAYGROUND_LAYER_H_

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
    m_VertexArray.reset(Dwarfworks::VertexArray::Create());

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
    Dwarfworks::Ref<Dwarfworks::VertexBuffer> vertexBuffer;
    vertexBuffer.reset(Dwarfworks::VertexBuffer::Create(vertices, vbSize));

    // vertex buffer layout
    Dwarfworks::BufferLayout vbLayout = {
        {Dwarfworks::ShaderDataType::Float3, "a_Position"},
        {Dwarfworks::ShaderDataType::Float4, "a_Color"}};

    vertexBuffer->SetLayout(vbLayout);
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    // indices
    uint32_t indices[3] = {0, 1, 2};

    // index buffer
    const auto ibCount = sizeof(indices) / sizeof(uint32_t);
    Dwarfworks::Ref<Dwarfworks::IndexBuffer> indexBuffer;
    indexBuffer.reset(Dwarfworks::IndexBuffer::Create(indices, ibCount));

    m_VertexArray->SetIndexBuffer(indexBuffer);

    // square vertex array
    m_SquareVA.reset(Dwarfworks::VertexArray::Create());

    // square vertices
    float squareVertices[3 * 4] = {
        -0.75f, -0.75f, 0.0f,  // bottom left
        0.75f,  -0.75f, 0.0f,  // bottom right
        0.75f,  0.75f,  0.0f,  // top right
        -0.75f, 0.75f,  0.0f   // top left
    };

    uint32_t squareVbSize = sizeof(squareVertices);
    Dwarfworks::Ref<Dwarfworks::VertexBuffer> squareVB;
    squareVB.reset(
        Dwarfworks::VertexBuffer::Create(squareVertices, squareVbSize));

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
    squareIB.reset(
        Dwarfworks::IndexBuffer::Create(squareIndices, squareIbCount));

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
    m_Shader.reset(new Dwarfworks::Shader(vertSrc, fragSrc));

    // blue square vertex shader
    std::string blueVertSrc = R"(
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
    std::string blueFragSrc = R"(
	#version 330 core
	layout(location = 0) out vec4 color;

	void main() {
	  color = vec4(0.2, 0.3, 0.7, 1.0);
	}
  )";

    // blue square shader program
    m_BlueShader.reset(new Dwarfworks::Shader(blueVertSrc, blueFragSrc));
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

    Dwarfworks::Renderer::Submit(m_BlueShader, m_SquareVA);
    Dwarfworks::Renderer::Submit(m_Shader, m_VertexArray);

    Dwarfworks::Renderer::EndScene();
  }

  virtual void OnDebugUIRender() override {
    ImGui::Begin((GetName() + " editor").c_str());
    ImGui::Text("Add stuff here ...");
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
  Dwarfworks::Ref<Dwarfworks::VertexArray> m_VertexArray;

  Dwarfworks::Ref<Dwarfworks::Shader> m_BlueShader;
  Dwarfworks::Ref<Dwarfworks::VertexArray> m_SquareVA;

  Dwarfworks::OrthographicCameraController m_CameraController;
};

#endif // PLAYGROUND_LAYER_H_
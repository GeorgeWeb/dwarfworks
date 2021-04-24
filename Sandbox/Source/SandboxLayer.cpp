#include "SandboxLayer.h"

// Debug GUI
#include <imgui/imgui.h>

static constexpr float s_AspectRatio = static_cast<float>(s_ScreenWidth) / static_cast<float>(s_ScreenHeight);
static constexpr bool  s_CanRotate   = true;

SandboxLayer::SandboxLayer() : Dwarfworks::Layer("Playground"), m_CameraController(s_AspectRatio, s_CanRotate)
{
    // --------------------------------------- //
    // Buffers (Vertex, Index) and VertexArray //
    // --------------------------------------- //

    // BEGIN TRIANGLE

    // vertex array
    m_Sprites["triangle"] = Dwarfworks::VertexArray::Create();

    // vertices
    float triangleVertices[(3 + 4) * 3] = {
        -0.5f, -0.5f, 0.0f,       // point: bottom left
        0.8f,  0.2f,  0.8f, 1.0f, // color: bottom left

        0.5f,  -0.5f, 0.0f,       // point: bottom right
        0.2f,  0.3f,  0.8f, 1.0f, // color: bottom right

        0.0f,  0.5f,  0.0f,      // point: top
        0.8f,  0.8f,  0.2f, 1.0f // color: top
    };

    // vertex buffer
    uint32_t                                  tiangleVbSize = sizeof(triangleVertices);
    Dwarfworks::Ref<Dwarfworks::VertexBuffer> triangleVB;
    triangleVB = Dwarfworks::VertexBuffer::Create(triangleVertices, tiangleVbSize);

    // vertex buffer layout
    Dwarfworks::BufferLayout vbLayout;
    vbLayout.Append<Dwarfworks::ShaderDataType::Float3>("a_Position");
    vbLayout.Append<Dwarfworks::ShaderDataType::Float4>("a_Color");

    triangleVB->SetLayout(vbLayout);
    m_Sprites["triangle"]->AddVertexBuffer(triangleVB);

    // indices
    uint32_t triangleIndices[3] = {0, 1, 2};

    // index buffer
    const auto                               ibCount = sizeof(triangleIndices) / sizeof(uint32_t);
    Dwarfworks::Ref<Dwarfworks::IndexBuffer> triangleIB;
    triangleIB = Dwarfworks::IndexBuffer::Create(triangleIndices, ibCount);

    m_Sprites["triangle"]->SetIndexBuffer(triangleIB);

    // END OF TRIANGLE

    // BEGIN SQUARE

    // square vertex array
    m_Sprites["square"] = Dwarfworks::VertexArray::Create();

    // square vertices
    float squareVertices[(3 + 2) * 4] = {
        -0.75f, -0.75f, 0.0f, // point: bottom left
        0.0f,   0.0f,         // tex coord: bottom left

        0.75f,  -0.75f, 0.0f, // point: bottom right
        1.0,    0.0f,         // tex coord: bottom right

        0.75f,  0.75f,  0.0f, // point: top right
        1.0f,   1.0f,         // tex coord: top right

        -0.75f, 0.75f,  0.0f, // point: top left
        0.0f,   1.0f          // tex coord: top left
    };

    uint32_t                                  squareVbSize = sizeof(squareVertices);
    Dwarfworks::Ref<Dwarfworks::VertexBuffer> squareVB;
    squareVB = Dwarfworks::VertexBuffer::Create(squareVertices, squareVbSize);

    // vertex buffer layout
    squareVB->SetLayout(
        {{Dwarfworks::ShaderDataType::Float3, "a_Position"}, {Dwarfworks::ShaderDataType::Float2, "a_TexCoord"}});
    m_Sprites["square"]->AddVertexBuffer(squareVB);

    // square indices
    uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};

    // square index buffer
    const auto                               squareIbCount = sizeof(squareIndices) / sizeof(uint32_t);
    Dwarfworks::Ref<Dwarfworks::IndexBuffer> squareIB;
    squareIB = Dwarfworks::IndexBuffer::Create(squareIndices, squareIbCount);

    m_Sprites["square"]->SetIndexBuffer(squareIB);

    // END OF SQUARE

    // --------------------------- //
    // Shaders and Shader Programs //
    // --------------------------- //

    // TODO:
    // Create UniformBuffer class
    //
    // UniformBuffer should serve as a base class to handle uniform buffer
    // objects (UBO) Then for things like ViewProjection Matrix and Transform
    // Matrix, we can pass them as a UBO defined as struct in the shader and
    // keep them persistent per Vertex shader calls rather than binding new
    // uniform copies repetitively for each VS.
    //
    // With this approach we can even automate that with a
    // TransformUniformBuffer child class that will multiply the Transform
    // Matrix with the ViewProjection Matrix and we only need to bind the
    // TransformUniformBuffer for a Drawable that we'll hold a reference to.
    //
    // Consider rewording Uniform to Constant for a more robust and abstract API
    // purposes because UBOs in OpenGL and/or Vulkan are not the same in as in DX CBs.

    // shader program
    auto& basicShader = m_ShaderLibrary.Load("Assets/Shaders/Basic.glsl");

    // flat color shader program
    auto& flatColorShader = m_ShaderLibrary.Load("Assets/Shaders/FlatColor.glsl");

    // texture shader program
    auto& textureShader = m_ShaderLibrary.Load("Assets/Shaders/Texture.glsl");

    // Load texture(s)
    m_Textures["checkerboard"] = Dwarfworks::Texture2D::Create("Assets/Textures/Checkerboard.png");
    m_Textures["inn"]          = Dwarfworks::Texture2D::Create("Assets/Textures/Inn.png");

    // Upload texture sampler2D uniform
    textureShader->Bind();
    textureShader->SetInt("u_Texture", 0);
}

void SandboxLayer::OnUpdate(Dwarfworks::Timestep deltaTime)
{
    // Poll user input
    // ---------------

    // Animate objects
    // ---------------

    // update camera
    m_CameraController.OnUpdate(deltaTime);
}

void SandboxLayer::OnRender()
{
    // clear buffers - Framebuffer abstraction (TODO!)
    Dwarfworks::RenderCommand::SetClearColor({0.2f, 0.2f, 0.2f, 1.0f});
    Dwarfworks::RenderCommand::Clear();

    // Begin scene rendering
    Dwarfworks::Renderer::BeginScene(m_CameraController.GetCamera());

    // Get references to the sprites
    auto& triangle = m_Sprites["triangle"];
    auto& square   = m_Sprites["square"];

    // Get references to the shaders
    auto& basicShader     = m_ShaderLibrary.Get("Basic");
    auto& flatColorShader = m_ShaderLibrary.Get("FlatColor");
    auto& textureShader   = m_ShaderLibrary.Get("Texture");

    // Get references to the textures
    auto& checkerboardTexture = m_Textures["checkerboard"];
    auto& innTexture          = m_Textures["inn"];

    // Initialize transform matrix
    glm::mat4 transform(1.0f); // identity default

    // ------------------- //
    // Colored Square Grid //
    // ------------------- //
    flatColorShader->Bind();
    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 20; x++)
        {
            auto squarePos   = glm::vec3(x * 0.175f, y * 0.175f, 0.0f);
            auto squareScale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
            // update transform matrix
            transform = glm::translate(glm::mat4(1.0f), squarePos) * squareScale;
            // update color uniform
            flatColorShader->SetFloat4("u_Color", (x % 2 == 0) ? blueColor : redColor);
            Dwarfworks::Renderer::Submit(flatColorShader, square, transform);
        }
    }

    // --------------- //
    // Textured Square //
    // --------------- //
    // checkerboard background
    checkerboardTexture->Bind();
    // update transform matrix
    transform = glm::translate(glm::mat4(1.0f), glm::vec3(-1.25f, 0.75f, 0.0f));
    Dwarfworks::Renderer::Submit(textureShader, square, transform);
    // inn overlay
    innTexture->Bind();
    // update transform matrix
    transform = glm::translate(glm::mat4(1.0f), glm::vec3(-1.25f, 0.75f, 0.0f));
    Dwarfworks::Renderer::Submit(textureShader, square, transform);

    // ----------------- //
    // Textured Triangle //
    // ----------------- //
    transform = glm::translate(glm::mat4(1.0f), glm::vec3(-1.25f, 2.5f, 0.0f));
    Dwarfworks::Renderer::Submit(basicShader, triangle, transform);

    // End scene rendering
    Dwarfworks::Renderer::EndScene();
}

void SandboxLayer::OnDebugUIRender()
{
    ImGui::Begin((GetName() + " editor").c_str());
    ImGui::Text("Square Grid");
    ImGui::ColorEdit4("Color 1", glm::value_ptr(blueColor));
    ImGui::ColorEdit4("Color 2", glm::value_ptr(redColor));
    ImGui::Text("Textured Square");
    // TODO: Add properties...
    ImGui::End();
}

void SandboxLayer::OnEvent(Dwarfworks::Event& event)
{
    Dwarfworks::EventManager eventManager(event);

    // handle builtin camera events
    m_CameraController.OnEvent(event);

    // Dynamically recalculate the camera projection matrix
    if (event.GetEventType() == Dwarfworks::EventType::WindowResize)
    {
        auto& re = static_cast<Dwarfworks::WindowResizeEvent&>(event);

        float aspectRatio = static_cast<float>(re.GetWidth()) / static_cast<float>(re.GetHeight());
        m_CameraController.SetAspectRatio(aspectRatio);

        float zoomLevel = m_CameraController.GetZoomLevel();
        m_CameraController.GetCamera().SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel,
                                                     zoomLevel);
    }

    eventManager.Dispatch<Dwarfworks::KeyPressedEvent>([&](auto& ke) {
        switch (ke.GetKeyCode())
        {
            case Dwarfworks::KeyCodes::ESCAPE: {
                DW_INFO("Pressed 'ESC'");
                break;
            }
            default: DW_TRACE("Pressed {0}", static_cast<char>(ke.GetKeyCode())); break;
        }
        return false; // is blocking (true for non-blocking)
    });
}

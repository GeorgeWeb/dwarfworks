#include "SandboxLayer.h"

// ImGUI for DebugUI (?)
#include "Dwarfworks/Core/Log/Log.h"
#include "imgui/imgui.h"

SandboxLayer::SandboxLayer() : Dwarfworks::Layer("Sandbox"), m_CameraController(s_AspectRatio, s_CanRotate)
{
    // Viewport
    Dwarfworks::RenderCommand::SetViewport(0, 0, s_ScreenWidth, s_ScreenHeight);
}

void SandboxLayer::OnAttach()
{
#pragma region BEGIN TRIANGLE
    // triangle vertex array object
    m_Sprites["triangle"] = Dwarfworks::VertexArray::Create();

    // triangle vertices
    float triangleVertices[] = {
        -0.5f, -0.5f, 0.0f,       // point: bottom left
        0.8f,  0.2f,  0.8f, 1.0f, // color: bottom left

        0.5f,  -0.5f, 0.0f,       // point: bottom right
        0.2f,  0.3f,  0.8f, 1.0f, // color: bottom right

        0.0f,  0.5f,  0.0f,      // point: top
        0.8f,  0.8f,  0.2f, 1.0f // color: top
    };

    // triangle vertex buffer
    Dwarfworks::Ref<Dwarfworks::VertexBuffer> triangleVb;
    constexpr uint32_t                        triangleVbSize = sizeof(triangleVertices);
    triangleVb = Dwarfworks::VertexBuffer::Create(triangleVertices, triangleVbSize);

    // triangle vertex buffer layout
    Dwarfworks::BufferLayout vbLayout;
    vbLayout.Append<Dwarfworks::ShaderDataType::Float3>("a_Position");
    vbLayout.Append<Dwarfworks::ShaderDataType::Float4>("a_Color");
    triangleVb->SetLayout(vbLayout);
    m_Sprites["triangle"]->AddVertexBuffer(triangleVb);

    // triangle indices
    uint32_t triangleIndices[] = {0, 1, 2};

    // triangle index buffer
    Dwarfworks::Ref<Dwarfworks::IndexBuffer> triangleIb;
    triangleIb = Dwarfworks::IndexBuffer::Create(triangleIndices, ARRAY_COUNT(triangleIndices));
    m_Sprites["triangle"]->SetIndexBuffer(triangleIb);
#pragma endregion

#pragma region BEGIN SQUARE
    // square vertex array object
    m_Sprites["square"] = Dwarfworks::VertexArray::Create();

    // square vertices
    float squareVertices[] = {
        -0.75f, -0.75f, 0.0f, // point: bottom left
        0.0f,   0.0f,         // tex coord: bottom left

        0.75f,  -0.75f, 0.0f, // point: bottom right
        1.0,    0.0f,         // tex coord: bottom right

        0.75f,  0.75f,  0.0f, // point: top right
        1.0f,   1.0f,         // tex coord: top right

        -0.75f, 0.75f,  0.0f, // point: top left
        0.0f,   1.0f          // tex coord: top left
    };

    // square vertex buffer
    Dwarfworks::Ref<Dwarfworks::VertexBuffer> squareVb;
    constexpr uint32_t                        squareVbSize = sizeof(squareVertices);
    squareVb = Dwarfworks::VertexBuffer::Create(squareVertices, squareVbSize);
    // vertex buffer layout
    squareVb->SetLayout({// vertex buffer attribute: position
                         {Dwarfworks::ShaderDataType::Float3, "a_Position"},
                         // vertex buffer attribute: textcoord
                         {Dwarfworks::ShaderDataType::Float2, "a_TexCoord"}});
    m_Sprites["square"]->AddVertexBuffer(squareVb);

    // square indices
    uint32_t squareIndices[] = {0, 1, 2, 2, 3, 0};

    // square index buffer
    Dwarfworks::Ref<Dwarfworks::IndexBuffer> squareIb;
    squareIb = Dwarfworks::IndexBuffer::Create(squareIndices, ARRAY_COUNT(squareIndices));
    m_Sprites["square"]->SetIndexBuffer(squareIb);
#pragma endregion

    // Load texture(s)
    m_Textures["checkerboard"] = Dwarfworks::Texture2D::Create("Assets/Textures/Checkerboard.png");
    m_Textures["inn"]          = Dwarfworks::Texture2D::Create("Assets/Textures/Inn.png");

    // shader program
    m_ShaderLibrary.Load("Assets/Shaders/Basic.glsl");
    m_ShaderLibrary.Load("Assets/Shaders/FlatColor.glsl");
    m_ShaderLibrary.Load("Assets/Shaders/Texture.glsl");

    // Upload texture sampler2D uniform
    m_ShaderLibrary.Get("Texture")->Bind();
    m_ShaderLibrary.Get("Texture")->SetInt("u_Texture", 0);
}

void SandboxLayer::OnDetach()
{
}

void SandboxLayer::OnUpdate(Dwarfworks::Timestep deltaTime)
{
    // update camera
    m_CameraController.OnUpdate(deltaTime);
}

void SandboxLayer::OnRender()
{
    // TODO(georgi): Frame buffer abstraction
    Dwarfworks::RenderCommand::SetClearColor({0.1f, 0.2f, 0.3f, 1.0f});
    Dwarfworks::RenderCommand::Clear(Dwarfworks::ClearBufferMask::DepthBuffer |
                                     Dwarfworks::ClearBufferMask::ColorBuffer);

    // Begin scene rendering
    Dwarfworks::Renderer::BeginScene(m_CameraController.GetCamera());

    // Get references to the sprites
    auto& triangle = m_Sprites["triangle"];
    auto& square   = m_Sprites["square"];

    // Get references to the textures
    auto& checkerboardTexture = m_Textures["checkerboard"];
    auto& innTexture          = m_Textures["inn"];

    // Get references to the shaders
    auto basicShader     = m_ShaderLibrary.Get("Basic");
    auto flatColorShader = m_ShaderLibrary.Get("FlatColor");
    auto textureShader   = m_ShaderLibrary.Get("Texture");

    // Initialize transform matrix
    glm::mat4 transform(1.0f); // identity default

    flatColorShader->Bind();
    const int rows = 20, cols = 20;
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            auto squarePos   = glm::vec3(x * 0.175f, y * 0.175f, 0.0f);
            auto squareScale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
            // update transform matrix
            transform = glm::translate(glm::mat4(1.0f), squarePos) * squareScale;
            // update color uniform
            flatColorShader->SetFloat4("u_Color", (x % 2 == 0) ? s_BlueColor : s_RedColor);
            Dwarfworks::Renderer::Submit(flatColorShader, square, transform);
        }
    }

    // TODO(georgi): Replace with Renderer2D::DrawQuad

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

    transform = glm::translate(glm::mat4(1.0f), glm::vec3(-1.25f, 2.5f, 0.0f));
    Dwarfworks::Renderer::Submit(basicShader, triangle, transform);

    // End scene rendering
    Dwarfworks::Renderer::EndScene();
}

void SandboxLayer::OnDebugUIRender()
{
    ImGui::Begin((GetName() + " editor").c_str());
    ImGui::Text("Square Grid");
    ImGui::ColorEdit4("Color 1", glm::value_ptr(s_BlueColor));
    ImGui::ColorEdit4("Color 2", glm::value_ptr(s_RedColor));
    ImGui::End();
}

void SandboxLayer::OnEvent(Dwarfworks::Event& event)
{
    Dwarfworks::EventDispatcher eventDispatcher(event);

    // Handle builtin camera events
    m_CameraController.OnEvent(event);

    // Dynamically recalculate the camera projection matrix
    eventDispatcher.Dispatch<Dwarfworks::WindowResizeEvent>([&](auto& re) {
        const uint32_t width  = re.GetWidth();
        const uint32_t height = re.GetHeight();
        // Update aspect ration
        float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
        m_CameraController.SetAspectRatio(aspectRatio);
        // Re-project
        float zoomLevel = m_CameraController.GetZoomLevel();
        m_CameraController.GetCamera().SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel,
                                                     zoomLevel);

        // Reset Viewport
        Dwarfworks::RenderCommand::SetViewport(0, 0, width, height);

        return false;
    });

    // Quit the application using the 'Esc' key
    eventDispatcher.Dispatch<Dwarfworks::KeyPressedEvent>([&](auto& ke) {
        if (ke.GetKeyCode() == Dwarfworks::KeyCode::ESCAPE)
        {
            Dwarfworks::Application::Get().Quit();
        }

        return true;
    });
}

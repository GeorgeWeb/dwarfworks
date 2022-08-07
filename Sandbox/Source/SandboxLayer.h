#pragma once

#include "Dwarfworks.h"

#include <map>

constexpr uint32_t s_ScreenWidth  = 1920;
constexpr uint32_t s_ScreenHeight = 1080;

constexpr auto s_AspectRatio = static_cast<float>(s_ScreenWidth) / static_cast<float>(s_ScreenHeight);
constexpr bool s_CanRotate   = true;

// Temp.
static glm::vec4 s_BlueColor  = {0.2f, 0.3f, 0.8f, 1.0f};
static glm::vec4 s_RedColor   = {0.8f, 0.2f, 0.3f, 1.0f};
static glm::vec4 s_GreenColor = {0.2f, 0.8f, 0.3f, 1.0f};
static glm::vec4 s_WhiteColor = {1.0f, 1.0f, 1.0f, 1.0f};
static glm::vec4 s_BlackColor = {0.0f, 0.0f, 0.0f, 1.0f};

// Temp.
using ShaderTable    = std::map<const std::string, Dwarfworks::Ref<Dwarfworks::Shader>>;
using Texture2DTable = std::map<const std::string, Dwarfworks::Ref<Dwarfworks::Texture2D>>;
using SpriteTable    = std::map<const std::string, Dwarfworks::Ref<Dwarfworks::VertexArray>>;

/*
struct Mesh final
{
    Texture2DTable            m_Textures;
    SpriteTable               m_Sprites;

    glm::mat4 Transform;
};
*/

class SandboxLayer final : public Dwarfworks::Layer
{
  public:
    SandboxLayer();

    virtual void OnAttach() override final;
    virtual void OnDetach() override final;

    virtual void OnUpdate(Dwarfworks::Timestep deltaTime) override final;

    virtual void OnRender() override final;

    virtual void OnDebugUIRender() override final;

    virtual void OnEvent(Dwarfworks::Event& event) override final;

  private:
    // meshes
    // std::vector<Scope<Mesh>> m_Meshes;

    // camera
    Dwarfworks::OrthographicCameraController m_CameraController;
    // shaders
    Dwarfworks::ShaderLibrary m_ShaderLibrary;

    // textures
    Texture2DTable m_Textures;
    // sprites
    SpriteTable m_Sprites;
};

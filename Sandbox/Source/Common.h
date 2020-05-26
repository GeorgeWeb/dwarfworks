#pragma once

// Engine
#include <Dwarfworks.h>

// For testing purposes
#define ASPECT_RATIO_16_10 1
// ...
#if ASPECT_RATIO_16_10
static constexpr uint32_t s_ScreenWidth = 1680;
static constexpr uint32_t s_ScreenHeight = 1050;
#else
static constexpr uint32_t s_ScreenWidth = 1600;
static constexpr uint32_t s_ScreenHeight = 900;
#endif

// ...
class SandboxLayer : public Dwarfworks::Layer {
 public:
  explicit SandboxLayer(const std::string& name) : Layer(name) {}

  virtual void OnUpdate(Dwarfworks::Timestep deltaTime) override{};
  virtual void OnRender() override{};
  virtual void OnDebugUIRender() override{};
  virtual void OnEvent(Dwarfworks::Event& event) override{};

  virtual bool IsOverlay() const override { return m_Overlay; }

 protected:
  bool m_Overlay = false;
};

// ...
using ShaderTable =
    std::map<const std::string, Dwarfworks::Ref<Dwarfworks::Shader>>;
using Texture2DTable =
    std::map<const std::string, Dwarfworks::Ref<Dwarfworks::Texture2D>>;
using SpriteTable =
    std::map<const std::string, Dwarfworks::Ref<Dwarfworks::VertexArray>>;

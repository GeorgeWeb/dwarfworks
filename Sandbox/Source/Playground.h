#ifndef PLAYGROUND_LAYER_H_
#define PLAYGROUND_LAYER_H_

// Engine and common defines
#include "Common.h"

class Playground final : public SandboxLayer {
 public:
  Playground();

  virtual void OnUpdate(Dwarfworks::Timestep deltaTime) override final;
  virtual void OnRender() override final;
  virtual void OnDebugUIRender() override final;
  virtual void OnEvent(Dwarfworks::Event& event) override final;

 private:
  // camera
  Dwarfworks::OrthographicCameraController m_CameraController;

  // shaders
  Dwarfworks::ShaderLibrary m_ShaderLibrary;

  // textures
  Texture2DTable m_Textures;

  // sprites
  SpriteTable m_Sprites;

  // lights
  // TBD

  // temporary
  static inline glm::vec4 blueColor = {0.2f, 0.3f, 0.8f, 1.0f};
  static inline glm::vec4 redColor = {0.8f, 0.2f, 0.3f, 1.0f};
  static inline glm::vec4 greenColor = {0.2f, 0.8f, 0.3f, 1.0f};
  static inline glm::vec4 whiteColor = {1.0f, 1.0f, 1.0f, 1.0f};
  static inline glm::vec4 blackColor = {0.0f, 0.0f, 0.0f, 1.0f};
};

#endif  // PLAYGROUND_LAYER_H_

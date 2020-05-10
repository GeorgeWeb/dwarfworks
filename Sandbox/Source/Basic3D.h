#ifndef BASIC_3D_LAYER_H_
#define BASIC_3D_LAYER_H_

#include "Common.h"

class Basic3D final : public SandboxLayer {
 public:
  Basic3D();

  virtual void OnUpdate(Dwarfworks::Timestep deltaTime) override final;
  virtual void OnRender() override final;
  virtual void OnDebugUIRender() override final;
  virtual void OnEvent(Dwarfworks::Event& event) override final;

 private:
  // temporary
  static inline glm::vec4 blueColor = {0.2f, 0.3f, 0.8f, 1.0f};
  static inline glm::vec4 redColor = {0.8f, 0.2f, 0.3f, 1.0f};
  static inline glm::vec4 greenColor = {0.2f, 0.8f, 0.3f, 1.0f};
  static inline glm::vec4 whiteColor = {1.0f, 1.0f, 1.0f, 1.0f};
  static inline glm::vec4 blackColor = {0.0f, 0.0f, 0.0f, 1.0f};
};

#endif  // BASIC_3D_LAYER_H_

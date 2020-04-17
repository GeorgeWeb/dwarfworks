#ifndef FACTORIES_SHADER_FACTORY_H_
#define FACTORIES_SHADER_FACTORY_H_

#include "Dwarfworks/Core/Core.h"
#include "Dwarfworks/Graphics/Shader.h"

namespace Dwarfworks {

// TODO: Implement as a Singleton!
class DW_API ShaderFactory {
 public:
  // ...
  Ref<Shader> FlatColorShader();
  // ...
  Ref<Shader> VertexColorGradientShader();
  // ...
  // Ref<Shader> Texture2DShader();
  // ...
  // Ref<Shader> Texture3DShader();
  // ...
  // Ref<Shader> PhongShader();
  // ...
  // Ref<Shader> AnimatedPhongShader();
  // ...
  // Ref<Shader> PBRShader();
  // ...
  // Ref<Shader> AnimatedPBRShader();
  // ...
  // Ref<Shader> TerrainShader();
  // ...
  // Ref<Shader> OceanShader();
  // ...
  // Ref<Shader> SkyBoxShader();

  // a complete single shader with all supported features
  // Ref<Shader> StandardShader();
};

}

#endif // FACTORIES_SHADER_FACTORY_H_

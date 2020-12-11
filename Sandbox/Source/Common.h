#ifndef SANDBOX_COMMON_H_
#define SANDBOX_COMMON_H_

#include <Dwarfworks.h>

static constexpr uint32_t s_ScreenWidth = 1920;
static constexpr uint32_t s_ScreenHeight = 1080;

using ShaderTable =
    std::map<const std::string, Dwarfworks::Ref<Dwarfworks::Shader>>;
using Texture2DTable =
    std::map<const std::string, Dwarfworks::Ref<Dwarfworks::Texture2D>>;
using SpriteTable =
    std::map<const std::string, Dwarfworks::Ref<Dwarfworks::VertexArray>>;

#endif // SANDBOX_COMMON_H

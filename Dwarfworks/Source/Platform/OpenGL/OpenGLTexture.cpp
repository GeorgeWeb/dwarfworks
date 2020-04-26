// begin PCH
#include "dwpch.h"
// end PCH

#include "Dwarfworks/Core/Log/Log.h"

#include "OpenGLTexture.h"

#include <stb_image.h>

#include <glad/glad.h>

namespace Dwarfworks {

static constexpr int levels = 1; // (num mipmaps)	temporary
static constexpr int flip = 1; // flip image on load

OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : m_Path(path) {
  const char* filename = path.c_str();
  int x, y, ch;
  // store the image data in memory on the CPU
  stbi_set_flip_vertically_on_load(flip);
  stbi_uc* data = stbi_load(filename, &x, &y, &ch, 0);
  DW_CORE_ASSERT(data, "Failed to load image!");
  
  m_Width = x;
  m_Height = y;

  int internalFormat = (ch == 4) ? GL_RGBA8 : (ch == 3) ? GL_RGB8 : 0;
  int dataFormat = (ch == 4) ? GL_RGBA : (ch == 3) ? GL_RGB : 0;

  DW_CORE_ASSERT(internalFormat & dataFormat, "Texture format NOT supported!");
  // save the data format
  m_Format = dataFormat;

  glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
  glTextureStorage2D(m_RendererId, levels, internalFormat, m_Width, m_Height);

  // handle minification and magnification
  int param;
  // linearly interpolate to workout color
  param = GL_LINEAR;
  glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, param);
  // snap to the nearest pixel (more crisp)
  param = GL_NEAREST;
  glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, param);

  DW_CORE_ASSERT(levels == 1, "No more/less than 1 mipmap levels supported!");
  glTextureSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

  // deallocate the memory where image data is stored in
  stbi_image_free(data);
}

OpenGLTexture2D::~OpenGLTexture2D() {
  glDeleteTextures(1, &m_RendererId);
}

void OpenGLTexture2D::Bind(uint32_t slot /*=0*/) const {
	glBindTextureUnit(slot, m_RendererId);
}

}

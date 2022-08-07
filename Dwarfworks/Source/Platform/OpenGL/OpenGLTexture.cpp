// begin PCH
#include "dwpch.h"
// end PCH

#include "glad/glad.h"
#include "stb_image.h"

#include "Dwarfworks/Core/Log/Log.h"
#include "OpenGLTexture.h"

namespace Dwarfworks
{
static constexpr int levels = 1; // (num mipmaps)	temporary
static constexpr int flip   = 1; // flip image on load

OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : m_Path {path}
{
    const char* filename = path.c_str();
    int         x, y, ch;
    // Store the image data in memory on the CPU
    stbi_set_flip_vertically_on_load(flip);
    stbi_uc* pixelData = stbi_load(filename, &x, &y, &ch, 0);
    DW_CORE_ASSERT(pixelData, "Failed to load image!");

    m_Width  = x;
    m_Height = y;

    int internalFormat = (ch == 4) ? GL_RGBA8 : (ch == 3) ? GL_RGB8 : 0;
    int pixelFormat    = (ch == 4) ? GL_RGBA : (ch == 3) ? GL_RGB : 0;

    DW_CORE_ASSERT(internalFormat & pixelFormat, "Texture format NOT supported!");
    // Save the pixel format
    m_Format = pixelFormat;

    // Create texture
    // glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
    glGenTextures(1, &m_RendererId);
    glBindTexture(GL_TEXTURE_2D, m_RendererId);

    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture filtering parameters
    // Linearly interpolate to workout color
    // glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // 4.5
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // Snap to the nearest pixel (more crisp)
    // glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // 4.5
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Mip-maps

    // (levels = LOD number for the image)
    DW_CORE_ASSERT(levels == 1, "No more/less than 1 mipmap levels supported!");

    // glTextureStorage2D(m_RendererId, levels, internalFormat, m_Width, m_Height); // 4.5
    // glTexStorage2D(GL_TEXTURE_2D, levels, internalFormat, m_Width, m_Height); // 4.2
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, pixelFormat, GL_UNSIGNED_BYTE, pixelData);

    // Generate mipmaps
    // glTextureSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, pixelFormat, GL_UNSIGNED_BYTE, pixelData); // 4.5
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, pixelFormat, GL_UNSIGNED_BYTE, pixelData);

    // Deallocate the memory where image data is stored in
    stbi_image_free(pixelData);
}

OpenGLTexture2D::~OpenGLTexture2D()
{
    glDeleteTextures(1, &m_RendererId);
}

inline void OpenGLTexture2D::Bind(uint32 slot /*=0*/) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_RendererId);
}

} // namespace Dwarfworks

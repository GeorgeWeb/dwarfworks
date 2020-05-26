// begin PCH
#include "dwpch.h"
// end PCH

#include <glad/glad.h>

#include "OpenGLRendererAPI.h"

namespace Dwarfworks {

const uint32_t BufferTarget::Color = GL_COLOR_BUFFER_BIT;
const uint32_t BufferTarget::Depth = GL_DEPTH_BUFFER_BIT;
const uint32_t BufferTarget::Stencil = GL_STENCIL_BUFFER_BIT;

void OpenGLRendererAPI::SetBlending(bool enable) const {
  if (enable) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  } else {
    glDisable(GL_BLEND);
  }
}

void OpenGLRendererAPI::SetDepthTest(bool enable) const {
  if (enable) {
    glEnable(GL_DEPTH_TEST);
  } else {
    glDisable(GL_DEPTH_TEST);
  }
}

void OpenGLRendererAPI::SetScissorTest(bool enable) const {
  if (enable) {
    glEnable(GL_SCISSOR_TEST);
  } else {
    glDisable(GL_SCISSOR_TEST);
  }
}

void OpenGLRendererAPI::Initialize() const {
  // Enable texture blending
  SetBlending();
}

void OpenGLRendererAPI::SetViewport(int x, int y, uint32_t width,
                                    uint32_t height) const {
  glViewport(x, y, width, height);
}

void OpenGLRendererAPI::SetScissor(int x, int y, uint32_t width,
                                   uint32_t height) const {
  glScissor(x, y, width, height);
}

void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) const {
  glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRendererAPI::Clear(uint32_t target) const { glClear(target); }

void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray) const {
  uint32_t elementCount = vertexArray->GetIndexBuffer()->GetCount();
  if (static bool print = true; print) {
    DW_CORE_INFO("Drawing elements with {0} indices.", elementCount);
    print = false;
  }
  glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, nullptr);
}

}  // namespace Dwarfworks

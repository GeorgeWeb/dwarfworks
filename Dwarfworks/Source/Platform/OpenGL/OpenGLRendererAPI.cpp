// begin PCH
#include "dwpch.h"
// end PCH

#include <glad/glad.h>

#include "OpenGLRendererAPI.h"

namespace Dwarfworks {

void OpenGLRendererAPI::Initialize() const {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpenGLRendererAPI::SetViewport(int x, int y, uint32_t width,
                                    uint32_t height) const {
  glViewport(x, y, width, height);
}

void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) const {
  glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRendererAPI::Clear() const {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray) const {
  uint32_t elementCount = vertexArray->GetIndexBuffer()->GetCount();
  if (static bool print = true; print) {
    DW_CORE_INFO("Drawing elements with {0} indices.", elementCount);
    print = false;
  }
  glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, nullptr);
}

}  // namespace Dwarfworks

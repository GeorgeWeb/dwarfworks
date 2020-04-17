// begin PCH
#include "dwpch.h"
// end PCH

#include <glad/glad.h>

#include "OpenGLRendererAPI.h"

namespace Dwarfworks {

void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) {
  glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRendererAPI::Clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray) {
  uint32_t elementCount = vertexArray->GetIndexBuffer()->GetCount();
  if (static bool print = true; print) {
	  DW_CORE_INFO("Drawing elements with {0} indices.", elementCount);
	  print = false;
  }
  glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, nullptr);
}

}  // namespace Dwarfworks

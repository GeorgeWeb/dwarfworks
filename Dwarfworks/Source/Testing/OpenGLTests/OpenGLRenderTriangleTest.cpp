// begin PCH
#include "dwpch.h"
// end PCH

#include "OpenGLRenderTriangleTest.h"

// glad
#include <glad/glad.h>
// imgui
#include "imgui.h"

namespace Testing {

// OpenGLRenderTriangleTest

OpenGLRenderTriangleTest::OpenGLRenderTriangleTest() {
  glGenVertexArrays(1, &m_VertexArray);
  glBindVertexArray(m_VertexArray);

  glGenBuffers(1, &m_VertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

  float vertices[9] = {-0.5f, -0.5f, 0.0f,   // left
                       0.5f,  -0.5f, 0.0f,   // right
                       0.0f,  0.5f,  0.0f};  // top

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

  glGenBuffers(1, &m_IndexBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

  uint32_t indices[3] = {0, 1, 2};
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(uint32_t), indices,
               GL_STATIC_DRAW);

  // vertex shader
  std::string vertSrc = R"(
	#version 330 core
	
	layout (location = 0) in vec3 a_Position;

	out vec3 v_Position;

	void main() {
	  v_Position = a_Position;
	  gl_Position = vec4(a_Position, 1.0);
	}
  )";

  // fragment shader
  std::string fragSrc = R"(
	#version 330 core
	
	layout (location = 0) out vec4 color;

	in vec3 v_Position;

	void main() {
      vec3 finalColor = vec3(v_Position * 0.5 + 0.5);
	  color = vec4(finalColor, 1.0);
	}
  )";

  m_Shader = Dwarfworks::CreateScope<Dwarfworks::Shader>(vertSrc, fragSrc);
}

void OpenGLRenderTriangleTest::OnRender() {
  m_Shader->Bind();
  glBindVertexArray(m_VertexArray);
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
  m_Shader->Unbind();
}

}  // namespace Testing

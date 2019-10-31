// begin PCH
#include "dwpch.h"
// end PCH

#include "ShaderManagerTest.h"

// glad
#include <glad/glad.h>
// imgui
#include "imgui.h"

namespace Testing {
ShaderManagerTest::ShaderManagerTest()
    : m_ShaderManager{Dwarfworks::ShaderManager::GetInstance()} {
  // Create Shaders
  m_ShaderManager.CreateProgram(
      m_Program1,
      "../Dwarfworks/Source/Testing/OpenGLTests/GLSLShaders/TestShader1.vert",
      "../Dwarfworks/Source/Testing/OpenGLTests/GLSLShaders/TestShader1.frag");
  m_ShaderManager.CreateProgram(
      m_Program2,
      "../Dwarfworks/Source/Testing/OpenGLTests/GLSLShaders/TestShader2.vert",
      "../Dwarfworks/Source/Testing/OpenGLTests/GLSLShaders/TestShader2.frag");

  // Generate triangle
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

  unsigned int indices[3] = {0, 1, 2};
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(uint32_t), indices,
               GL_STATIC_DRAW);

  // bind normal shader
  m_ShaderManager.BindProgram(m_Program1);
}

void ShaderManagerTest::OnRender() {
  m_ShaderManager.BindProgram(m_ShaderManager.GetActiveProgramName());
  glBindVertexArray(m_VertexArray);
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
  m_ShaderManager.UnbindProgram();
}

void ShaderManagerTest::OnDebugUIRender() {
  for (auto& programName : m_ShaderManager.GetAllProgramNames()) {
    if (ImGui::Button(programName.c_str())) {
      m_ShaderManager.BindProgram(programName);
    }
  }
}

}  // namespace Testing

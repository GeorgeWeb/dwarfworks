// begin PCH
#include "dwpch.h"
// end PCH

#include "ShaderManagerTest.h"

namespace Tests {
#define SMGetInstance() Dwarfworks::ShaderManager::GetInstance()
ShaderManagerTest::ShaderManagerTest() {
  // Create Shaders
  //	"3.3.shader.vs", "3.3.shader.fs"
  // SM = Dwarfworks::ShaderManager();

  DW_WARN("{0}", glGetString(GL_VERSION));

  SMGetInstance().CreateProgram(
      m_Program1, "../Dwarfworks/Source/Tests/TestShaders/TestShader1.vert",
      "../Dwarfworks/Source/Tests/TestShaders/TestShader1.frag");
  SMGetInstance().CreateProgram(
      m_Program2, "../Dwarfworks/Source/Tests/TestShaders/TestShader2.vert",
      "../Dwarfworks/Source/Tests/TestShaders/TestShader2.frag");

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
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  // bind normal shader
  SMGetInstance().BindProgram(m_Program1);
}

void ShaderManagerTest::OnRender() {
  SMGetInstance().BindProgram(SMGetInstance().GetActiveProgramName());
  glBindVertexArray(m_VertexArray);
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
  SMGetInstance().UnbindProgram();
}

void ShaderManagerTest::OnDebugUIRender() {
  for (auto& programName : SMGetInstance().GetAllProgramNames()) {
    if (ImGui::Button(programName.c_str())) {
      SMGetInstance().BindProgram(programName);
    }
  }
}
#undef SMGetInstance()
}  // namespace Tests

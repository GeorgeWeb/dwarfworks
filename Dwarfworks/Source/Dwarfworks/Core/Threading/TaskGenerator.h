#pragma once

#include "Dwarfworks/Core/Core.h"

#include "ThreadManager.h"

namespace Dwarfworks {
DW_API void TestTaskRendering() {
  for (int i = 0; i < 10000000; i++) {
  }
  DW_CORE_WARN("RENDERING");
}

DW_API void TestTaskAI() {
  for (int i = 0; i < 5000; i++) {
  }
  DW_CORE_WARN("AI");
}

DW_API void TestTaskPhysics() {
  int a = 0;
  int b = 0;
  for (int i = 0; i < 600; i++) {
    a = a + b;
  }
  DW_CORE_WARN("PHYSICS");
}
class DW_API TaskGenerator {
 public:
  explicit TaskGenerator(ThreadManager* threadManager)
      : m_ThreadManager(threadManager) {
    m_RenderTask.function = &TestTaskRendering;
    m_AITask.function = &TestTaskAI;
    m_PhysicsTask.function = &TestTaskPhysics;

    m_RenderingTaskListRef =
        m_ThreadManager->GetTaskListRef(TaskLabelRendering);
    m_PhysicsTaskListRef = m_ThreadManager->GetTaskListRef(TaskLabelPhysics);
    m_AiTaskListRef = m_ThreadManager->GetTaskListRef(TaskLabelAI);
  }

  void CreateTasks() {
    if (!m_RenderingTaskListRef->IsFull())
      m_RenderingTaskListRef->Add(CreateScope<Task>(m_RenderTask));
    if (!m_AiTaskListRef->IsFull())
      m_AiTaskListRef->Add(CreateScope<Task>(m_AITask));
    if (!m_PhysicsTaskListRef->IsFull())
      m_PhysicsTaskListRef->Add(CreateScope<Task>(m_PhysicsTask));
  }

 private:
  ThreadManager* m_ThreadManager;

  Task m_RenderTask;
  Task m_AITask;
  Task m_PhysicsTask;

  Ref<TaskList> m_RenderingTaskListRef;
  Ref<TaskList> m_PhysicsTaskListRef;
  Ref<TaskList> m_AiTaskListRef;
};

}  // namespace Dwarfworks

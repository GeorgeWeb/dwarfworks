#include "dwpch.h"

#include "TaskList.h"

namespace Dwarfworks {

const size_t TaskList::s_MaxTaskListSize = 60;

// Task List
// ---------

TaskList::TaskList() {}

TaskList::~TaskList() {
  while (!m_TaskList.empty()) {
    m_TaskList.pop();
  }
}

void TaskList::Add(Scope<Task> task) { m_TaskList.push(std::move(task)); }

Scope<Task> TaskList::PullTask() {
  Scope<Task> task = std::move(m_TaskList.front());
  m_TaskList.pop();
  return task;
}

// Bin List
// --------

void BinList::Add(Scope<Task> task) { task.reset(nullptr); }

}  // namespace Dwarfworks

#ifndef TASK_LIST_H_
#define TASK_LIST_H_

#include <iostream>
#include <queue>

#include "Dwarfworks/Core/Core.h"

namespace Dwarfworks {

class DW_API Task {
  using taskFunc_t = void (*)();

 public:
  // int id;
  std::string name;
  void* data;
  taskFunc_t function;
};

class DW_API TaskList {
 public:
  TaskList() = default;

  ~TaskList();

  TaskList(TaskList&&) = default;
  TaskList& operator=(TaskList&&) = default;

  TaskList(const TaskList&) = delete;
  TaskList& operator=(const TaskList&) = delete;

  void Add(Scope<Task> task);

 private:
  std::queue<Scope<Task>> m_TaskList;
};

}  // namespace Dwarfworks

#endif  // TASK_LIST_H_

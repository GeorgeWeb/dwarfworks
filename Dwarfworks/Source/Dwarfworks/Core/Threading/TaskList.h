#ifndef CORE_THREADING_TASK_LIST_H_
#define CORE_THREADING_TASK_LIST_H_

#include <iostream>
#include <queue>

#include "Dwarfworks/Core/Core.h"
#include "Dwarfworks/Core/Log/Log.h"

namespace Dwarfworks {

// TASK
// ---------------------------------
class DW_API Task {
  using taskFunc_t = void (*)();

 public:
  // int id;
  std::string name;
  void* data;
  taskFunc_t function;
};

// TASK LIST
// ---------------------------------
class DW_API TaskList {
 public:
  TaskList();

  virtual ~TaskList();

  TaskList(TaskList&&) = default;
  TaskList& operator=(TaskList&&) = default;

  TaskList(const TaskList&) = delete;
  TaskList& operator=(const TaskList&) = delete;

  virtual void Add(Scope<Task> task);
  Scope<Task> PullTask();

  inline bool IsEmpty() const { return m_TaskList.empty(); }
  inline bool IsFull() const { return m_TaskList.size() > s_MaxTaskListSize; }

 private:
  static const size_t s_MaxTaskListSize;
  std::queue<Scope<Task>> m_TaskList;
};

// BIN LIST
// ---------------------------------
class DW_API BinList : public TaskList {
 public:
  BinList() = default;
  ~BinList() override = default;

  void Add(Scope<Task> task) override;
};

}  // namespace Dwarfworks

#endif  // CORE_THREADING_TASK_LIST_H_

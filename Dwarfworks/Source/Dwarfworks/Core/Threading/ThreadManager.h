#ifndef CORE_THREADING_THREAD_MANAGER_H_
#define CORE_THREADING_THREAD_MANAGER_H_

#include "dwpch.h"

#include "Dwarfworks/Core/Core.h"

#include "TaskList.h"

#include <thread>

namespace Dwarfworks {

// ...

enum TaskLabel {
  // ...
  TaskLabelRendering = 0,
  // ...
  TaskLabelPhysics = 1,
  // ...
  TaskLabelAI = 2,
  // ...
  TaskLabelOther = 3
};

struct ThreadArg {
  ThreadArg(unsigned int id, TaskLabel label, TaskList* tasks);

  unsigned int id;
  TaskList* tasks;
  TaskLabel label;
  bool paused = true;
};

class DW_API ThreadManager {
 public:
  ThreadManager();

  // TASKS LIST
 public:
  Ref<TaskList> GetTaskListRef(TaskLabel label);

 private:
  std::unordered_map<TaskLabel, Ref<TaskList>> m_TaskListRefs;
  Ref<BinList> m_BinList;

  // THREADS
 public:
  void ThreadProcess(ThreadArg* argument);
  void UnpauseThreads();
  void PauseThreads();
  // void ThreadProcess();
  void JoinThreads();
  void RunThreads();
  void CreateTaskLists();

 private:
  unsigned int m_NumThreads;
  std::vector<std::thread*> m_ThreadList;
  std::vector<ThreadArg> m_ThreadArgs;
};
}  // namespace Dwarfworks

#endif  // CORE_THREADING_THREAD_MANAGER_H_

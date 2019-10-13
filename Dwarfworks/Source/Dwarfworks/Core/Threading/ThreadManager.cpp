#include "dwpch.h"

#include "ThreadManager.h"

#include "Dwarfworks/Core/Log/Log.h"

#include <chrono>
namespace Dwarfworks {

ThreadManager::ThreadManager() {
  // m_NumThreads = std::thread::hardware_concurrency();
  m_NumThreads = 3;
  // m_ThreadList.reserve(m_NumThreads - 1);
  // m_ThreadList = std::vector<std::thread*>(m_NumThreads - 1);
  m_ThreadList = std::vector<std::thread*>(3);
  // m_ThreadArgs.reserve(m_NumThreads - 1);
  m_ThreadArgs.reserve(m_NumThreads);
}

Ref<TaskList> ThreadManager::GetTaskListRef(TaskLabel label) {
  auto taskListIt = m_TaskListRefs.find(label);
  if (taskListIt != m_TaskListRefs.end()) {
    return taskListIt->second;
  }
  DW_CORE_WARN("No such Task List exists");
  return m_BinList;
}

void ThreadManager::ThreadProcess(ThreadArg* argument) {
  while (argument->paused)
    ;
  while (!argument->paused) {
    if (!argument->tasks->IsEmpty()) {
      auto task = argument->tasks->PullTask();
      task->function();
    }
  }
  DW_CORE_FATAL("Thread id = {0} FINISHED!", (argument->id));
}

void ThreadManager::UnpauseThreads() {
  for (int i = 0; i < m_NumThreads; i++) {
    ThreadArg* k = &(m_ThreadArgs.at(i));
    k->paused = false;
  }
}

void ThreadManager::PauseThreads() {
  for (int i = 0; i < m_NumThreads; i++) {
    ThreadArg* k = &(m_ThreadArgs.at(i));
    k->paused = true;
  }
}

void ThreadManager::JoinThreads() {
  for (auto thread : m_ThreadList) {
    thread->join();
  }
}

void ThreadManager::CreateTaskLists() {
  for (int labelValue = 0; labelValue < m_NumThreads; ++labelValue) {
    // create task list
    auto taskRef = CreateRef<TaskList>();
    m_TaskListRefs.emplace(static_cast<TaskLabel>(labelValue), taskRef);
  }
}
void ThreadManager::RunThreads() {
  // create thread list
  for (int threadId = 0; threadId < m_NumThreads; ++threadId) {
    auto threadArg =
        ThreadArg(threadId, static_cast<TaskLabel>(threadId),
                  GetTaskListRef(static_cast<TaskLabel>(threadId)).get());
    m_ThreadArgs.push_back(threadArg);

    m_ThreadList[threadId] = new std::thread(
        &ThreadManager::ThreadProcess, this, &(m_ThreadArgs.at(threadId)));
  }
}

ThreadArg::ThreadArg(unsigned int id, TaskLabel label, TaskList* tasks)
    : id{id}, label{label}, tasks{tasks} {}
}  // namespace Dwarfworks

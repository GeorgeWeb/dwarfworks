#ifndef DWARFWORKS_APPLICATION_H_
#define DWARFWORKS_APPLICATION_H_

#include "core.h"

namespace dwarfworks {

class DWARFWORKS_API application {
  // represents the state of the application,
  // used to gracefully exit with a message
  enum class state : int { OK = 0, FAILED = 1, RUNNING = 2 };

 public:
  application();
  virtual ~application();

  // the application/game main loop
  void run();

  // function is defined inside the client sources
  // holds the logic for creating a new application
  friend application* create_app();

 private:
  state m_state{state::OK};

  // checks if the application initialization was 'OK'
  // designed to throw on state != OK
  void prepare_loop() noexcept(false);
};

}  // namespace dwarfworks

#endif  // DWARFWORKS_APPLICATION_H_

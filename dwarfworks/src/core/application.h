#ifndef DWARFWORKS_CORE_APPLICATION_H_
#define DWARFWORKS_CORE_APPLICATION_H_

#include "core.h"

namespace dwarfworks {

	class DWARFWORKS_API application {
	// represents the state of the application, 
	// used to gracefully exit with a message
	enum class state : int {
		OK = 0,
		FAILED = 1
	};
	public:
		application();
		virtual ~application();

		void run();

	private:
		state m_state = state::OK;
	};

	application* create_app();
}

#endif // DWARFWORKS_CORE_APPLICATION_H_
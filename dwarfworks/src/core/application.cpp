#include "application.h"

#include <stdio.h>

namespace dwarfworks {

	application::application() : m_state(state::OK)
	{
		// TODO: implement
	}

	application::~application()
	{
		// TODO: implement
	}

	void application::run()
	{
		printf("Running <dwarfworks> application\n");
		while (true);
	}
}

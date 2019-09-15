#ifndef DWARFWORKS_CORE_ENTRY_POINT_H_
#define DWARFWORKS_CORE_ENTRY_POINT_H_

#ifdef DWARFWORKS_PLATFORM_WINDOWS

extern dwarfworks::application* dwarfworks::create_app();

void main(int argc, char** argv) {
	auto app = dwarfworks::create_app();
	app->run();
	delete app;
}

#endif // DWARFWORKS_PLATFORM_WINDOWS


#endif // DWARFWORKS_CORE_ENTRY_POINT_H_
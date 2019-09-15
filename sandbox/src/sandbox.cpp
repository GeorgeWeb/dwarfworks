#include <dwarfworks.h>

class sandbox : public dwarfworks::application {
public:
	sandbox() = default;
	~sandbox() override = default;
};

dwarfworks::application* dwarfworks::create_app()
{
	return new sandbox();
}

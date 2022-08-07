#ifndef CORE_ENTRY_POINT_H
#define CORE_ENTRY_POINT_H

extern Dwarfworks::Scope<Dwarfworks::Application> Dwarfworks::CreateApplication();

auto main() -> int
{
    Dwarfworks::Log::Initialize();

    auto App = Dwarfworks::CreateApplication();
    App->GameLoop();

    return 0;
}

#endif // CORE_ENTRY_POINT_H

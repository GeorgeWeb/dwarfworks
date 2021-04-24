#ifndef CORE_ENTRY_POINT_H_
#define CORE_ENTRY_POINT_H_

extern Dwarfworks::Scope<Dwarfworks::Application> Dwarfworks::CreateApplication();

auto main() -> int32_t
{
    Dwarfworks::Log::Initialize();

    [] {
        return Dwarfworks::CreateApplication();
    }()
        ->GameLoop();

    return 0;
}

#endif // CORE_ENTRY_POINT_H_

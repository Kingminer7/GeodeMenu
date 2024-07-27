#include "ModuleKeybinds.hpp"

bool KeybindsMenuLayer::init()
{
    if (EOLModKeybinds::isKeybindsLoaded() && !EOLModKeybinds::hasSetupKeybinds)
        EOLModKeybinds::setupKeybinds();

    log::info("loaded keybinds: {}", EOLModKeybinds::isKeybindsLoaded());

    return MenuLayer::init();
}

bool EOLModKeybinds::isKeybindsLoaded()
{
    return Loader::get()->getLoadedMod("geode.custom-keybinds");
}

void EOLModKeybinds::setupKeybinds()
{
    hasSetupKeybinds = true;

    log::info("setting up keybinds");

    /*BindManager::get()->registerBindable({
        // ID, should be prefixed with mod ID
        "backlip"_spr,
        // Name
        "Do a Backflip!",
        // Description, leave empty for none
        "Throw a backflip",
        // Default binds
        { Keybind::create(KEY_Q, Modifier::None) },
        // Category; use slashes for specifying subcategories. See the
        // Category class for default categories
        "My Mod/Awesome Tricks"
    });

    new EventListener([=](InvokeBindEvent* event) {
        


	    return ListenerResult::Propagate;
    }, InvokeBindFilter(nullptr, "backlip"_spr));*/

    log::info("setup complete");
}
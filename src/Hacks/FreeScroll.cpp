#ifdef EOLMOD_FREESCROLL

#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>
#include "../Client/Client.h"

using namespace geode::prelude;

class $modify (EditorUI)
{
    struct Fields {
        Module* mod = nullptr;
    };

    void constrainGameLayerPosition()
    {
        if (!m_fields->mod)
            m_fields->mod = Client::GetModule("free-scroll");

        if (!m_fields->mod->enabled)
            EditorUI::constrainGameLayerPosition();
    }
};

#endif
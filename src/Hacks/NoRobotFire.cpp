#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include "../Client/Client.h"

using namespace geode::prelude;

class $modify (PlayerObject)
{
    virtual void update(float dt)
    {
        PlayerObject::update(dt);

        m_robotFire->setVisible(false);
        m_robotBurstParticles->setVisible(false);
    }

    EOLMOD_MOD_ALL_HOOKS("no-robot-fire")
};
#include <Geode/Geode.hpp>
#include <Geode/modify/HardStreak.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include "../Client/Client.h"

using namespace geode::prelude;

class $modify (HardStreak)
{
    void updateStroke(float p0)
    {
        if (LevelEditorLayer::get())
            m_drawStreak = true;

        HardStreak::updateStroke(p0);
    }

    EOLMOD_MOD_ALL_HOOKS("editor-wave-trail")
};

class $modify (PlayerObject)
{
    void placeStreakPoint()
    {
        if (LevelEditorLayer::get() && m_isDart)
            m_waveTrail->addPoint(this->getPosition());
        else
            PlayerObject::placeStreakPoint();
    }

    virtual void update(float dt)
    {
        PlayerObject::update(dt);

        if (LevelEditorLayer::get())
            m_waveTrail->m_currentPoint = this->getPosition();
    }

    EOLMOD_MOD_ALL_HOOKS("editor-wave-trail")
};
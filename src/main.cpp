#include <Geode/modify/CCKeyboardDispatcher.hpp>
#include "Client/AndroidUI.h"
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CCDictionary.hpp>
#include "Client/AndroidBall.h"
#include "Layers/SillyBaseLayer.h"

using namespace geode::prelude;
#include <Geode/modify/LoadingLayer.hpp>
#include "Keybinds/SetBindSetting.hpp"
#include "Keybinds/RecordKeyPopup.hpp"

#ifdef GEODE_IS_WINDOWS
//#define IMGUI
#endif

bool showing = false;

#ifdef IMGUI
bool android = false;
#else
bool android = true;
#endif

Client* client;

#ifndef GEODE_IS_IOS

class $modify (CCKeyboardDispatcher)
{
    bool dispatchKeyboardMSG(enumKeyCodes key, bool down, bool idk)
    {
        if (!CCScene::get())
            return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down, idk);

        if (!CCScene::get()->getChildByType<LoadingLayer>(0) && !CCScene::get()->getChildByType<RecordKeyPopup>(0))
        {
            bool v = false;

            std::vector<int> btns = { enumKeyCodes::KEY_Q };

            #ifdef QOLMOD_CUSTOM_KEYS_SETTING

            if (SetBindValue::instance)
                btns = SetBindValue::instance->buttons;

            #endif

            for (auto btn : btns)
            {
                if (btn == key)
                    v = true;
            }

            if (down && v && !idk)
            {
                if (Client::get()->useImGuiUI())
                {
                    Client::get()->toggleWindowVisibility(WindowTransitionType::Vertical);
                }
                else
                {
                    PlatformToolbox::showCursor();

                    if (auto ui = CCScene::get()->getChildByType<AndroidUI>(0))
                    {
                        // ui->onClose(nullptr);
                        ui->keyBackClicked();

                        if (PlayLayer::get() && !PlayLayer::get()->m_isPaused && !PlayLayer::get()->m_levelEndAnimationStarted && !GameManager::sharedState()->getGameVariable("0024"))
                            PlatformToolbox::hideCursor();
                    }
                    else
                    {
                        AndroidUI::addToScene();
                    }
                }
            }

            if (!CCScene::get()->getChildByType<AndroidUI>(0))
            {
                if (Client::get()->handleKeybinds(key, down, idk))
                    return false;
            }
        }

        return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down, idk);
    }
};

#endif

void migrateData()
{
    if (Mod::get()->getSavedValue<bool>("migrated"))
        return;
    
    auto path = Mod::get()->getSaveDir().string();
    path = utils::string::replace(path, Mod::get()->getID(), "TheSillyDoggo.Cheats");

    auto saved = path + "\\saved.json";
    auto savedNew = Mod::get()->getSaveDir().string() + "\\saved.json";

    log::debug("Old Config Path: {}", saved);
    log::debug("Old Config Path Exists: {}", std::filesystem::exists(saved));

    log::debug("Old Config Path: {}", savedNew);
    log::debug("Old Config Path Exists: {}", std::filesystem::exists(savedNew));

    if (std::filesystem::exists(saved))
    {
        auto res = std::filesystem::copy_file(saved, savedNew, std::filesystem::copy_options::skip_existing);

        log::debug("Copy saved results: {}", res);
    }

    auto res = Mod::get()->loadData();

    if (res.isErr())
        log::error("Error loading: {}", res.err());

    Mod::get()->setSavedValue<bool>("migrated", true);
}

$execute
{
    migrateData();

    client = new Client();
    Client::instance = client;

    ClientUtils::Setup(android);
}

bool v = false;

class $modify (MenuLayer)
{
    virtual bool init()
    {
        if (!MenuLayer::init())
            return false;

        if (!v)
        {
            if (Client::get()->useImGuiUI())
            {
                ImGuiCocos::get().setup([] {
                    Client::get()->initImGui();
                }).draw([] {
                    Client::get()->drawImGui();
                });
            }

            if (Client::GetModuleEnabled("save-pos"))
            {
                AndroidBall::position = ccp(Mod::get()->getSavedValue("posX", 32), Mod::get()->getSavedValue("posY", CCDirector::get()->getWinSize().height / 2));

                if (AndroidBall::position.x < 0)
                    AndroidBall::position.x = 0;

                if (AndroidBall::position.y < 0)
                    AndroidBall::position.y = 0;

                if (AndroidBall::position.x > CCDirector::get()->getWinSize().width)
                    AndroidBall::position.x = CCDirector::get()->getWinSize().width;

                if (AndroidBall::position.y > CCDirector::get()->getWinSize().height)
                    AndroidBall::position.y = CCDirector::get()->getWinSize().height;
            }
            else
            {
                AndroidBall::position = ccp(32, CCDirector::get()->getWinSize().height / 2);
            }
            
            v = true;
        }

        return true;
    }
};
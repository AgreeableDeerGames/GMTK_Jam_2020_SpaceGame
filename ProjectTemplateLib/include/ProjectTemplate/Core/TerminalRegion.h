#pragma once

#include <ProjectTemplate/Core/TemplateRegion.h>
#include <ProjectTemplate/Utils/DllUtils.h>

#include <GameBackbone/Core/GameRegion.h>
#include <GameBackbone/UserInput/GestureBind.h>

#include <SFML/System/Clock.hpp>

namespace PT
{
    class libProjectTemplate TerminalRegion : public PT::TemplateRegion
    {
    public:
        void update(sf::Int64 elapsedTime) override;

    private:
        void LogIn();
        void LogOut();

        GB::KeyboardGestureBind GeneratePasscode();

        bool isLoggedIn;
        // Passcode
        // Some Set of Inputs
        // Puzzle?
    };
}
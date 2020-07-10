#pragma once

#include <ProjectTemplate/Core/TemplateRegion.h>
#include <ProjectTemplate/Utils/DllUtils.h>

#include <GameBackbone/Core/GameRegion.h>
#include <GameBackbone/UserInput/GestureBind.h>


namespace PT
{
    class libProjectTemplate TerminalRegion : public PT::TemplateRegion
    {
    public:

    private:
        GB::KeyboardGestureBind GeneratePasscode();

        // Passcode
        // Some Set of Inputs
        // Puzzle?
    };
}
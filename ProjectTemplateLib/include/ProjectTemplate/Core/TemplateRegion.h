#pragma once

#include <ProjectTemplate/Utils/DllUtils.h>

#include <GameBackbone/Core/GameRegion.h>

#include <TGUI/Gui.hpp>

namespace PT
{
    class libProjectTemplate TemplateRegion : public GB::GameRegion
    {
    public:
        using GB::GameRegion::GameRegion;
        virtual ~TemplateRegion() = default;

        virtual tgui::Gui& GetGui() = 0;
    };
}
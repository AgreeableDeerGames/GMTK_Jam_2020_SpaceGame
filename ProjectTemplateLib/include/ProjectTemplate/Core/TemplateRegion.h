#pragma once

#include <ProjectTemplate/Utils/DllUtils.h>

#include <GameBackbone/Core/GameRegion.h>

#include <TGUI/Gui.hpp>

namespace PT
{
    class libProjectTemplate TemplateRegion : public GB::GameRegion
    {
    public:
        TemplateRegion(sf::RenderWindow& window) :
            m_gui(window)
        {
        }

        //GUI
        tgui::Gui m_gui;
    };
}
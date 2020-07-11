#pragma once

#include <ProjectTemplate/Core/TemplateRegion.h>
#include <ProjectTemplate/Core/InputRecorder.h>
#include <ProjectTemplate/Core/Terminal.h>
#include <ProjectTemplate/Core/Ship.h>
#include <ProjectTemplate/Utils/DllUtils.h>

#include <GameBackbone/Core/GameRegion.h>
#include <GameBackbone/UserInput/GestureBind.h>

#include <TGUI/TGUI.hpp>

#include <SFML/System/Clock.hpp>

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace PT
{
    class libProjectTemplate TerminalRegion : public PT::TemplateRegion
    {
    public:
        TerminalRegion(sf::RenderWindow& window, std::shared_ptr<Ship> ship, std::vector<Ship::Stat> trackedStats);
        TerminalRegion(const TerminalRegion&) = delete;
        TerminalRegion& operator=(const TerminalRegion&) = delete;

        bool handleEvent(sf::Int64 elapsedTime, const sf::Event& event) override;

        void update(sf::Int64 elapsedTime) override;

    protected:

        virtual void InitGui(const std::vector<Ship::Stat>& trackedStats);

        bool m_isInRecordState;
        std::function<void()> m_nextActionToBind;
        std::string m_nextActionNameToBind;
        InputRecorder m_recorder;

        Terminal m_terminal;

        std::shared_ptr<Ship> m_ship;
        std::map<Ship::Stat, tgui::ProgressBar::Ptr> m_visibleShipBars;
        tgui::TextBox::Ptr m_displayedTerminal;
    };
}
#pragma once

#include <ProjectTemplate/Core/TemplateRegion.h>
#include <ProjectTemplate/Core/InputRecorder.h>
#include <ProjectTemplate/Core/Terminal.h>
#include <ProjectTemplate/Utils/DllUtils.h>

#include <GameBackbone/Core/GameRegion.h>
#include <GameBackbone/UserInput/GestureBind.h>

#include <SFML/System/Clock.hpp>

#include <vector>
#include <memory>

namespace PT
{
    class libProjectTemplate TerminalRegion : public PT::TemplateRegion
    {
    public:
        TerminalRegion();
        TerminalRegion(const TerminalRegion&) = delete;
        TerminalRegion& operator=(const TerminalRegion&) = delete;

        bool handleEvent(sf::Int64 elapsedTime, const sf::Event& event) override;

        void update(sf::Int64 elapsedTime) override;

    private:

        bool m_isInRecordState;
        std::function<void()> m_nextActionToBind;
        InputRecorder m_recorder;

        std::vector<Terminal> m_terminals;
    };
}
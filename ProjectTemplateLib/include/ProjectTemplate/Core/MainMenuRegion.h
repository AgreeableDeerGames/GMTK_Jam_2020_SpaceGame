#pragma once

#include <ProjectTemplate/Utils/DllUtils.h>
#include <ProjectTemplate/Core/TemplateRegion.h>
#include <ProjectTemplate/Core/TerminalHub.h>

#include <TGUI/Gui.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>

namespace PT
{
	class EventController;

	class MainMenuRegion : public TemplateRegion
	{
	public:
		MainMenuRegion(EventController& eventController, sf::RenderWindow& window);

		bool handleEvent(sf::Int64 elapsedTime, const sf::Event& event) override;

		tgui::Gui& GetGui() override;

		void Reset();

	private:
		void InitGui();

		void InitHub();

		void SetRandomGameState();

		EventController& m_eventController;

		sf::RenderWindow& m_window;
		tgui::Gui m_gui;
		tgui::Theme m_defaultTheme;

		//std::unique_ptr<TerminalOne> m_tutorialRegion;
		std::unique_ptr<TerminalHub> m_hub;
	};
}
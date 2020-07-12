#pragma once

#include <ProjectTemplate/Utils/DllUtils.h>
#include <ProjectTemplate/Core/TemplateRegion.h>
#include <ProjectTemplate/Core/TerminalOne.h>

#include <TGUI/Gui.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>

namespace PT
{
	class MainMenuRegion : public TemplateRegion
	{
	public:
		MainMenuRegion(sf::RenderWindow& window);

		bool handleEvent(sf::Int64 elapsedTime, const sf::Event& event) override;

		tgui::Gui& GetGui() override;

		void Reset();

	private:
		void InitGui();

		sf::RenderWindow& m_window;
		tgui::Gui m_gui;
		tgui::Theme m_defaultTheme;
		std::unique_ptr<TerminalOne> m_tutorialRegion;
	};
}
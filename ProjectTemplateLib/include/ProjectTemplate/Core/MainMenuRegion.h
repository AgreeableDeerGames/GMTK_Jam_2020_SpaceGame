#pragma once

#include <ProjectTemplate/Utils/DllUtils.h>
#include <ProjectTemplate/Core/TemplateRegion.h>
#include <ProjectTemplate/Core/TerminalOne.h>

#include <TGUI/Gui.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

namespace PT
{
	class MainMenuRegion : public TemplateRegion
	{
	public:
		MainMenuRegion(sf::RenderWindow& window);

		bool handleEvent(sf::Int64 elapsedTime, const sf::Event& event) override;

		tgui::Gui& GetGui() override;

	private:
		void InitGui();

		tgui::Gui m_gui;
		tgui::Theme m_defaultTheme;
		TerminalOne m_tutorialRegion;
	};
}
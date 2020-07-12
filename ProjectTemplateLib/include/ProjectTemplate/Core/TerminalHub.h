#pragma once

#include <ProjectTemplate/Core/TemplateRegion.h>
#include <ProjectTemplate/Core/TerminalRegion.h>
#include <ProjectTemplate/Utils/DllUtils.h>

#include <memory>

namespace PT
{
	class libProjectTemplate TerminalHub : public TemplateRegion
	{
	public:
		TerminalHub(sf::RenderWindow& window, std::shared_ptr<Ship> ship, std::shared_ptr<DataPad> dataPad);
		TerminalHub(const TerminalHub&) = delete;
		TerminalHub& operator=(const TerminalHub&) = delete;
		TerminalHub(TerminalHub&&) noexcept = default;
		TerminalHub& operator=(TerminalHub&&) noexcept = default;

		tgui::Gui& GetGui() override;

		bool handleEvent(sf::Int64 elapsedTime, const sf::Event& event) override;

		// void update(sf::Int64 elapsedTime) override;

		// Functions to switch regions.
		void SwapToTerminalHub();
		void SwapToTerminalOne();
		void SwapToTerminalTwo();
		void SwapToTerminalThree();

		std::vector<std::unique_ptr<TerminalRegion>> m_regions;

		std::shared_ptr<DataPad> m_dataPad;
		// Set of binds to functions to switch regions. on the datapad

		std::shared_ptr<Ship> m_ship;

		Terminal m_terminal;
	};
}

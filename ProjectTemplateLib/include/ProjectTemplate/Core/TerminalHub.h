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

		// void update(sf::Int64 elapsedTime) override;

		// Functions to switch regions.
		void SwapToTerminalOne();

	private:
		std::vector<std::unique_ptr<TerminalRegion>> m_regions;

		std::shared_ptr<DataPad> m_dataPad;
		// Set of binds to functions to switch regions. on the datapad


		tgui::Gui m_gui;
	};
}
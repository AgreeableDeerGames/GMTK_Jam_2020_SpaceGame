#pragma once

#include <ProjectTemplate/Core/TemplateRegion.h>
#include <ProjectTemplate/Core/TerminalRegion.h>
#include <ProjectTemplate/Utils/DllUtils.h>


namespace PT
{
	class libProjectTemplate TerminalHub : public TemplateRegion
	{
	public:
		TerminalHub(sf::RenderWindow& window, std::shared_ptr<Ship> ship);
		TerminalHub(const TerminalHub&) = delete;
		TerminalHub& operator=(const TerminalHub&) = delete;
		TerminalHub(TerminalHub&&) noexcept = default;
		TerminalHub& operator=(TerminalHub&&) noexcept = default;

		// void update(sf::Int64 elapsedTime) override;

		// Functions to switch regions.

	private:
		std::vector<TerminalRegion> m_regions;


		// DataPad m_dataPad
		// Set of binds to functions to switch regions. on the datapad


		tgui::Gui m_gui;
	};
}

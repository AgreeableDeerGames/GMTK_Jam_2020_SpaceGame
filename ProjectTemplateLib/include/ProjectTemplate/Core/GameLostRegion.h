#pragma once

#include <ProjectTemplate/Core/Ship.h>
#include <ProjectTemplate/Core/Terminal.h>
#include <ProjectTemplate/Core/TemplateRegion.h>
#include <ProjectTemplate/Utils/DllUtils.h>

#include <TGUI/Gui.hpp>

#include <memory>

namespace PT
{
	class libProjectTemplate GameLostRegion : public TemplateRegion
	{
	public:
		GameLostRegion(sf::RenderWindow& window);

		void SetFinalShip(std::shared_ptr<Ship> finalShip);

		void SetFinalDataPad(std::shared_ptr<DataPad> finalDataPad);

		bool handleEvent(sf::Int64 elapsedTime, const sf::Event& event) override;

		tgui::Gui& GetGui() override;

	private:
		void InitGui();

		std::shared_ptr<Ship> m_ship;
		std::shared_ptr<DataPad> m_dataPad;
		tgui::Gui m_gui;
	};
}

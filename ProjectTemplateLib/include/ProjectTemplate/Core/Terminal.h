#pragma once

#include <ProjectTemplate/Core/DataPad.h>
#include <ProjectTemplate/Core/Ship.h>
#include <ProjectTemplate/Utils/DllUtils.h>
#include <ProjectTemplate/Utils/GestureBindUtils.h>

#include <GameBackbone/Core/Updatable.h>
#include <GameBackbone/UserInput/GestureBind.h>
#include <GameBackbone/UserInput/ButtonPressGestureHandler.h>

#include <TGUI/TGUI.hpp>

#include <SFML/Graphics.hpp>

#include <array>
#include <functional>
#include <memory>
#include <map>

namespace PT
{
	class libProjectTemplate Terminal : public sf::Drawable, public GB::Updatable, public GB::InputHandler
	{
	private:
		constexpr static inline std::size_t m_allowedBindCount = 9;
	public:
		Terminal(sf::RenderWindow& window, std::shared_ptr<Ship> ship, const std::vector<Ship::Stat>& trackedSats, std::shared_ptr<DataPad> dataPad);
		Terminal(const Terminal& other) = delete;
		Terminal(Terminal&& other) = default;
		Terminal& operator=(const Terminal& other) = delete;
		Terminal& operator=(Terminal&& other) noexcept = default;
		virtual ~Terminal() = default;

		void LogIn();
		void LogOut();

		void update(sf::Int64 elapsedTime) override;

		NumberGestureBind& GetPasscode();

		bool handleEvent(sf::Int64 elapsedTime, const sf::Event& event) override;

		void InitGui(const std::vector<Ship::Stat>& trackedStats);


		bool IsLoggedIn();

		tgui::Gui& GetGui();

		tgui::TextBox::Ptr m_displayedTerminal;
		tgui::TextBox::Ptr m_lastCommand;


	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		NumberGestureBind GeneratePasscode();

		bool m_isLoggedIn;

		NumberGestureBind m_passcode;

		tgui::Gui m_gui;
		std::map<Ship::Stat, tgui::ProgressBar::Ptr> m_visibleShipBars;
		std::map<Ship::Stat, tgui::Label::Ptr> m_visibleLabels;
		std::shared_ptr<Ship> m_ship;
		std::shared_ptr<DataPad> m_dataPad;
		tgui::Theme m_defaultTheme;
	};
}
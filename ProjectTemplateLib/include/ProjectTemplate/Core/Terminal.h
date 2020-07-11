#pragma once

#include <ProjectTemplate/Utils/DllUtils.h>
#include <ProjectTemplate/Core/Ship.h>

#include <GameBackbone/Core/Updatable.h>
#include <GameBackbone/UserInput/GestureBind.h>
#include <GameBackbone/UserInput/ButtonPressGestureHandler.h>

#include <SelbaWard.hpp>

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
		Terminal(sf::RenderWindow& window, const std::vector<Ship::Stat>& trackedSats, std::shared_ptr<Ship> ship);
		Terminal(const Terminal& other) = delete;
		Terminal(Terminal&& other) = default;
		Terminal& operator=(const Terminal& other) = delete;
		Terminal& operator=(Terminal&& other) noexcept = default;
		virtual ~Terminal() = default;

		void LogIn();
		void LogOut();

		void update(sf::Int64 elapsedTime) override;

		GB::KeyboardGestureBind& GetPasscode();

		bool handleEvent(sf::Int64 elapsedTime, const sf::Event& event) override;

		void AddBind(GB::KeyboardGestureBind bind);

		const GB::KeyboardGestureBind& GetBindWithName(const std::string& name);

		void InitGui(const std::vector<Ship::Stat>& trackedStats);

		void ReplaceBind(std::string name, GB::KeyboardGestureBind bind);

		// void ReplaceBind()

		bool IsLoggedIn();

		tgui::Gui& GetGui();

	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		GB::KeyboardGestureBind GeneratePasscode();
		void RegenerateControls();

		bool m_isLoggedIn;
		GB::KeyboardGestureBind m_passcode;

		// Dont use this to handle events. We just need this because 
		// GestureHandler doesn't have a way to change a single bind yet
		std::vector<GB::KeyboardGestureBind> m_bindVec;
		GB::KeyboardGestureHandler m_controls;
		tgui::Gui m_gui;
		std::map<Ship::Stat, tgui::ProgressBar::Ptr> m_visibleShipBars;
		tgui::TextBox::Ptr m_displayedTerminal;
		std::shared_ptr<Ship> m_ship;
	};
}
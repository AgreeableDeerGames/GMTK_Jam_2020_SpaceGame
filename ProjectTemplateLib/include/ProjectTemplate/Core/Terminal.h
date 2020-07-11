#pragma once

#include <ProjectTemplate/Utils/DllUtils.h>

#include <GameBackbone/Core/Updatable.h>
#include <GameBackbone/UserInput/GestureBind.h>
#include <GameBackbone/UserInput/ButtonPressGestureHandler.h>

#include <SelbaWard.hpp>

#include <SFML/Graphics.hpp>

#include <array>
#include <functional>
#include <memory>

namespace PT
{
	class libProjectTemplate Terminal : public sf::Drawable, public GB::Updatable
	{
	private:
		constexpr static inline std::size_t m_allowedBindCount = 9;
	public:
		Terminal();
		Terminal(const Terminal& other) = delete;
		Terminal(Terminal&& other) = default;
		Terminal& operator=(const Terminal& other) = delete;
		Terminal& operator=(Terminal&& other) noexcept = default;
		virtual ~Terminal() = default;

		void LogIn();
		void LogOut();

		void update(sf::Int64 elapsedTime) override;

		GB::KeyboardGestureBind& GetPasscode();


	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		GB::KeyboardGestureBind GeneratePasscode();

		bool m_isLoggedIn;
		selbaward::ConsoleScreen m_screen;
		sf::Texture m_screenTexture;
		GB::KeyboardGestureBind m_passcode;

		// Dont use this to handle events. We just need this because 
		// GestureHandler doesn't have a way to change a single bind yet
		std::vector<GB::KeyboardGestureBind> m_bindVec;
		GB::KeyboardGestureHandler m_controls;
	};
}
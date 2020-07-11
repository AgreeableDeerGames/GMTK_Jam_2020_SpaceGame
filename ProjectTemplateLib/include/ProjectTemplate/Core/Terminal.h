#pragma once

#include <ProjectTemplate/Utils/DllUtils.h>

#include <GameBackbone/Core/Updatable.h>
#include <GameBackbone/UserInput/GestureBind.h>

#include <SelbaWard.hpp>

#include <SFML/Graphics.hpp>

#include <memory>

namespace PT
{
	class libProjectTemplate Terminal : public sf::Drawable, public GB::Updatable
	{
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
	};
}
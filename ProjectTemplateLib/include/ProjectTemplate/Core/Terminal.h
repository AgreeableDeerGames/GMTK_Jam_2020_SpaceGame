#pragma once

#include <ProjectTemplate/Utils/DllUtils.h>
#include <ProjectTemplate/Utils/GestureBindUtils.h>


#include <GameBackbone/Core/Updatable.h>
#include <GameBackbone/UserInput/GestureBind.h>
#include <GameBackbone/UserInput/ButtonPressGestureHandler.h>

#include <SelbaWard.hpp>

#include <SFML/Graphics.hpp>

#include <array>
#include <functional>
#include <memory>
#include <optional>

namespace PT
{
	class libProjectTemplate Terminal : public sf::Drawable, public GB::Updatable, public GB::InputHandler
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

		NumberGestureBind& GetPasscode();

		bool handleEvent(sf::Int64 elapsedTime, const sf::Event& event) override;

		void AddBind(NumberGestureBind bind);

		const NumberGestureBind* GetBindWithName(const std::string& name);

		void ReplaceBind(std::string name, NumberGestureBind bind);

		// void ReplaceBind()

		bool IsLoggedIn();

	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		NumberGestureBind GeneratePasscode();
		void RegenerateControls();

		bool m_isLoggedIn;
		selbaward::ConsoleScreen m_screen;
		sf::Texture m_screenTexture;
		NumberGestureBind m_passcode;

		// Dont use this to handle events. We just need this because 
		// GestureHandler doesn't have a way to change a single bind yet
		std::vector<NumberGestureBind> m_bindVec;
		NumberGestureHandler m_controls;
	};
}
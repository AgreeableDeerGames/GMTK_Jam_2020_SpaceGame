#pragma once


#include <GameBackbone/UserInput/ButtonPressGestureHandler.h>
#include <GameBackbone/UserInput/GestureBind.h>

#include <SFML/Window/Event.hpp>

#include <string>
#include <unordered_map>

namespace PT {
	// Comparitor used to compare two button down or button up events for Numbers and Numpad Numbers
	class NumberComparator
	{
	public:
		bool operator()(const sf::Event& userEvent, const sf::Event& gestureEvent) const
		{
			// Short circuit if the type doesn't match or if the types are not handlable.
			if (userEvent.type != gestureEvent.type && userEvent.type != sf::Event::KeyPressed)
			{
				return false;
			}

			switch(gestureEvent.key.code)
			{
			case sf::Keyboard::Key::Numpad0:
			case sf::Keyboard::Key::Num0:
			{
				return (userEvent.key.code == sf::Keyboard::Key::Numpad0 || userEvent.key.code == sf::Keyboard::Key::Num0);
			}
			case sf::Keyboard::Key::Numpad1:
			case sf::Keyboard::Key::Num1:
			{
				return (userEvent.key.code == sf::Keyboard::Key::Numpad1 || userEvent.key.code == sf::Keyboard::Key::Num1);
			}
			case sf::Keyboard::Key::Numpad2:
			case sf::Keyboard::Key::Num2:
			{
				return (userEvent.key.code == sf::Keyboard::Key::Numpad2 || userEvent.key.code == sf::Keyboard::Key::Num2);
			}
			case sf::Keyboard::Key::Numpad3:
			case sf::Keyboard::Key::Num3:
			{
				return (userEvent.key.code == sf::Keyboard::Key::Numpad3 || userEvent.key.code == sf::Keyboard::Key::Num3);
			}
			case sf::Keyboard::Key::Numpad4:
			case sf::Keyboard::Key::Num4:
			{
				return (userEvent.key.code == sf::Keyboard::Key::Numpad4 || userEvent.key.code == sf::Keyboard::Key::Num4);
			}
			case sf::Keyboard::Key::Numpad5:
			case sf::Keyboard::Key::Num5:
			{
				return (userEvent.key.code == sf::Keyboard::Key::Numpad5 || userEvent.key.code == sf::Keyboard::Key::Num5);
			}
			case sf::Keyboard::Key::Numpad6:
			case sf::Keyboard::Key::Num6:
			{
				return (userEvent.key.code == sf::Keyboard::Key::Numpad6 || userEvent.key.code == sf::Keyboard::Key::Num6);
			}
			case sf::Keyboard::Key::Numpad7:
			case sf::Keyboard::Key::Num7:
			{
				return (userEvent.key.code == sf::Keyboard::Key::Numpad7 || userEvent.key.code == sf::Keyboard::Key::Num7);
			}
			case sf::Keyboard::Key::Numpad8:
			case sf::Keyboard::Key::Num8:
			{
				return (userEvent.key.code == sf::Keyboard::Key::Numpad8 || userEvent.key.code == sf::Keyboard::Key::Num8);
			}
			case sf::Keyboard::Key::Numpad9:
			case sf::Keyboard::Key::Num9:
			{
				return (userEvent.key.code == sf::Keyboard::Key::Numpad9 || userEvent.key.code == sf::Keyboard::Key::Num9);
			}
			default:
			{
				return false;
			}
			}

			// Return true if the buttons match
			return (userEvent.key.code == gestureEvent.key.code && userEvent.key.code != sf::Keyboard::Unknown);
		}
	};

	// Typedef for GestureBind and InputHandler
	using NumberGestureBind = GB::BasicGestureBind<NumberComparator>;
	using NumberGestureHandler = GB::ButtonPressGestureHandler<NumberGestureBind>;

	// 
	inline std::string StringifyGesture(NumberGestureBind boundGesture)
	{
		static std::unordered_map<sf::Keyboard::Key, std::string> keyMapping
		{
			{ sf::Keyboard::Key::Numpad0, "0" },
			{ sf::Keyboard::Key::Numpad1, "1" },
			{ sf::Keyboard::Key::Numpad2, "2" },
			{ sf::Keyboard::Key::Numpad3, "3" },
			{ sf::Keyboard::Key::Numpad4, "4" },
			{ sf::Keyboard::Key::Numpad5, "5" },
			{ sf::Keyboard::Key::Numpad6, "6" },
			{ sf::Keyboard::Key::Numpad7, "7" },
			{ sf::Keyboard::Key::Numpad8, "8" },
			{ sf::Keyboard::Key::Numpad9, "9" },
			{ sf::Keyboard::Key::Num0, "0" },
			{ sf::Keyboard::Key::Num1, "1" },
			{ sf::Keyboard::Key::Num2, "2" },
			{ sf::Keyboard::Key::Num3, "3" },
			{ sf::Keyboard::Key::Num4, "4" },
			{ sf::Keyboard::Key::Num5, "5" },
			{ sf::Keyboard::Key::Num6, "6" },
			{ sf::Keyboard::Key::Num7, "7" },
			{ sf::Keyboard::Key::Num8, "8" },
			{ sf::Keyboard::Key::Num9, "9" }
		};

		std::string returnString = "";

		for (const sf::Event& event : boundGesture.getGesture())
		{
			returnString.append(keyMapping[event.key.code]);
		}

		return returnString;
	}
}
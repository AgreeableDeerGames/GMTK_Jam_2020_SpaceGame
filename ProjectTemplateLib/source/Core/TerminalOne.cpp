#include <ProjectTemplate/Core/TerminalOne.h>

using namespace PT;

TerminalOne::TerminalOne(std::shared_ptr<Ship> ship) : TerminalRegion(ship)
{
	// Add sprinkler bind to the vector of binds.

	std::vector<sf::Event> bindKeys;

	sf::Event eventForKey = {};
	eventForKey.key = sf::Event::KeyEvent{ sf::Keyboard::Key::Numpad1, false, false, false, false };
	eventForKey.type = sf::Event::KeyPressed;

	// Push the event into the vector
	bindKeys.push_back(eventForKey);
	std::function<void()> action = [this](){ TurnOnSprinklers(); };
	std::string name = "Sprinkler Bind";
	sf::Int64 maxTimeBetweenInputs = 1000;
	GB::KeyboardGestureBind::EndType endType = GB::KeyboardGestureBind::EndType::Block;
	GB::KeyboardGestureBind returnBind{
		bindKeys,
		action,
		name,
		maxTimeBetweenInputs,
		endType
	};

	m_terminal.AddBind(returnBind);
}

void TerminalOne::TurnOnSprinklers()
{
	m_ship->m_areSprinklersOn = true;
}
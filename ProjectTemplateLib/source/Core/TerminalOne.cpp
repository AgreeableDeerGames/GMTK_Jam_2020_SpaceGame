#include <ProjectTemplate/Core/TerminalOne.h>

using namespace PT;

TerminalOne::TerminalOne(std::shared_ptr<Ship> ship) : m_isInitialized(false), TerminalRegion(ship)
{
	// Put us in a state of binding.
	m_isInRecordState = true;
	m_nextActionToBind = [this]() { TurnOnSprinklers(); };
	m_nextActionNameToBind = "Sprinkler Bind";


	// Example of how to force a particular bind.
	// Add sprinkler bind to the vector of binds.
	/*std::vector<sf::Event> bindKeys;

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

	m_terminal.AddBind(returnBind);*/
}

void TerminalOne::update(sf::Int64 elapsedTime)
{
	if (!m_isInitialized)
	{
		// Teach the user how to Log Into the first console
		
		if (m_terminal.IsLoggedIn())
		{
			// Tell the user about the first problem.

			// Teach them how to bind a key

			// Have them use their bound key to fix the problem

			//if (problem is fixed)
			{
				// Introduce the concept of switching terminals

				// Have the user bind the old and new terminals to their numpad. repeat
			}
		}
	}


}


void TerminalOne::TurnOnSprinklers()
{
	m_ship->m_areSprinklersOn = true;
}
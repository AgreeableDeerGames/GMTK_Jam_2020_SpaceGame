#include <ProjectTemplate/Core/TerminalOne.h>

#include <ProjectTemplate/Utils/DisplayText.h>
#include <ProjectTemplate/Utils/GestureBindUtils.h>

using namespace PT;

TerminalOne::TerminalOne(sf::RenderWindow& window, std::shared_ptr<Ship> ship) : m_isInitialized(false),
	TerminalRegion(window, ship, {Ship::Stat::water, Ship::Stat::fires})
{
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
	TerminalRegion::update(elapsedTime);

	if (!m_isInitialized)
	{
		if (!m_terminal.IsLoggedIn())
		{
			// Teach the user how to Log Into the first console
			m_displayedTerminal->setText(std::string(terminalOne_Welcome));
			m_displayedTerminal->addText(StringifyGesture(m_terminal.GetPasscode()));
			m_displayedTerminal->addText("\n\n");
			m_displayedTerminal->addText(std::string(terminalOne_LogIn));
		}
		else
		{
			// if (/*bind does not exist*/)
			{
				// Tell the user about the first problem.
				m_displayedTerminal->setText(std::string(logInSuccessful));
				m_displayedTerminal->addText("\n\n");


				// Teach them how to bind a key
				m_displayedTerminal->addText(std::string(terminalOne_FireBind));

				// Have them use their bound key to fix the problem
				// Put us in a state of binding.
				m_isInRecordState = true;
				m_nextActionToBind = [this]() { TurnOnSprinklers(); };
				m_nextActionNameToBind = "Sprinkler Bind";
			}
			//else
			{
				m_displayedTerminal->setText(std::string(logInSuccessful));
			}
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
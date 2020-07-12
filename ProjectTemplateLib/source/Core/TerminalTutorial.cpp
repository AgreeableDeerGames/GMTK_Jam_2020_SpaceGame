#include <ProjectTemplate/Core/TerminalTutorial.h>

#include <ProjectTemplate/Core/EventController.h>
#include <ProjectTemplate/Utils/DisplayText.h>
#include <ProjectTemplate/Utils/GestureBindUtils.h>

using namespace PT;

TerminalTutorial::TerminalTutorial(sf::RenderWindow & window, std::shared_ptr<Ship> ship, std::shared_ptr<DataPad> dataPad) :
	TerminalRegion(
		window,
		ship,
		{
			Ship::Stat::water,
			Ship::Stat::fires,
			Ship::Stat::oxygen,
			Ship::Stat::hullIntegrity,
			Ship::Stat::temperature,
			Ship::Stat::nanites,
			Ship::Stat::radiation,
			Ship::Stat::bacteria 
		}, 
		dataPad),

	m_isInitialized(false), 
	m_fireInitialized(false)
{
	//m_terminal.AddBind()

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
	sf::Int64 maxTimeBetweenInputs = 1000000;
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

void TerminalTutorial::update(sf::Int64 elapsedTime)
{
	TerminalRegion::update(elapsedTime);

	if (!m_isInitialized)
	{
		if (!m_terminal.IsLoggedIn())
		{
			// Teach the user how to Log Into the first console
			m_terminal.m_displayedTerminal->setText(std::string(terminalTutorial_Welcome));
			m_terminal.m_displayedTerminal->addText(StringifyGesture(m_terminal.GetPasscode()));
			m_terminal.m_displayedTerminal->addText("\n\n");
			m_terminal.m_displayedTerminal->addText(std::string(terminalTutorial_LogIn));
		}
		else
		{
			const NumberGestureBind* bind = m_dataPad->GetBindWithName("Sprinkler Bind");
			if (bind == nullptr)
			{
				// Tell the user about the first problem.
				m_terminal.m_displayedTerminal->setText(std::string(logInSuccessful));
				m_terminal.m_displayedTerminal->addText("\n\n");


				// Teach them how to bind a key
				m_terminal.m_displayedTerminal->addText(std::string(terminalTutorial_FireBind));

				// Have them use their bound key to fix the problem
				// Put us in a state of binding.
				m_isInRecordState = true;
				m_nextActionToBind = [this]() { TurnOnSprinklers(); };
				m_nextActionNameToBind = "Sprinkler Bind";
			}
			else
			{
				if (!m_ship->m_areSprinklersOn)
				{
					m_terminal.m_displayedTerminal->setText(std::string(terminalTutorial_FireBound));
					m_terminal.m_displayedTerminal->addText(StringifyGesture(*bind));

					m_terminal.m_displayedTerminal->addText("\n\n");
					m_terminal.m_displayedTerminal->addText(std::string(terminalTutorial_FireRequest));
					if (!m_fireInitialized)
					{
						m_ship->m_stats[Ship::Stat::fires] = 8;
						m_fireInitialized = true;
					}
				}
				else
				{
					if (m_ship->m_stats[Ship::Stat::fires] != 0)
					{
						// Congratulate the user on following directions!
						m_terminal.m_displayedTerminal->setText(std::string(terminalTutorial_FireOut));

						m_terminal.m_displayedTerminal->addText("\n\n");
						m_terminal.m_displayedTerminal->addText("Wait for the fire to go out.");
					}
					else
					{
						// Introduce the concept of switching terminals
						m_terminal.m_displayedTerminal->setText("Bind the Log Out Key and use it to log out. Then Start a New Game. Enjoy!");

						const NumberGestureBind* bind = m_dataPad->GetBindWithName("Log Out");
						if (bind == nullptr)
						{
							// Have them use their bound key to fix the problem
							// Put us in a state of binding.
							m_isInRecordState = true;
							m_nextActionToBind = [this]() { BackOutToMainMenu(); };
							m_nextActionNameToBind = "Log Out";
						}
					}

				}
			}
		}
	}


}


void TerminalTutorial::TurnOnSprinklers()
{
	m_ship->m_areSprinklersOn = true;
}

void TerminalTutorial::BackOutToMainMenu()
{
	this->setNextRegion(*EventController::GetGlobalBeatTutorialRegion());
}
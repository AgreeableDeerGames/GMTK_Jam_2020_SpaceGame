#include <ProjectTemplate/Core/TerminalRegion.h>

#include <GameBackbone/Util/RandGen.h>

#include <vector>

using namespace PT;

void TerminalRegion::update(sf::Int64 elapsedTime)
{
	if (isLoggedIn)
	{
		// showPuzzle();
	}
	else
	{
		// awaitKeyInput();
	}
}

void  TerminalRegion::LogIn()
{
	// Display Log In Message for a certain amount of time

	// Set the "isLoggedIn" flag to true
	isLoggedIn = true;
}

void  TerminalRegion::LogOut()
{
	// Display Log Out Message for a certain amount of time
	
	// Set the "isLoggedIn" flag to false
	isLoggedIn = false;
}

GB::KeyboardGestureBind TerminalRegion::GeneratePasscode()
{
	static std::vector<sf::Keyboard::Key> keyMapping
	{
		sf::Keyboard::Key::Num0,
		sf::Keyboard::Key::Num1,
		sf::Keyboard::Key::Num2,
		sf::Keyboard::Key::Num3,
		sf::Keyboard::Key::Num4,
		sf::Keyboard::Key::Num5,
		sf::Keyboard::Key::Num6,
		sf::Keyboard::Key::Num7,
		sf::Keyboard::Key::Num8,
		sf::Keyboard::Key::Num9
	};

	GB::RandGen generator;
	std::vector<sf::Event> bindKeys;
	for (int ii = 0; ii < 4; ii++)
	{
		// Randomly generate a number from 0-9
		int randNum = generator.uniDist(0, 10);

		// Get the correct key for the number and create an event
		sf::Event eventForKey = {};
		eventForKey.key = sf::Event::KeyEvent{ keyMapping.at(randNum), false, false, false, false };

		// Push the event into the vector
		bindKeys.push_back(eventForKey);
	}

	std::function<void()> action = [this]() {LogIn(); };
	std::string name = "Passcode";
	sf::Int64 maxTimeBetweenInputs = 1000;
	GB::KeyboardGestureBind::EndType endType = GB::KeyboardGestureBind::EndType::Block;

	return GB::KeyboardGestureBind
	{ 
		bindKeys,
		action,
		name,
		maxTimeBetweenInputs,
		endType
	};
}


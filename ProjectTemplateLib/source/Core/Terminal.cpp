#include <ProjectTemplate/Core/Terminal.h>

#include <GameBackbone/Util/RandGen.h>

PT::Terminal::Terminal() :
	m_screen({ 25, 20 })
{
	m_screenTexture.loadFromFile("Textures/resources/WindowsConsoleASCII.png");
	m_screen.setTexture(m_screenTexture, 16, { 8, 12 }); // texture, number of tiles per row, tile size
	m_screen.setSize({ 256.0f, 256.0f }); // scaled x2
	m_screen.setShowCursor(false);
}

void PT::Terminal::LogIn()
{
	m_isLoggedIn = true;
}

void PT::Terminal::LogOut()
{
	m_isLoggedIn = false;
}

void PT::Terminal::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_screen, states);
}

void PT::Terminal::update(sf::Int64 elapsedTime)
{
	//stringToPrint.at(m_screen.getCursorValue());
	std::string stringToPrint = "Test String";

	/*int value = m_screen.getCursorValue();
	m_screen << Cs::Char(stringToPrint.at(value)) << Cs::Right();*/
	m_screen.setMappedCursorCommandCharacter('\n', Cs::CursorCommand::Newline);
	m_screen << Cs::Direct::Begin << Cs::Location(0,0)
		<<
		"TEST\nTEST\nTEST\nTEST\nTEST\nTEST\nTEST\nTEST\nTEST\nTEST\nTEST\nTEST\nTEST\nTEST\nTEST\nTEST\nTEST\nTEST\nTEST\nTEST\nTEST\nTEST\nTEST\nTEST\nTEST\nTEST\nTEST\nTEST\nTEST\nTEST\n"
		
		<<
		Cs::Direct::End;
}

GB::KeyboardGestureBind PT::Terminal::GeneratePasscode()
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


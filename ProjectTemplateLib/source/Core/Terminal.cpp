#include <ProjectTemplate/Core/Terminal.h>

#include <GameBackbone/Util/RandGen.h>

#include <stdexcept>

PT::Terminal::Terminal() :
	m_isLoggedIn(false),
	m_screen({ 25, 20 }),
	m_screenTexture(),
	m_passcode(GeneratePasscode()),
	m_bindVec(),
	m_controls()
{
	m_screenTexture.loadFromFile("Textures/resources/WindowsConsoleASCII.png");
	m_screen.setTexture(m_screenTexture, 16, { 8, 12 }); // texture, number of tiles per row, tile size
	m_screen.setSize({ 256.0f, 256.0f }); // scaled x2
	m_screen.setShowCursor(false);



}

void PT::Terminal::AddBind(GB::KeyboardGestureBind bind)
{
	m_bindVec.emplace_back(std::move(bind));
	RegenerateControls();
}

void PT::Terminal::ReplaceBind(std::string name, GB::KeyboardGestureBind bind)
{
	bind.setName(name);
	auto found = std::find_if(
		std::begin(m_bindVec),
		std::end(m_bindVec),
		[&](const GB::KeyboardGestureBind& value) {return value.getName() == name; });

	if (found != std::end(m_bindVec))
	{
		*found = bind;
		RegenerateControls();
	}
	else
	{
		throw std::runtime_error("could not find bind to replace");
	}
}

const GB::KeyboardGestureBind& PT::Terminal::GetBindWithName(const std::string& name)
{
	auto found = std::find_if(
		std::begin(m_bindVec),
		std::end(m_bindVec),
		[&](const GB::KeyboardGestureBind& value) {return value.getName() == name; });
	return* found;
}

void PT::Terminal::LogIn()
{
	// Print Logged In
	std::cout << "Logged In.\n";

	m_isLoggedIn = true;
}

void PT::Terminal::LogOut()
{
	// Print Logged In
	std::cout << "Logged Out.\n";

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
		sf::Keyboard::Key::Numpad0,
		sf::Keyboard::Key::Numpad1,
		sf::Keyboard::Key::Numpad2,
		sf::Keyboard::Key::Numpad3,
		sf::Keyboard::Key::Numpad4,
		sf::Keyboard::Key::Numpad5,
		sf::Keyboard::Key::Numpad6,
		sf::Keyboard::Key::Numpad7,
		sf::Keyboard::Key::Numpad8,
		sf::Keyboard::Key::Numpad9
	};

	GB::RandGen generator;
	std::vector<sf::Event> bindKeys;
	for (int ii = 0; ii < 4; ii++)
	{
		// Randomly generate a number from 0-9
		int randNum = generator.uniDist(0, 10);
		std::cout << randNum << " ";

		// Get the correct key for the number and create an event
		sf::Event eventForKey = {};
		eventForKey.key = sf::Event::KeyEvent{ keyMapping.at(randNum), false, false, false, false };
		eventForKey.type = sf::Event::KeyPressed;

		// Push the event into the vector
		bindKeys.push_back(eventForKey);
	}

	std::function<void()> action = [this]() { LogIn(); };
	std::string name = "Passcode";
	sf::Int64 maxTimeBetweenInputs = 1000000;
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

bool PT::Terminal::handleEvent(sf::Int64 elapsedTime, const sf::Event& event)
{
	if (m_isLoggedIn)
	{
		return m_controls.handleEvent(elapsedTime, event);
	}

	if (event.type == sf::Event::KeyPressed)
	{
		auto result = m_passcode.processEvent(elapsedTime, event);
		if (!result.readyForInput)
		{
			std::cout << "Loggin Failed. Resetting Passcode.\n";
			m_passcode.reset();
		}

		return result.inputConsumed;
	}
	return false;
}


void PT::Terminal::RegenerateControls()
{
	GB::KeyboardGestureHandler newControls;
	for (const auto& bind : m_bindVec)
	{
		newControls.addGesture(bind);
	}
	m_controls = std::move(newControls);
}


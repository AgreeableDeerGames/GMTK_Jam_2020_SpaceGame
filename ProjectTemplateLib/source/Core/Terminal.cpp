#include <ProjectTemplate/Core/Terminal.h>
#include <ProjectTemplate/Utils/GestureBindUtils.h>

#include <GameBackbone/Util/RandGen.h>

#include <stdexcept>
#include <optional>

using namespace PT;

Terminal::Terminal(sf::RenderWindow& window, const std::vector<Ship::Stat>& trackedSats, std::shared_ptr<Ship> ship) :
	m_displayedTerminal(),
	m_isLoggedIn(false),
	m_passcode(GeneratePasscode()),
	m_bindVec(),
	m_controls(),
	m_gui(window),
	m_visibleShipBars(),
	m_ship(std::move(ship))
{
	InitGui(trackedSats);
}

void Terminal::AddBind(NumberGestureBind bind)
{
	m_bindVec.emplace_back(std::move(bind));
	RegenerateControls();
}

void Terminal::ReplaceBind(std::string name, NumberGestureBind bind)
{
	bind.setName(name);
	auto found = std::find_if(
		std::begin(m_bindVec),
		std::end(m_bindVec),
		[&](const NumberGestureBind& value) {return value.getName() == name; });

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

const NumberGestureBind* Terminal::GetBindWithName(const std::string& name)
{
	auto found = std::find_if(
		std::begin(m_bindVec),
		std::end(m_bindVec),
		[&](const NumberGestureBind& value) {return value.getName() == name; });
	if (found == std::end(m_bindVec))
	{
		return nullptr;
	}
	return &(*found);
}

void Terminal::LogIn()
{
	// Print Logged In
	std::cout << "Logged In.\n";

	for (auto& [category, statusBar] : m_visibleShipBars)
	{
		statusBar->setVisible(true);
	}
	for (auto& [category, label] : m_visibleLabels)
	{
		label->setVisible(true);
	}
	m_isLoggedIn = true;
}

void Terminal::LogOut()
{
	// Print Logged In
	std::cout << "Logged Out.\n";
	for (auto& [category, statusBar] : m_visibleShipBars)
	{
		statusBar->setVisible(false);
	}
	for (auto& [category, label] : m_visibleLabels)
	{
		label->setVisible(false);
	}

	m_isLoggedIn = false;
}

void Terminal::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void Terminal::update(sf::Int64 elapsedTime)
{
	// update gui
	for (auto& [key, value] : m_visibleShipBars)
	{
		m_visibleShipBars.at(key)->setValue(m_ship->m_stats[key]);
	}
}

NumberGestureBind Terminal::GeneratePasscode()
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
	NumberGestureBind::EndType endType = NumberGestureBind::EndType::Block;

	return NumberGestureBind
	{
		bindKeys,
		action,
		name,
		maxTimeBetweenInputs,
		endType
	};
}

bool Terminal::handleEvent(sf::Int64 elapsedTime, const sf::Event& event)
{
	m_gui.handleEvent(event);

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


void Terminal::RegenerateControls()
{
	NumberGestureHandler newControls;
	for (const auto& bind : m_bindVec)
	{
		newControls.addGesture(bind);
	}
	m_controls = std::move(newControls);
}

bool Terminal::IsLoggedIn()
{
	return m_isLoggedIn;
}

tgui::Gui& Terminal::GetGui()
{
	return m_gui;
}

void Terminal::InitGui(const std::vector<Ship::Stat>& trackedStats)
{
	m_gui.removeAllWidgets();

	tgui::Theme theme("TGUI_Widgets/Black.txt");
	// Get a bound version of the window size
	// Passing this to setPosition or setSize will make the widget automatically update when the view of the gui changes
	tgui::Layout windowWidth = tgui::bindWidth(this->m_gui);
	tgui::Layout windowHeight = tgui::bindHeight(this->m_gui);

	// Add progress bars for stats
	for (std::size_t i = 0; i < trackedStats.size(); ++i)
	{
		tgui::Layout progressBarWidth = windowWidth / 3;
		tgui::Layout progressBarHeight = windowHeight / 25;

		auto label =  tgui::Label::create();
		label->setRenderer(theme.getRenderer("Label"));
		label->setSize({ progressBarWidth, progressBarHeight });
		label->setPosition(1.25* windowWidth / 25, (progressBarHeight / 2) + progressBarHeight * (1.75 * i));
		label->setText(m_ship->GetStatName(trackedStats[i]));
		label->setVisible(false);
		m_gui.add(label);


		auto progressBar = tgui::ProgressBar::create();
		progressBar->setRenderer(theme.getRenderer("ProgressBar"));
		progressBar->setSize({ progressBarWidth, progressBarHeight });
		progressBar->setPosition(windowWidth / 25, 2 * (progressBarHeight / 2) + progressBarHeight * (1.75 * i));
		progressBar->setVisible(false);
		m_gui.add(progressBar);

		m_visibleShipBars[trackedStats[i]] = progressBar;
		m_visibleLabels[trackedStats[i]] = label;
	}

	// TODO: Center this.
	m_displayedTerminal = tgui::TextBox::create();
	m_displayedTerminal->setEnabled(false);
	m_displayedTerminal->setSize(windowWidth * 0.9, windowHeight * 0.25);
	m_displayedTerminal->setPosition(25, 500);
	m_displayedTerminal->setText("SOME TEXT");
	m_gui.add(m_displayedTerminal);
}

NumberGestureBind& Terminal::GetPasscode()
{
	return m_passcode;
}
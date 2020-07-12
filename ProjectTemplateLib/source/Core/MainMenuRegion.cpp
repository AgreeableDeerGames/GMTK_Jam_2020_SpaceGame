#include <ProjectTemplate/Core/MainMenuRegion.h>
#include <ProjectTemplate/Core/Ship.h>
#include <ProjectTemplate/Core/ShipControlTerminalRegion.h>
#include <ProjectTemplate/Core/DataPad.h>

#include <GameBackbone/Util/RandGen.h>

#include <TGUI/TGUI.hpp>


#include <memory>

using namespace PT;

MainMenuRegion::MainMenuRegion(sf::RenderWindow& window) : 
	m_window(window),
	m_gui(window),
	m_defaultTheme(),
	m_hub(std::make_unique<TerminalHub>(window, std::make_shared<Ship>(), std::make_shared<DataPad>()))
{
	InitGui();
	InitHub();
}

bool MainMenuRegion::handleEvent(sf::Int64 elapsedTime, const sf::Event& event)
{
	return m_gui.handleEvent(event);
}

tgui::Gui& MainMenuRegion::GetGui()
{
	return m_gui;
}

void MainMenuRegion::InitGui()
{
	m_gui.removeAllWidgets();

	// Load the black theme
	m_defaultTheme.load("TGUI_Widgets/Black.txt");

	// By setting this as the default theme all widgets created after this point will be created with this theme.
	// After defaultTheme deconstructs all widgets that are using the default theme will be reset to white theme.
	// This is ok for this use case because defaultTheme wont be destructed until the end of the program.
	tgui::Theme::setDefault(&m_defaultTheme);

	// Get a bound version of the window size
	// Passing this to setPosition or setSize will make the widget automatically update when the view of the gui changes
	tgui::Layout windowWidth = tgui::bindWidth(m_gui);
	tgui::Layout windowHeight = tgui::bindHeight(m_gui);

	// Add buttons for each game mode
	std::vector<tgui::Button::Ptr> gameModeButtons;

	// Create tutorial
	tgui::Button::Ptr tutorialButton = tgui::Button::create();
	tutorialButton->setText("Tutorial");
	tutorialButton->connect("pressed", [this]()
	{
		this->setNextRegion(*m_hub);
		m_hub->SwapToTerminalOne();
	});
	gameModeButtons.push_back(tutorialButton);

	// Create main game
	tgui::Button::Ptr newGameButton = tgui::Button::create();
	newGameButton->setText("New Game");
	newGameButton->connect("pressed", [this]()
		{
			// remove tutorial
			m_hub->m_regions.erase(m_hub->m_regions.begin());

			// Randomize ship state
			SetRandomGameState();

			this->setNextRegion(*m_hub);
			m_hub->SwapToTerminalOne();
			static_cast<ShipControlTerminalRegion&>(m_hub->getNextRegion()).m_shouldBindLogOff = true;
			static_cast<ShipControlTerminalRegion&>(m_hub->getNextRegion()).m_nextActionToBind = [this]() {m_hub->SwapToTerminalHub(); };
			static_cast<ShipControlTerminalRegion&>(m_hub->getNextRegion()).m_nextActionNameToBind = "Log Off";
		});
	gameModeButtons.push_back(newGameButton);

	// Size and place buttons
	// The number of buttons will be needed a few times. Calculate it once.
	const std::size_t demoRegionButtonCount = gameModeButtons.size();
	// The buttons should be 1/4 the width of the screen
	tgui::Layout buttonWidth = windowWidth / 4.0f;
	// Adjust the height of the buttons so that they can all fit on screen
	tgui::Layout buttonHeight = windowHeight / ((float)demoRegionButtonCount * 2 + 1);
	for (std::size_t i = 0; i < demoRegionButtonCount; ++i)
	{
		// Save some repetitive typing
		auto& currentButton = gameModeButtons.at(i);
		// Set the size of the button
		currentButton->setSize(buttonWidth, buttonHeight);
		// Place the button in the middle of the screen
		tgui::Layout horizontalPosition = windowWidth / 2.0f - buttonWidth / 2.0f;
		// Space the buttons apart
		tgui::Layout verticalPosition = (2 * i + 1) * buttonHeight;
		currentButton->setPosition(horizontalPosition, verticalPosition);
		// Add the buttons to the GUI
		m_gui.add(currentButton);
	}
}

void MainMenuRegion::Reset()
{
	m_hub = std::make_unique<TerminalHub>(m_window, std::make_shared<Ship>(), std::make_shared<DataPad>());
	InitGui();
}

void MainMenuRegion::InitHub()
{
	m_hub->m_regions.emplace_back(
		std::make_unique<ShipControlTerminalRegion>(
			m_window,
			m_hub->m_ship,
			std::vector<Ship::Stat>
			{
				Ship::Stat::oxygen,
				Ship::Stat::fires,
				Ship::Stat::hullIntegrity,
				Ship::Stat::water
			},
			m_hub->m_dataPad,
			std::unordered_map<std::string, std::function<void()>>
			{
				{"Turn on sprinklers", []() {}},
				{"Turn off sprinklers", []() {}},
			},
			"Engine Room"
		)
	);

	m_hub->m_regions.emplace_back(
		std::make_unique<ShipControlTerminalRegion>(
			m_window,
			m_hub->m_ship,
			std::vector<Ship::Stat>
			{
				Ship::Stat::oxygen,
				Ship::Stat::temperature,
				Ship::Stat::bacteria,
				Ship::Stat::radiation,
			},
			m_hub->m_dataPad,
			std::unordered_map<std::string, std::function<void()>>
			{
				{"Release Bacteria", []() {}},
				{"Stop Releasing Bacteria", []() {}},
			},
			"Bio Lab"
		)
	);

	m_hub->m_regions.emplace_back(
		std::make_unique<ShipControlTerminalRegion>(
			m_window,
			m_hub->m_ship,
			std::vector<Ship::Stat>
			{
				Ship::Stat::temperature,
				Ship::Stat::nanites,
				Ship::Stat::hullIntegrity
			},
			m_hub->m_dataPad,
			std::unordered_map<std::string, std::function<void()>>
			{
				{"Release Nanites", []() {}},
				{"Stop Releasing Nanites", []() {}},
			},
			"Engineering Lab"
		)
	);
}


void MainMenuRegion::SetRandomGameState()
{
	auto ship = m_hub->m_ship;

	GB::RandGen rand;
	ship->m_stats[Ship::Stat::bacteria] = rand.uniDist(0.0, 20.0);
	ship->m_stats[Ship::Stat::radiation] = rand.uniDist(0.0, 20.0);
	ship->m_stats[Ship::Stat::fires] = rand.uniDist(0.0, 10.0);
	ship->m_stats[Ship::Stat::temperature] = rand.uniDist(25.0, 75.0);
	ship->m_stats[Ship::Stat::water] = rand.uniDist(25.0, 75.0);
}
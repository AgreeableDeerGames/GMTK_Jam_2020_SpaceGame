#include <ProjectTemplate/Core/MainMenuRegion.h>
#include <ProjectTemplate/Core/Ship.h>

#include <TGUI/TGUI.hpp>

#include <memory>

using namespace PT;

MainMenuRegion::MainMenuRegion(sf::RenderWindow& window) : 
	m_gui(window),
	m_defaultTheme(),
	m_tutorialRegion(window, std::make_shared<Ship>())
{
	InitGui();
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

	// Create Scale and Rotation Demo button
	tgui::Button::Ptr tutorialButton = tgui::Button::create();
	tutorialButton->setText("Tutorial");
	tutorialButton->connect("pressed", [this]()
	{
		this->setNextRegion(m_tutorialRegion);
	});
	gameModeButtons.push_back(tutorialButton);

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
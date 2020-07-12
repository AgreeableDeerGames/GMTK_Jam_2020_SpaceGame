#include <ProjectTemplate/Core/GameLostRegion.h>
#include <ProjectTemplate/Core/EventController.h>

#include <TGUI/TGUI.hpp>

using namespace PT;

GameLostRegion::GameLostRegion(sf::RenderWindow& window) :
	m_gui(window)
{
	InitGui();
}

bool GameLostRegion::handleEvent(sf::Int64 elapsedTime, const sf::Event& event)
{
	return m_gui.handleEvent(event);
}

tgui::Gui& GameLostRegion::GetGui()
{
	return m_gui;
}

void GameLostRegion::InitGui()
{
	m_gui.removeAllWidgets();

	// Get a bound version of the window size
	// Passing this to setPosition or setSize will make the widget automatically update when the view of the gui changes
	tgui::Layout windowWidth = tgui::bindWidth(m_gui);
	tgui::Layout windowHeight = tgui::bindHeight(m_gui);

	// Add buttons for each game mode
	std::vector<tgui::Widget::Ptr> gameLostWidgets;


	// Tell them that they lost
	tgui::Label::Ptr gameOverLabel = tgui::Label::create();
	gameOverLabel->setText("Game Over");
	gameLostWidgets.push_back(gameOverLabel);

	// Back to main menu
	tgui::Button::Ptr mainMenuButton = tgui::Button::create();
	mainMenuButton->setText("Main Menu");
	mainMenuButton->connect("pressed", [this]()
	{
		EventController::GetGlobalMainMenuRegion()->Reset();
		this->setNextRegion(*EventController::GetGlobalMainMenuRegion());
	});
	gameLostWidgets.push_back(mainMenuButton);

	// Size and place buttons
	// The number of buttons will be needed a few times. Calculate it once.
	const std::size_t demoRegionButtonCount = gameLostWidgets.size();
	// The buttons should be 1/4 the width of the screen
	tgui::Layout buttonWidth = windowWidth / 4.0f;
	// Adjust the height of the buttons so that they can all fit on screen
	tgui::Layout buttonHeight = windowHeight / ((float)demoRegionButtonCount * 2 + 1);
	for (std::size_t i = 0; i < demoRegionButtonCount; ++i)
	{
		// Save some repetitive typing
		auto& currentButton = gameLostWidgets.at(i);
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

void GameLostRegion::SetFinalShip(std::shared_ptr<Ship> finalShip)
{
	InitGui();
	m_ship = std::move(finalShip);
}
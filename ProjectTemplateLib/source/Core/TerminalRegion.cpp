#include <ProjectTemplate/Core/TerminalRegion.h>
#include <ProjectTemplate/Core/Ship.h>

#include <ProjectTemplate/Core/InputRecorder.h>

#include <TGUI/TGUI.hpp>

#include <memory>
#include <vector>

using namespace PT;

TerminalRegion::TerminalRegion(sf::RenderWindow& window, std::shared_ptr<Ship> ship, std::vector<Ship::Stat> trackedStats) :
	TemplateRegion(window),
	m_isInRecordState(),
	m_nextActionToBind(),
    m_nextActionNameToBind(),
	m_recorder(),
	m_terminal(),
	m_ship(std::move(ship)),
	m_visibleShipBars()
{
	InitGui(trackedStats);
	addDrawable(0, m_terminal);
}

bool TerminalRegion::handleEvent(sf::Int64 elapsedTime, const sf::Event& event)
{
	m_gui.handleEvent(event);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
	{
		if (m_isInRecordState)
		{
			m_terminal.AddBind(m_recorder.GetCompletedBind(m_nextActionNameToBind, m_nextActionToBind));
		}
	}

	if (m_isInRecordState)
	{
		return m_recorder.handleEvent(elapsedTime, event);
	}
	else
	{
		m_terminal.handleEvent(elapsedTime, event);
	}
}

void TerminalRegion::update(sf::Int64 elapsedTime)
{
	m_terminal.update(elapsedTime);

	m_ship->update(elapsedTime);
}

void PT::TerminalRegion::InitGui(const std::vector<Ship::Stat>& trackedStats)
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
		auto progressBar = tgui::ProgressBar::create();
		tgui::Layout progressBarWidth = windowWidth / 3;
		tgui::Layout progressBarHeight = windowHeight / 20;
		progressBar->setRenderer(theme.getRenderer("ProgressBar"));
		progressBar->setSize({ progressBarWidth, progressBarHeight });
		progressBar->setValue(50);
		progressBar->setPosition(windowWidth / 25, (progressBarHeight / 2) + progressBarHeight * (1.25 * i));
		m_gui.add(progressBar);

		m_visibleShipBars[trackedStats[i]] = progressBar;
	}

	m_displayedTerminal = tgui::TextBox::create();
	m_displayedTerminal->setEnabled(false);
	m_displayedTerminal->setSize(windowWidth * 0.9, windowHeight * 0.25);
	m_displayedTerminal->setPosition(25, 500);
	m_displayedTerminal->setText("SOME TEXT");
	m_gui.add(m_displayedTerminal);

}
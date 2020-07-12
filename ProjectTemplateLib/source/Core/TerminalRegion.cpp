#include <ProjectTemplate/Core/EventController.h>
#include <ProjectTemplate/Core/TerminalRegion.h>
#include <ProjectTemplate/Core/Ship.h>

#include <ProjectTemplate/Core/InputRecorder.h>

#include <TGUI/TGUI.hpp>

#include <memory>
#include <vector>

using namespace PT;

TerminalRegion::TerminalRegion(sf::RenderWindow& window, std::shared_ptr<Ship> ship, std::vector<Ship::Stat> trackedStats, std::shared_ptr<DataPad> dataPad) :
	TemplateRegion(),
	m_isInRecordState(),
	m_nextActionToBind(),
    m_nextActionNameToBind(),
	m_recorder(),
	m_terminal(window, ship, trackedStats, dataPad),
	m_ship(std::move(ship)),
	m_dataPad(std::move(dataPad))
{
	addDrawable(0, m_terminal);
}

bool TerminalRegion::handleEvent(sf::Int64 elapsedTime, const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Enter)
		{
			if (m_isInRecordState)
			{
				//m_terminal.AddBind(m_recorder.GetCompletedBind(m_nextActionNameToBind, m_nextActionToBind));
				m_dataPad->AddBind(m_recorder.GetCompletedBind(m_nextActionNameToBind, m_nextActionToBind));
				m_isInRecordState = false;
				return true;
			}
		}

		if (m_isInRecordState)
		{
			return m_recorder.handleEvent(elapsedTime, event);
		}
		else
		{
			return m_terminal.handleEvent(elapsedTime, event);
		}
	}
	else
	{
		return false;
	}
}

void TerminalRegion::update(sf::Int64 elapsedTime)
{
	m_terminal.update(elapsedTime);
	m_ship->update(elapsedTime);

	if (IsGameOver())
	{
		setNextRegion(*EventController::GetGlobalGameLostRegion());
	}
}


tgui::Gui& PT::TerminalRegion::GetGui()
{
	return m_terminal.GetGui();
}


bool TerminalRegion::IsGameOver()
{
	if (m_ship->m_stats[Ship::Stat::hullIntegrity] == 0 ||
		m_ship->m_stats[Ship::Stat::oxygen] == 0 || 
		m_ship->m_stats[Ship::Stat::temperature] == 0 ||
		m_ship->m_stats[Ship::Stat::temperature] == 100 ||
		m_ship->m_stats[Ship::Stat::fires] == 100)
	{
		return true;
	}
	return false;
}
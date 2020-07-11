#include <ProjectTemplate/Core/TerminalRegion.h>
#include <ProjectTemplate/Core/Ship.h>

#include <ProjectTemplate/Core/InputRecorder.h>

#include <memory>
#include <vector>

using namespace PT;

TerminalRegion::TerminalRegion(std::shared_ptr<Ship> ship) :
	m_isInRecordState(),
	m_nextActionToBind(),
    m_nextActionNameToBind(),
	m_recorder(),
	m_ship(std::move(ship)),
	m_terminal()
{
	addDrawable(0, m_terminal);
}

bool TerminalRegion::handleEvent(sf::Int64 elapsedTime, const sf::Event& event)
{
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

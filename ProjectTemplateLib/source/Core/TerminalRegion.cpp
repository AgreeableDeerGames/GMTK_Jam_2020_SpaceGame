#include <ProjectTemplate/Core/TerminalRegion.h>
#include <ProjectTemplate/Core/Ship.h>

#include <ProjectTemplate/Core/InputRecorder.h>

#include <memory>
#include <vector>

using namespace PT;

TerminalRegion::TerminalRegion(std::shared_ptr<Ship> ship) :
	m_ship(std::move(ship)),
	m_terminals()
{
	m_terminals.emplace_back();

	for (auto& terminal : m_terminals)
	{
		addDrawable(0, terminal);
	}
}

bool TerminalRegion::handleEvent(sf::Int64 elapsedTime, const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
	{
		if (m_isInRecordState)
		{
			// m_bindVec.push_back()
			m_recorder.GetCompletedBind(m_nextActionToBind);
		}
	}

	if (m_isInRecordState)
	{
		return m_recorder.handleEvent(elapsedTime, event);
	}
	else
	{
		return true;
	}
}


void TerminalRegion::update(sf::Int64 elapsedTime)
{
	for (auto& terminal : m_terminals)
	{
		terminal.update(elapsedTime);
	}

	m_ship->update(elapsedTime);
}

#include <ProjectTemplate/Core/TerminalRegion.h>

#include <ProjectTemplate/Core/InputRecorder.h>


#include <vector>

using namespace PT;

TerminalRegion::TerminalRegion() :
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
		m_recorder.handleEvent(elapsedTime, event);
	}
	else
	{

	}
}


void TerminalRegion::update(sf::Int64 elapsedTime)
{
	for (auto& terminal : m_terminals)
	{
		terminal.update(elapsedTime);
	}
}

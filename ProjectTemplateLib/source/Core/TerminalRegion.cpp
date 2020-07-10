#include <ProjectTemplate/Core/TerminalRegion.h>


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

void TerminalRegion::update(sf::Int64 elapsedTime)
{
}

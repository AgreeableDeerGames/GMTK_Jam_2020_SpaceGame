#include <ProjectTemplate/Core/TerminalRegion.h>
#include <ProjectTemplate/Core/Ship.h>

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

void TerminalRegion::update(sf::Int64 elapsedTime)
{
	m_ship->update(elapsedTime);
}

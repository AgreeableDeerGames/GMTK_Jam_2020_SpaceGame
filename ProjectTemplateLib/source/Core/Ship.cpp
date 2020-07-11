#include <ProjectTemplate/Core/Ship.h>

#include <iostream>

using namespace PT;

double oxygenGainedFromLifeSupport = 0.1;
double oxygenLostFromHoles = 0.05;
double oxygenLostFromFires = 0.05;

double hullLostFromDamage = 0.1;
double hullGainedFromRepairs = 0.5;

double heatGainedFromFires = 0.05;
double heatLostFromHoles = 0.05;
double heatGainedFromHeating = 0.5;
double heatLostFromCooling = 0.5;

double fireSpread = 0.1;
double firePutOutBySprinklers = 0.1;

double waterGenerated = 0.1;
double waterLostBySprinklers = 0.5;

Ship::Ship() : 
    m_stats({ 
        {Stat::oxygen, 100.0},
        {Stat::hullIntegrity, 100.0},
        {Stat::temperature, 50.0},
        {Stat::fires, 0.0},
        {Stat::water, 100.0}}),
    m_isHullBeingRepaired(false),
    m_isHeatingOn(false),
    m_isCoolingOn(false),
    m_areSprinklersOn(false)
{
}

void Ship::update(sf::Int64 elapsedTime)
{
	// Default Behavior
    m_stats[Stat::oxygen] = m_stats[Stat::oxygen] + oxygenGainedFromLifeSupport - (oxygenLostFromHoles * m_stats[Stat::hullIntegrity] * m_stats[Stat::oxygen]) - (oxygenLostFromFires * m_stats[Stat::fires] * m_stats[Stat::oxygen]);
    m_stats[Stat::hullIntegrity] = m_stats[Stat::hullIntegrity] - hullLostFromDamage + ((int)m_isHullBeingRepaired * hullGainedFromRepairs);
    m_stats[Stat::temperature] = m_stats[Stat::temperature] + (heatGainedFromFires * m_stats[Stat::fires]) - (heatLostFromHoles * m_stats[Stat::hullIntegrity]) + ((int)m_isHeatingOn * heatGainedFromHeating) - ((int)m_isCoolingOn * heatLostFromCooling);

    m_stats[Stat::fires] = m_stats[Stat::fires] + (fireSpread * m_stats[Stat::fires]) - ((int)m_areSprinklersOn * firePutOutBySprinklers);
    m_stats[Stat::water] = m_stats[Stat::water] + waterGenerated - ((int)m_areSprinklersOn * waterLostBySprinklers);

    //PrintToTerminal();
}

void PT::Ship::PrintToTerminal() const
{
    std::cout << m_stats.at(Stat::oxygen) << std::endl;
    std::cout << m_stats.at(Stat::hullIntegrity) << std::endl;
    std::cout << m_stats.at(Stat::temperature) << std::endl;
    std::cout << m_stats.at(Stat::fires) << std::endl;
    std::cout << m_stats.at(Stat::water) << std::endl;
}

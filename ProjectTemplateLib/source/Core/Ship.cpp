#include <ProjectTemplate/Core/Ship.h>

#include <iostream>
#include <unordered_map>

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
double firePutOutBySprinklers = 0.5;

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
    m_stats[Stat::hullIntegrity] = m_stats[Stat::hullIntegrity] - hullLostFromDamage + ((int)m_isHullBeingRepaired * hullGainedFromRepairs);

    UpdateWater(elapsedTime);
    UpdateFire(elapsedTime);
    UpdateOxygen(elapsedTime);
    UpdateTemperature(elapsedTime);
    //PrintToTerminal();
}

void Ship::PrintToTerminal() const
{
    std::cout << m_stats.at(Stat::oxygen) << std::endl;
    std::cout << m_stats.at(Stat::hullIntegrity) << std::endl;
    std::cout << m_stats.at(Stat::temperature) << std::endl;
    std::cout << m_stats.at(Stat::fires) << std::endl;
    std::cout << m_stats.at(Stat::water) << std::endl;
}


void Ship::UpdateWater(sf::Int64 elapsedTime)
{
    const double waterGeneratedPerSecond = waterGenerated * elapsedTime * 0.000001;
    const double waterLostPerSecond = (int)m_areSprinklersOn * waterLostBySprinklers * elapsedTime * 0.000001;


    m_stats[Stat::water] = m_stats[Stat::water] + waterGeneratedPerSecond - waterLostPerSecond;
    if (m_stats[Stat::water] < 0)
    {
        m_stats[Stat::water] = 0;
	}
    if (m_stats[Stat::water] > 100)
    {
        m_stats[Stat::water] = 100;
	}
}

void Ship::UpdateFire(sf::Int64 elapsedTime)
{
    const double fireSpreadPerSecond = m_areSprinklersOn ? 0.0 : m_stats[Stat::fires] * fireSpread * elapsedTime * 0.000001;
    const double firePutOutPerSecond = (int)m_areSprinklersOn * firePutOutBySprinklers * elapsedTime * 0.000001;

    m_stats[Stat::fires] = m_stats[Stat::fires] + fireSpreadPerSecond - firePutOutPerSecond;
    if (m_stats[Stat::fires] < 0)
    {
        m_stats[Stat::fires] = 0;
	}
    if (m_stats[Stat::fires] > 100)
    {
        m_stats[Stat::fires] = 100;
	}
}

void Ship::UpdateOxygen(sf::Int64 elapsedTime)
{
    const double oxygenGainedPerSecond = oxygenGainedFromLifeSupport * elapsedTime * 0.000001;
    const double oxygenLostPerSecond = m_stats[Stat::oxygen] * m_stats[Stat::fires] * oxygenLostFromFires * elapsedTime * 0.000001;

    m_stats[Stat::oxygen] = m_stats[Stat::oxygen] + oxygenGainedPerSecond - oxygenLostPerSecond;
    //m_stats[Stat::oxygen] = m_stats[Stat::oxygen] + oxygenGainedFromLifeSupport - (oxygenLostFromHoles * m_stats[Stat::hullIntegrity] * m_stats[Stat::oxygen]) - (oxygenLostFromFires * m_stats[Stat::fires] * m_stats[Stat::oxygen]);
    if (m_stats[Stat::oxygen] < 0)
    {
        m_stats[Stat::oxygen] = 0;
	}
    if (m_stats[Stat::oxygen] > 100)
    {
        m_stats[Stat::oxygen] = 100;
	}
}

void Ship::UpdateTemperature(sf::Int64 elapsedTime)
{
    m_stats[Stat::temperature] = m_stats[Stat::temperature] + (heatGainedFromFires * m_stats[Stat::fires]) - (heatLostFromHoles * m_stats[Stat::hullIntegrity]) + ((int)m_isHeatingOn * heatGainedFromHeating) - ((int)m_isCoolingOn * heatLostFromCooling);
}

std::string Ship::GetStatName(Ship::Stat stat)
{
	static std::unordered_map<Ship::Stat, std::string> statMapping
	{
		{ Ship::Stat::oxygen, "Oxygen" },
		{ Ship::Stat::hullIntegrity, "Hull Integrity" },
		{ Ship::Stat::temperature, "Temperature" },
		{ Ship::Stat::fires, "Fire" },
		{ Ship::Stat::water, "Water Reservers" }
	};

    return statMapping[stat];
}

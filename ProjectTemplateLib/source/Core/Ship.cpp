#include <ProjectTemplate/Core/Ship.h>

#include <iostream>
#include <unordered_map>

using namespace PT;

namespace 
{
    double oxygenGainedFromLifeSupport = 0.1;
    double oxygenLostFromHoles = 0.05;
    double oxygenLostFromFires = 0.0005;

    double hullLostFromDamage = 0.1;
    double hullGainedFromRepairs = 0.5;

    double heatGainedFromFires = 0.005;
    double heatLostFromHoles = 0.05;
    double heatGainedFromHeating = 0.5;
    double heatLostFromCooling = 0.5;
    double heatNormalizationRate = 0.001;

    double fireSpread = 0.1;
    double firePutOutBySprinklers = 0.5;

    double waterGenerated = 0.1;
    double waterLostBySprinklers = 0.5;
    double radiationGainedFromSprinklers = 0.2;

    double hullRepairedByNanites = 0.01;
    double naniteFireChance = 0.0001;
    double naniteDeathChance = 0.001;
    double nanitesReleased = 0.7;
    double nanitesDestroyedPerDeath = 0.1;
    double fireFromNaniteExplosion = 0.1;

    double radiationEatenByBacteria = 0.5;
    double hullEatenByBacteria = 0.1;
    double bacteriaReleased = 0.4;
    double bacteriaDeathRate = 0.1;
}


Ship::Ship() : 
    m_stats({ 
        {Stat::oxygen, 100.0},
        {Stat::hullIntegrity, 100.0},
        {Stat::temperature, 50.0},
        {Stat::fires, 0.0},
        {Stat::water, 100.0},
        {Stat::nanites, 0.0},
        {Stat::radiation, 0.0}}),

    m_isHullBeingRepaired(false),
    m_isHeatingOn(false),
    m_isCoolingOn(false),
    m_areSprinklersOn(false),
    m_releasingNanites(false),
    m_isReleasingBacteria(false),
    m_randGen()
{
}

void Ship::update(sf::Int64 elapsedTime)
{
    UpdateWater(elapsedTime);
    UpdateFire(elapsedTime);
    UpdateOxygen(elapsedTime);
    UpdateTemperature(elapsedTime);
    UpdateNanites(elapsedTime);
    UpdateRadiation(elapsedTime);
    UpdateBacteria(elapsedTime);
    UpdateHull(elapsedTime);
}

void Ship::PrintToTerminal() const
{
    for (auto& [key, value] : m_stats)
    {
        std::cout << GetStatName(key) << " " << value << std::endl;
    }
}

void Ship::UpdateShipStat(Stat stat, double change)
{
    m_stats[stat] += change;
    if (m_stats[stat] < 0)
    {
        m_stats[stat] = 0;
    }
    if (m_stats[stat] > 100)
    {
        m_stats[stat] = 100;
    }
}

void PT::Ship::UpdateShipStat(sf::Int64 elapsedTime, Stat stat, double change)
{
    UpdateShipStat(stat, change * elapsedTime * 0.000001);
}

void Ship::UpdateWater(sf::Int64 elapsedTime)
{
    const double gain = waterGenerated;
    const double loss = (int)m_areSprinklersOn * waterLostBySprinklers;
    UpdateShipStat(elapsedTime, Stat::water, gain - loss);
}

void Ship::UpdateFire(sf::Int64 elapsedTime)
{
    const double gain = m_areSprinklersOn ? 0.0 : m_stats[Stat::fires] * fireSpread;
    const double loss = (int)m_areSprinklersOn * firePutOutBySprinklers;
    UpdateShipStat(elapsedTime, Stat::fires, gain - loss);
}

void Ship::UpdateOxygen(sf::Int64 elapsedTime)
{
    const double gain = oxygenGainedFromLifeSupport;
    const double loss = m_stats[Stat::oxygen] * m_stats[Stat::fires] * oxygenLostFromFires;
    UpdateShipStat(elapsedTime, Stat::oxygen, gain - loss);
}

void Ship::UpdateTemperature(sf::Int64 elapsedTime)
{
    bool overHalf = m_stats[Stat::temperature] > 50;
    bool underHalf = m_stats[Stat::temperature] < 50;
    const double gain = (heatGainedFromFires * m_stats[Stat::fires]) + ((int)m_isHeatingOn * heatGainedFromHeating) + (int)underHalf * heatNormalizationRate;
    const double loss = (heatLostFromHoles * (100.0 / m_stats[Stat::hullIntegrity])) + ((int)m_isCoolingOn * heatLostFromCooling) + (int)overHalf * heatNormalizationRate;
    UpdateShipStat(elapsedTime, Stat::temperature, gain - loss);
}

void Ship::UpdateNanites(sf::Int64 elapsedTime)
{
    // TODO: MAKE THIS WORK
    const double gain = (int)m_releasingNanites * nanitesReleased;
    bool deadNanite = false;
    bool explodedNanite = false;
    if (this->m_stats[Stat::nanites] >= 0)
    {
        deadNanite = m_randGen.uniDist(0.0, 1.0) < naniteDeathChance * elapsedTime * 0.000001;
        explodedNanite = m_randGen.uniDist(0.0, 1.0) < naniteFireChance * elapsedTime * 0.000001;
    }
     
    const double loss = (int)deadNanite * nanitesDestroyedPerDeath + int(explodedNanite) * nanitesDestroyedPerDeath;
    UpdateShipStat(elapsedTime, Stat::nanites, gain - loss);

    if (explodedNanite)
    {
        UpdateShipStat(Stat::fires, fireFromNaniteExplosion);
    }
}

void Ship::UpdateRadiation(sf::Int64 elapsedTime)
{
    const double gain = (int)m_areSprinklersOn * radiationGainedFromSprinklers;
    const double loss = m_stats[Stat::bacteria] * radiationEatenByBacteria;
    UpdateShipStat(elapsedTime, Stat::radiation, gain - loss);
}

void Ship::UpdateBacteria(sf::Int64 elapsedTime)
{
    const double gain = (int)m_isReleasingBacteria * bacteriaReleased;
    const double loss = bacteriaDeathRate;
    UpdateShipStat(elapsedTime, Stat::bacteria, gain - loss);
}

void Ship::UpdateHull(sf::Int64 elapsedTime)
{
    const double gain = m_stats[Stat::nanites] * hullRepairedByNanites + (int)m_isHullBeingRepaired * hullGainedFromRepairs;
    const double loss = m_stats[Stat::bacteria] * hullEatenByBacteria;
    UpdateShipStat(elapsedTime, Stat::hullIntegrity, gain - loss);
}

std::string Ship::GetStatName(Ship::Stat stat) const
{
	static std::unordered_map<Ship::Stat, std::string> statMapping
	{
		{ Ship::Stat::oxygen, "Oxygen" },
		{ Ship::Stat::hullIntegrity, "Hull Integrity" },
		{ Ship::Stat::temperature, "Temperature" },
		{ Ship::Stat::fires, "Fire" },
        { Ship::Stat::water, "Water Reservers" },
        { Ship::Stat::nanites, "Active Nanites" },
        { Ship::Stat::radiation, "Radiation" },
        { Ship::Stat::bacteria, "Released Bacteria" }
	};

    return statMapping[stat];
}

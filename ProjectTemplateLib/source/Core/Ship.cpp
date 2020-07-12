#include <ProjectTemplate/Core/Ship.h>

#include <iostream>
#include <unordered_map>

using namespace PT;

#define RATE_MOD 1.0

namespace 
{
    double oxygenGainedFromLifeSupport = 0.1 * RATE_MOD;
    double oxygenLostFromHoles = 0.05 * RATE_MOD;
    double oxygenLostFromFires = 0.0005 * RATE_MOD;

    double hullLostFromDamage = 0.1 * RATE_MOD;
    double hullGainedFromRepairs = 0.5 * RATE_MOD;

    double heatGainedFromFires = 0.009 * RATE_MOD;
    double heatLostFromHoles = 0.05 * RATE_MOD;
    double heatGainedFromHeating = 0.5 * RATE_MOD;
    double heatLostFromCooling = 0.5 * RATE_MOD;
    double heatNormalizationRate = 0.001 * RATE_MOD;

    double fireSpread = 0.1 * RATE_MOD;
    double firePutOutBySprinklers = 0.5 * RATE_MOD;

    double waterGenerated = 0.3 * RATE_MOD;
    double waterLostBySprinklers = 1.0 * RATE_MOD;
    double radiationGainedFromSprinklers = 0.9 * RATE_MOD;

    double hullRepairedByNanites = 0.01 * RATE_MOD;
    double naniteFireChance = 0.001 * RATE_MOD;
    double naniteDeathChance = 0.001 * RATE_MOD;
    double nanitesReleased = 0.7 * RATE_MOD;
    double nanitesDestroyedPerDeath = 0.1 * RATE_MOD;
    double fireFromNaniteExplosion = 0.1 * RATE_MOD;

    double radiationEatenByBacteria = 0.1 * RATE_MOD;
    double hullEatenByBacteria = 0.05 * RATE_MOD;
    double bacteriaReleased = 0.4 * RATE_MOD;
    double bacteriaDeathRate = 0.1 * RATE_MOD;

    sf::Int64 naniteChargeTime = 10000000;
    sf::Int64 empChargeTime = 10000000;
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

    m_shouldUpdate(false),
    m_isHullBeingRepaired(false),
    m_isHeatingOn(false),
    m_isCoolingOn(false),
    m_areSprinklersOn(false),
    m_isReleasingNanites(false),
    m_isReleasingBacteria(false),
    m_randGen(),
    m_antibioticCharge(naniteChargeTime + 50),
    m_empcharge(empChargeTime + 50)
{
}

void Ship::update(sf::Int64 elapsedTime)
{   
    if (!m_shouldUpdate)
    {
        return;
    }

    if (m_antibioticCharge < naniteChargeTime)
    {
        m_antibioticCharge += elapsedTime;
    }
    if (m_empcharge < empChargeTime)
    {
        m_empcharge += elapsedTime;
    }

    UpdateWater(elapsedTime);
    UpdateFire(elapsedTime);
    UpdateOxygen(elapsedTime);
    UpdateTemperature(elapsedTime);
    UpdateNanites(elapsedTime);
    UpdateRadiation(elapsedTime);
    UpdateBacteria(elapsedTime);
    UpdateHull(elapsedTime);

    if (m_stats[Stat::water] == 0)
    {
        m_areSprinklersOn = false;
    }
    if (m_stats[Stat::nanites] == 100)
    {
        m_isReleasingNanites = false;
    }
    if (m_stats[Stat::bacteria] == 100)
    {
        m_isReleasingBacteria = false;
    }
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
    const double gain = (int)m_isReleasingNanites * nanitesReleased;
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

void Ship::AnibioticBurst()
{
    // Ten Second Charge
    if (m_antibioticCharge > naniteChargeTime)
    {
        m_antibioticCharge = 0;
        UpdateShipStat(Stat::bacteria, -10.0);
    }
}

void Ship::EMP()
{
    // Ten Second Charge
    if (m_empcharge > empChargeTime)
    {
        m_empcharge = 0;
        UpdateShipStat(Stat::nanites, -10.0);
    }
}
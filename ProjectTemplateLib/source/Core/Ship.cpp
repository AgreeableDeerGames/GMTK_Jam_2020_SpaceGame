#include <ProjectTemplate/Core/Ship.h>

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

Ship::Ship() : m_isHullBeingRepaired(false), m_isHeatingOn(false), m_isCoolingOn(false), m_areSprinklersOn(false),
m_oxygen(100.0), m_hullIntegrity(100.0), m_temperature(50.0), m_fires(0.0), m_water(100.0)
{

}

void Ship::update(sf::Int64 elapsedTime)
{
	// Default Behavior
    m_oxygen = m_oxygen + oxygenGainedFromLifeSupport - (oxygenLostFromHoles * m_hullIntegrity * m_oxygen) - (oxygenLostFromFires * m_fires * m_oxygen);
    m_hullIntegrity = m_hullIntegrity - hullLostFromDamage + ((int)m_isHullBeingRepaired * hullGainedFromRepairs);
    m_temperature = m_temperature + (heatGainedFromFires * m_fires) - (heatLostFromHoles * m_hullIntegrity) + ((int)m_isHeatingOn * heatGainedFromHeating) - ((int)m_isCoolingOn * heatLostFromCooling);

    m_fires = m_fires + (fireSpread * m_fires) - ((int)m_areSprinklersOn * firePutOutBySprinklers);
    m_water = m_water + waterGenerated - ((int)m_areSprinklersOn * waterLostBySprinklers);
}
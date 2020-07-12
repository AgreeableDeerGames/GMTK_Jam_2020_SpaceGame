#pragma once

#include <ProjectTemplate/Utils/DllUtils.h>

#include <GameBackbone/Core/Updatable.h>
#include <GameBackbone/Util/RandGen.h>

#include <map>
#include <string>

namespace PT
{
    class libProjectTemplate Ship : GB::Updatable
    {
    public:

        enum class Stat
        {
            // Oxygen - Higher Oxygen spreads fires quickly
            // 0% - 100%. 0% is a lose state
            oxygen,

            // Hull Integrity - Releases Oxygen
            // 0% - 100%. 0% is a lose state.
            hullIntegrity,

            // Temperature - Fires Create more heat, Hull holes reduce heat. There could be some global heating/cooling system
            // 0C - 100C. Hitting either end is a lose state.
            temperature,

            // Fires - Consume Oxygen, requires Oxygen
            // 0% - 100% of Ship.
            fires,

            // Water Reserve - Puts Out Fires. Highly radioactive.
            // 0% to 100%. No lose state here, just a resource. Maybe slowly regenerates.
            water,

            // Nanites - Repair hull damage have chance to explode and cause fire
            // 0% to 100%. Represents active nanites. No lose state here, just a resource. Maybe slowly regenerates.
            nanites,

            // Radiation - Kills living things
            // 0% - 100%. 100% is lose state
            radiation,

            // Radiation Eating Bacteria - Reduces radiation. Eats hull too. Slowly die off on their own.
            // 0% to 100%. No lose state here, just a resource. Maybe slowly regenerates.
            bacteria
        };

        std::map<Stat, double> m_stats;

        Ship();

        void update(sf::Int64 elapsedTime) override;
        std::string GetStatName(Ship::Stat) const;

        bool m_shouldUpdate;
        bool m_isHullBeingRepaired;
        bool m_isHeatingOn;
        bool m_isCoolingOn;
        bool m_areSprinklersOn;
        bool m_releasingNanites;
        bool m_isReleasingBacteria;

        void PrintToTerminal() const;

        void UpdateShipStat(Stat stat, double change);

    private:

        void UpdateShipStat(sf::Int64 elapsedTime, Stat stat, double change);

        void UpdateWater(sf::Int64 elapsedTime);
        void UpdateFire(sf::Int64 elapsedTime);
        void UpdateOxygen(sf::Int64 elapsedTime);
        void UpdateTemperature(sf::Int64 elapsedTime);
        void UpdateNanites(sf::Int64 elapsedTime);
        void UpdateRadiation(sf::Int64 elapsedTime);
        void UpdateBacteria(sf::Int64 elapsedTime);
        void UpdateHull(sf::Int64 elapsedTime);

        GB::RandGen m_randGen;
    };
}
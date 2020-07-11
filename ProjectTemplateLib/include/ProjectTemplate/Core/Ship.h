#pragma once

#include <ProjectTemplate/Utils/DllUtils.h>

#include <GameBackbone/Core/Updatable.h>

#include <map>

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

            // Water Reserve - Puts Out Fires
            // 0% to 100%. No lose state here, just a resource. Maybe slowly regenerates.
            water
        };

        std::map<Stat, double> m_stats;

        Ship();

        void update(sf::Int64 elapsedTime) override;

        bool m_isHullBeingRepaired;
        bool m_isHeatingOn;
        bool m_isCoolingOn;
        bool m_areSprinklersOn;

        void PrintToTerminal() const;


    private:

        void UpdateWater(sf::Int64 elapsedTime);
        void UpdateFire(sf::Int64 elapsedTime);
        void UpdateOxygen(sf::Int64 elapsedTime);
        void UpdateTemperature(sf::Int64 elapsedTime);

    };
}
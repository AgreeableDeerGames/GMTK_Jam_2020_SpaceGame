#pragma once

#include <ProjectTemplate/Utils/DllUtils.h>

#include <GameBackbone/Core/Updatable.h>

namespace PT
{
    class libProjectTemplate Ship : GB::Updatable
    {
    public:
        Ship();

        void update(sf::Int64 elapsedTime) override;

        bool m_isHullBeingRepaired;
        bool m_isHeatingOn;
        bool m_isCoolingOn;
        bool m_areSprinklersOn;

        void PrintToTerminal() const;

    private:

        // Oxygen - Higher Oxygen spreads fires quickly
        // 0% - 100%. 0% is a lose state
        double m_oxygen;

        // Hull Integrity - Releases Oxygen
        // 0% - 100%. 0% is a lose state.
        double m_hullIntegrity;

        // Temperature - Fires Create more heat, Hull holes reduce heat. There could be some global heating/cooling system
        // 0C - 100C. Hitting either end is a lose state.
        double m_temperature;


        // Fires - Consume Oxygen, requires Oxygen
        // 0% - 100% of Ship.
        double m_fires;

        // Water Reserve - Puts Out Fires
        // 0% to 100%. No lose state here, just a resource. Maybe slowly regenerates.
        double m_water;
    };
}
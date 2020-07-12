#pragma once

#include <ProjectTemplate/Utils/DllUtils.h>
#include <ProjectTemplate/Core/TemplateRegion.h>
#include <ProjectTemplate/TopDown/GameObject.h>
#include <ProjectTemplate/TopDown/TopDownRegion.h>

namespace PT
{
	class libProjectTemplate TopDownShip : TopDownRegion
	{
	public:
		TopDownShip(sf::RenderWindow& window);

		virtual ~TopDownShip() = default;

		void update(sf::Int64 elapsedTime) override;

	};
}
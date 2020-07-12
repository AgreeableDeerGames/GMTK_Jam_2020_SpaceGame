#pragma once

#include <ProjectTemplate/Utils/DllUtils.h>
#include <ProjectTemplate/Core/TemplateRegion.h>
#include <ProjectTemplate/TopDown/GameObject.h>

#include <GameBackbone/Core/UniformAnimationSet.h>
#include <GameBackbone/Core/AnimatedSprite.h>

#include <TGUI/TGUI.hpp>

#include <Box2D/Box2D.h>

namespace PT
{

	class libProjectTemplate TopDownRegion : public TemplateRegion
	{
	public:
		TopDownRegion(sf::RenderWindow& window);

		tgui::Gui& GetGui() override;

		bool handleEvent(sf::Int64 elapsedTime, const sf::Event& event) override;

		virtual void Init();

		void update(sf::Int64 elapsedTime) override;

		// Helper functions
		b2Vec2 convertToBox(sf::Vector2f sfCoords);
		sf::Vector2f convertToSprite(b2Vec2 boxCoord);
		sf::Vector2f convertToSprite(double boxCoordX, double boxCoordY);

	protected:

		tgui::Gui m_gui;

		sf::Texture m_playerTexture;
		sf::Texture m_devTileTexture;
		sf::Texture m_placeholderTexture;

		sf::VertexArray m_vertices;
		sf::Texture m_tileset;

		GB::UniformAnimationSet::Ptr m_noAnimation;
		GB::UniformAnimationSet::Ptr m_animations;

		GameObject::Ptr m_playerObject;
		std::vector<GameObject::Ptr> m_gameObjects;

		std::unique_ptr<b2World> m_templateWorld;


	private:
	};
}

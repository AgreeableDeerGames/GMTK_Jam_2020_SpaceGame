#pragma once

#include <GameBackbone/Core/UniformAnimationSet.h>

#include <Box2D/Box2D.h>

#include <ProjectTemplate/TopDown/GameObject.h>

#include <memory>

namespace PT
{
	class libProjectTemplate Player : public GameObject {
	public:

		Player(
			sf::Vector2f position,
			b2World* world // b2Body* objectBody
		);

		virtual void update(sf::Int64 elapsedTime) override;

	private:

		void updateBody();

		static std::shared_ptr<sf::Texture> TEXTURE;
		static std::shared_ptr<sf::Texture> GetTexture();

		static GB::UniformAnimationSet::Ptr ANIMATION;
		static GB::UniformAnimationSet::Ptr GetAnimation();
	};
}
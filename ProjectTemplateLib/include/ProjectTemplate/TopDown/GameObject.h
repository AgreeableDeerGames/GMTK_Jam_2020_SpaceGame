#pragma once

#include <ProjectTemplate/Utils/DllUtils.h>

#include <GameBackbone/Core/AnimatedSprite.h>

#include <SFML/System/Vector2.hpp>

#include <box2d/b2_body.h>
#include <box2d/box2d.h>

namespace PT
{
	constexpr float PI = 3.1415926535;
	constexpr double PIXELS_PER_METER = 32;

	class libProjectTemplate GameObject : public GB::AnimatedSprite
	{
	public:
		using Ptr = std::shared_ptr<GameObject>;

		enum class DIRECTION
		{
			Not_Moving,
			Up,
			Left,
			Down,
			Right
		};

		enum ObjectGroup {
			TILE = 0,
			ENTITY
		};

		GameObject(
			sf::Vector2f position,
			const sf::Texture& texture, GB::AnimationSet::Ptr animations, sf::Vector2f scale,
			b2World* world, // b2Body* objectBody,	
			bool shouldReset = false,
			bool isDynamic = true
		);

		virtual ~GameObject() = default;

		virtual void update(sf::Int64 elapsedTime) override;

		bool GetIsMovable() const;

		b2Body* m_objectBody;

		void createBody(b2World* world, bool isDynamic = true);

	private:
		bool m_isMovable;
		DIRECTION m_movementState;

		sf::Vector2i m_movementVector;

	};
}
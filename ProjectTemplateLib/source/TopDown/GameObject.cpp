#include <ProjectTemplate/TopDown/GameObject.h>

#include <SFML/System/Vector2.hpp>

#include <cmath>
#include <algorithm>

using namespace PT;

// Microseconds per Tic (Up for slower, Down for faster)
constexpr float worldSpeed = 50000.0f;
constexpr float pixelsPerStep = 5.0f;

GameObject::GameObject(
	sf::Vector2f position,
	const sf::Texture& texture, GB::AnimationSet::Ptr animations, sf::Vector2f scale,
	b2World* world, // b2Body* objectBody,	
	bool shouldReset, bool isDynamic
) : 
	GB::AnimatedSprite(texture, std::move(animations)),
	m_isMovable(isDynamic),
	m_movementState(DIRECTION::Not_Moving)
{
	setScale(scale);

	setPosition(position);
	createBody(world, isDynamic);

	// Move origin of the sprite to its center
	// This will allow the sprite to rotate around its center instead of around its top left corner
	// The function getLocalBounds is used instead of getGlobalBounds as the origin is always calculated before
	// other transformations (though it won't matter in this case since we apply this operation before any transformations)
	float spriteLocalHalfHeight = getLocalBounds().height / 2.0;
	float spriteLocalHalfWidth = getLocalBounds().width / 2.0;
	setOrigin(spriteLocalHalfWidth, spriteLocalHalfHeight);
}

void GameObject::update(sf::Int64 elapsedTime)
{
	AnimatedSprite::update(elapsedTime);
	// Instruct the world to perform a single step of simulation.
	float stepTime = elapsedTime / worldSpeed;

	// this->setRotation((180/PI)*std::atan2f(m_objectBody->GetLinearVelocity().y, m_objectBody->GetLinearVelocity().x));

}

bool PT::GameObject::GetIsMovable() const
{
	return m_isMovable;
}

void GameObject::createBody(b2World* world, bool isDynamic) {
	// This defines the properties of body that the Box2D will operate on
	b2BodyDef bodyDef;

	// Move the Box2D body to a place in the Box2D coordinate system that corresponds to the 
	// sprite's position in the SFML coordinate system
	b2Vec2 worldPosition = b2Vec2(getPosition().x / PIXELS_PER_METER, getPosition().y / PIXELS_PER_METER);
	bodyDef.position.Set(worldPosition.x, worldPosition.y);
	bodyDef.fixedRotation = true;
	bodyDef.linearDamping = 0.05f;

	if (isDynamic)
	{
		bodyDef.type = b2_dynamicBody;
	}

	// This will prevent the body from ever falling asleep. This slows things down, 
	// but prevents strange bugs (possibly in this demo only) where objects suddenly stop moving
	bodyDef.allowSleep = false;

	// Create a Box2D body from the provided properties and add it to the world
	m_objectBody = world->CreateBody(&bodyDef);

	// Define the shape of the Box2D body.
	b2PolygonShape shape;
	float bodyWidth = 1;
	float bodyHeight = 1;
	shape.SetAsBox(getScale().x * bodyWidth / 2.0f, getScale().y * bodyHeight / 2.0f);

	if (isDynamic)
	{
		// Properties for the dynamic body
		b2FixtureDef fixtureDef;

		// The Shape
		fixtureDef.shape = &shape;

		// These change the way that the object behaves in the world
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 1.0f;

		// Add a fixture to the body with the calculated paramaters
		// (these are the individual shapes that make up the body and actually do the collision)
		m_objectBody->CreateFixture(&fixtureDef);
	}
	else
	{
		// Non-dynamic bodies just need a shape.
		// Setting the Density of 0 makes it static
		m_objectBody->CreateFixture(&shape, 0.0f);
	}
}


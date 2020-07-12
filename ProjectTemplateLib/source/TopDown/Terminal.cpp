
#include <SFML/Graphics/Texture.hpp>

#include <ProjectTemplate/TopDown/Terminal.h>

#include <box2d/b2_body.h>

using namespace PT;

PT::TopDownTerminal::TopDownTerminal(
	sf::Vector2f position,
	b2World* world
)
	: GameObject(position, *GetTexture(), GetAnimation(), sf::Vector2f(0.9f, 0.9f), world, true, true)
{
	updateBody();
	setScale({ 0.95f, 0.95f });


	m_objectBody->SetLinearDamping(1.0f);
	m_objectBody->GetFixtureList()->SetDensity(0.1);
	m_objectBody->ResetMassData();
}

void PT::TopDownTerminal::update(sf::Int64 elapsedTime)
{
	AnimatedSprite::update(elapsedTime);
}

std::shared_ptr<sf::Texture> PT::TopDownTerminal::TEXTURE;
std::shared_ptr<sf::Texture> PT::TopDownTerminal::GetTexture()
{
	if (TEXTURE != nullptr)
	{
		return TEXTURE;
	}
	TEXTURE = std::make_shared<sf::Texture>();
	TEXTURE->loadFromFile(R"(Textures/Box.png)");
	return TEXTURE;
}

GB::UniformAnimationSet::Ptr PT::TopDownTerminal::ANIMATION = nullptr;
GB::UniformAnimationSet::Ptr PT::TopDownTerminal::GetAnimation()
{
	if (ANIMATION != nullptr)
	{
		return ANIMATION;
	}

	ANIMATION = std::make_shared<GB::UniformAnimationSet>(sf::Vector2i(32, 32));
	ANIMATION->addAnimation({ {0, 0} });
	return ANIMATION;
}

void PT::TopDownTerminal::updateBody()
{
	sf::Vector2f scalars(0.95f, 0.95f);

	m_objectBody->DestroyFixture(&m_objectBody->GetFixtureList()[0]);

	// Define the shape of the Box2D body.
	b2PolygonShape shape;

	// You must pass the half width and half height to Box2D to create a box shape
	shape.SetAsBox(scalars.x / 2.0f, scalars.y / 2.0f);

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
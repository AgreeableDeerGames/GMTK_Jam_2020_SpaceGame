#include <ProjectTemplate/TopDown/TopDownRegion.h>
#include <ProjectTemplate/TopDown/GameObject.h>

#include <GameBackbone/Core/UniformAnimationSet.h>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <iostream>
#include <memory>
#include <map>
#include <algorithm>

using namespace PT;

constexpr bool DEBUG_KEYPRESS = false;
constexpr bool DEBUG_MOUSE = false;
constexpr bool DEBUG_COLLISION = false;

const int32 velocityIterations = 6;
const int32 positionIterations = 2;
const b2Vec2 GRAVITY(0.0f, 0.0f);
const double pixelsPerMeter = 32;

TopDownRegion::TopDownRegion(sf::RenderWindow& window) :
	TemplateRegion(),
	m_gui(window)
{
}

tgui::Gui& TopDownRegion::GetGui()
{
	return m_gui;
}

bool TopDownRegion::handleEvent(sf::Int64 elapsedTime, const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		auto key = event.key;
		switch (key.code)
		{
		case sf::Keyboard::Up:
		case sf::Keyboard::W:
		{
			b2Vec2 vel = m_playerObject->m_objectBody->GetLinearVelocity();
			vel.y = -0.15;
			m_playerObject->m_objectBody->SetLinearVelocity(vel);
			break;
		}
		case sf::Keyboard::Left:
		case sf::Keyboard::A:
		{
			b2Vec2 vel = m_playerObject->m_objectBody->GetLinearVelocity();
			vel.x = -0.15;
			m_playerObject->m_objectBody->SetLinearVelocity(vel);
			break;
		}
		case sf::Keyboard::Down:
		case sf::Keyboard::S:
		{
			b2Vec2 vel = m_playerObject->m_objectBody->GetLinearVelocity();
			vel.y = 0.15;
			m_playerObject->m_objectBody->SetLinearVelocity(vel);
			break;
		}
		case sf::Keyboard::Right:
		case sf::Keyboard::D:
		{
			b2Vec2 vel = m_playerObject->m_objectBody->GetLinearVelocity();
			vel.x = 0.15;
			m_playerObject->m_objectBody->SetLinearVelocity(vel);
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else if (event.type == sf::Event::KeyPressed)
	{
		auto key = event.key;
		switch (key.code)
		{
		case sf::Keyboard::Up:
		case sf::Keyboard::W:
		{
			b2Vec2 vel = m_playerObject->m_objectBody->GetLinearVelocity();
			// Make sure that the sprite is moving left, otherwise we could randomly stop moving right
			if (vel.y < 0)
			{
				vel.y = 0;
				m_playerObject->m_objectBody->SetLinearVelocity(vel);
			}
			break;
		}
		case sf::Keyboard::Left:
		case sf::Keyboard::A:
		{
			b2Vec2 vel = m_playerObject->m_objectBody->GetLinearVelocity();
			// Make sure that the sprite is moving left, otherwise we could randomly stop moving right
			if (vel.x < 0)
			{
				vel.x = 0;
				m_playerObject->m_objectBody->SetLinearVelocity(vel);
			}
			break;
		}
		case sf::Keyboard::Down:
		case sf::Keyboard::S:
		{
			b2Vec2 vel = m_playerObject->m_objectBody->GetLinearVelocity();
			// Make sure that the sprite is moving left, otherwise we could randomly stop moving right
			if (vel.y > 0)
			{
				vel.y = 0;
				m_playerObject->m_objectBody->SetLinearVelocity(vel);
			}
			break;
		}
		case sf::Keyboard::Right:
		case sf::Keyboard::D:
		{
			b2Vec2 vel = m_playerObject->m_objectBody->GetLinearVelocity();
			if (vel.x > 0)
			{
				// Make sure that the sprite is moving right, otherwise we could randomly stop moving left
				vel.x = 0;
				m_playerObject->m_objectBody->SetLinearVelocity(vel);
			}
			break;
		}
		default:
		{
			break;
		}
		}
		return true;
	}
	return true;
}

void TopDownRegion::Init()
{
	m_tileset.loadFromFile(R"(Textures/Floor_Tile.png)");

	// Construct a world object, which will hold and simulate the rigid bodies.
	m_templateWorld = std::make_unique<b2World>(GRAVITY);
}

void TopDownRegion::update(sf::Int64 elapsedTime)
{
	// Instruct the world to perform a single step of simulation.
	float stepTime = elapsedTime / 50000.0f;
	m_templateWorld->Step(stepTime, velocityIterations, positionIterations);
	for (int ii = 0; ii < m_gameObjects.size(); ii++)
	{
		// Create a temporary body for accessing
		b2Body* objectBody = m_gameObjects[ii]->m_objectBody;

		// Set the new position of the object onto the corresponding sprite.
		b2Vec2 pos = objectBody->GetPosition();
		m_gameObjects[ii]->setPosition(convertToSprite(pos));

		// Update the angle of the sprite to match the angle of the Box2D body.
		// Converting from radians to degrees because Box2D uses radians and SFML uses degrees. 
		float angle = objectBody->GetAngle();
		//m_gameObjects[ii]->setRotation(angle * (180.0 / 3.1415926535));

		m_gameObjects[ii]->update(elapsedTime);
	}

	b2Body* objectBody = m_playerObject->m_objectBody;

	// Set the new position of the object onto the corresponding sprite.
	b2Vec2 pos = objectBody->GetPosition();
	m_playerObject->setPosition(convertToSprite(pos));

	m_playerObject->update(elapsedTime);
}

/// <summary>
/// Convert a coordinate from the SFML coordinate system to the Box2D coordinate system.
/// </summary>
/// <param name="sfCoords"> </param>
/// <return> b2Vec2 </return>
b2Vec2 TopDownRegion::convertToBox(sf::Vector2f sfCoords) {
	return b2Vec2(sfCoords.x / pixelsPerMeter, sfCoords.y / pixelsPerMeter);
}

/// <summary>
/// Convert a coordinate from the Box2D coordinate system to the SFML coordinate system.
/// </summary>
/// <param name="boxCoord"> The coordinate in the Box2D coordinate system </param>
/// <return> The coordinate in the SFML coordinate system. </return>
sf::Vector2f TopDownRegion::convertToSprite(b2Vec2 boxCoord) {
	return sf::Vector2f(boxCoord.x * pixelsPerMeter, boxCoord.y * pixelsPerMeter);
}

/// <summary>
/// Convert a coordinate from the Box2D coordinate system to the SFML coordinate system.
/// </summary>
/// <param name="boxCoordX"> The X position in the Box2D coordinate space. </param>
/// <param name="boxCoordY"> The Y position in the Box2D coordinate space. </param>
/// <return> The coordinate in the SFML coordinate system. </return>
sf::Vector2f TopDownRegion::convertToSprite(double boxCoordX, double boxCoordY) {
	return sf::Vector2f(boxCoordX * pixelsPerMeter, boxCoordY * pixelsPerMeter);
}

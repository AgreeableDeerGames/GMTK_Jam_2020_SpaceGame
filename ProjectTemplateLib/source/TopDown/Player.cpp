
#include <SFML/Graphics/Texture.hpp>

#include <ProjectTemplate/TopDown/Player.h>

#include <cmath>

using namespace PT;

Player::Player(
	sf::Vector2f position,
	b2World* world
)
	: GameObject(position, *GetTexture(), GetAnimation(), sf::Vector2f(0.75f, 0.75f), world, true)
{
	setAnimationDelay(sf::seconds(0.2));
	runAnimation(0, GB::ANIMATION_END_TYPE::ANIMATION_REVERSE);

	m_objectBody->SetLinearDamping(0.0f);

}

void Player::update(sf::Int64 elapsedTime)
{
	AnimatedSprite::update(elapsedTime);
	// Instruct the world to perform a single step of simulation.
	//   float stepTime = elapsedTime / worldSpeed;

	this->setRotation((180 / PI) * std::atan2f(m_objectBody->GetLinearVelocity().y, m_objectBody->GetLinearVelocity().x));

}

std::shared_ptr<sf::Texture> PT::Player::TEXTURE;
std::shared_ptr<sf::Texture> PT::Player::GetTexture()
{
	if (TEXTURE != nullptr)
	{
		return TEXTURE;
	}
	TEXTURE = std::make_shared<sf::Texture>();
	TEXTURE->loadFromFile(R"(Textures/Game_Jam_Top_Down_PC.png)");
	return TEXTURE;
}

GB::UniformAnimationSet::Ptr Player::ANIMATION = nullptr;
GB::UniformAnimationSet::Ptr Player::GetAnimation()
{
	if (ANIMATION != nullptr)
	{
		return ANIMATION;
	}

	ANIMATION = std::make_shared<GB::UniformAnimationSet>(sf::Vector2i(32, 32));
	ANIMATION->addAnimation({
		{ 0, 0 },
		{ 1, 0 },
		{ 2, 0 },
		{ 3, 0 },
		{ 4, 0 }
		});
	return ANIMATION;
}

void Player::updateBody()
{

}
#include <ProjectTemplate/TopDown/TopDownShip.h>
#include <ProjectTemplate/TopDown/Player.h>
#include <ProjectTemplate/TopDown/Terminal.h>


PT::TopDownShip::TopDownShip(sf::RenderWindow& window) : TopDownRegion(window)
{
	m_playerObject = std::make_shared<Player>(sf::Vector2f(100, 100), m_templateWorld.get());
	m_gameObjects.push_back(std::make_shared<TopDownTerminal>(sf::Vector2f(200, 100), m_templateWorld.get()));
	m_gameObjects.push_back(std::make_shared<TopDownTerminal>(sf::Vector2f(300, 300), m_templateWorld.get()));

	this->addDrawable(0, *m_playerObject);

	for (auto& gameObj : m_gameObjects)
	{
		addDrawable(0, *gameObj);
	}
}

void PT::TopDownShip::update(sf::Int64 elapsedTime)
{
	TopDownRegion::update(elapsedTime);
}

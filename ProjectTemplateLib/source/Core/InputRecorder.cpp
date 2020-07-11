#include <ProjectTemplate/Core/InputRecorder.h>

using namespace PT;

bool InputRecorder::handleEvent(sf::Int64 elapsedTime, const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{

		switch (event.key.code)
		{
		case sf::Keyboard::Key::Num0:
		case sf::Keyboard::Key::Num1:
		case sf::Keyboard::Key::Num2:
		case sf::Keyboard::Key::Num3:
		case sf::Keyboard::Key::Num4:
		case sf::Keyboard::Key::Num5:
		case sf::Keyboard::Key::Num6:
		case sf::Keyboard::Key::Num7:
		case sf::Keyboard::Key::Num8:
		case sf::Keyboard::Key::Num9:
		{
			// Push the event into the vector
			m_bindKeys.push_back(event);
			return true;
		}
		default:
		{
			return false;
		}
		}
			
	}
	return false;
}

GB::KeyboardGestureBind InputRecorder::GetCompletedBind(std::string name, std::function<void()> action)
{
	sf::Int64 maxTimeBetweenInputs = 1000;
	GB::KeyboardGestureBind::EndType endType = GB::KeyboardGestureBind::EndType::Block;

	GB::KeyboardGestureBind returnBind{
		m_bindKeys,
		action,
		name,
		maxTimeBetweenInputs,
		endType
	};

	// Clear the internal state
	m_bindKeys.clear();

	return returnBind;
}
#include <ProjectTemplate/Core/InputRecorder.h>

using namespace PT;

bool InputRecorder::handleEvent(sf::Int64 elapsedTime, const sf::Event& event)
{
	// Push the event into the vector
	m_bindKeys.push_back(event);

	return true;
}

GB::KeyboardGestureBind InputRecorder::GetCompletedBind(std::function<void()> action)
{
	std::string name = "ActionName";
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
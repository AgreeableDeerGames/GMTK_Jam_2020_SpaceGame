#pragma once

#include <ProjectTemplate/Utils/DllUtils.h>


#include <GameBackbone/UserInput/InputHandler.h>
#include <GameBackbone/UserInput/GestureBind.h>

namespace PT
{
	class libProjectTemplate InputRecorder : public GB::InputHandler
	{
	public:
		bool handleEvent(sf::Int64 elapsedTime, const sf::Event& event) override;
		GB::KeyboardGestureBind GetCompletedBind(std::function<void()> action);

	private:
		std::vector<sf::Event> m_bindKeys;
	};
}
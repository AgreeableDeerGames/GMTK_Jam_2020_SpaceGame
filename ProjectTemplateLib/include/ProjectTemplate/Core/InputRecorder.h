#pragma once

#include <ProjectTemplate/Utils/DllUtils.h>
#include <ProjectTemplate/Utils/GestureBindUtils.h>


#include <GameBackbone/UserInput/InputHandler.h>
#include <GameBackbone/UserInput/GestureBind.h>

namespace PT
{
	class libProjectTemplate InputRecorder : public GB::InputHandler
	{
	public:
		bool handleEvent(sf::Int64 elapsedTime, const sf::Event& event) override;
		NumberGestureBind GetCompletedBind(std::string name, std::function<void()> action);

	private:
		std::vector<sf::Event> m_bindKeys;
	};
}
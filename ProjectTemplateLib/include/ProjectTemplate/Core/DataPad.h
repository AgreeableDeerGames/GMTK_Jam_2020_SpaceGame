#pragma once

#include <ProjectTemplate/Utils/DllUtils.h>
#include <ProjectTemplate/Utils/GestureBindUtils.h>

#include <GameBackbone/UserInput/InputHandler.h>

namespace PT
{
	class libProjectTemplate DataPad : public GB::InputHandler
	{
	public:

		DataPad();

		bool handleEvent(sf::Int64 elapsedTime, const sf::Event& event) override;

		void AddBind(NumberGestureBind bind);
		const NumberGestureBind* GetBindWithName(const std::string& name);
		void ReplaceBind(std::string name, NumberGestureBind bind);


	private:

		void RegenerateControls();


		// Dont use this to handle events. We just need this because 
		// GestureHandler doesn't have a way to change a single bind yet
		std::vector<NumberGestureBind> m_bindVec;
		NumberGestureHandler m_controls;

	};
}
#pragma once

#include <ProjectTemplate/Core/TerminalRegion.h>
#include <ProjectTemplate/Utils/DllUtils.h>


namespace PT
{
	class libProjectTemplate TerminalTutorial : public TerminalRegion
	{
	public:
		TerminalTutorial(sf::RenderWindow& window, std::shared_ptr<Ship> ship, std::shared_ptr<DataPad> dataPad);
		TerminalTutorial(const TerminalTutorial&) = delete;
		TerminalTutorial& operator=(const TerminalTutorial&) = delete;
		TerminalTutorial(TerminalTutorial&&) noexcept = default;
		TerminalTutorial& operator=(TerminalTutorial&&) noexcept = default;

		void update(sf::Int64 elapsedTime) override;

		// Function to Bind to Interact with the Sprinklers
		void TurnOnSprinklers();


	private:
		bool m_isInitialized;
		bool m_fireInitialized;

	};
}
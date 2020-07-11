#pragma once

#include <ProjectTemplate/Core/TerminalRegion.h>
#include <ProjectTemplate/Utils/DllUtils.h>

namespace PT
{
	class libProjectTemplate TerminalOne : public TerminalRegion
	{
	public:
		TerminalOne(std::shared_ptr<Ship> ship);
		TerminalOne(const TerminalOne&) = delete;
		TerminalOne& operator=(const TerminalOne&) = delete;

		// Press 1 Key
		void TurnOnSprinklers();

	private:

	};
}
#pragma once

#include <ProjectTemplate/Utils/DllUtils.h>
#include <ProjectTemplate/Core/TerminalRegion.h>
#include <ProjectTemplate/Core/Ship.h>

#include <memory>
#include <map>
#include <string>
#include <functional>

namespace PT
{
	class libProjectTemplate ShipControlTerminalRegion : public PT::TerminalRegion
	{
	public:
		ShipControlTerminalRegion(
			sf::RenderWindow& window,
			std::shared_ptr<Ship> ship,
			std::vector<Ship::Stat> trackedStats,
			std::shared_ptr<DataPad> dataPad,
			std::unordered_map<std::string, std::function<void()>> availableFunctions,
			std::string terminalName);

		void update(sf::Int64 elapsedTime) override;

		virtual ~ShipControlTerminalRegion() = default;

		bool m_shouldBindLogOff;

	private:
		const std::unordered_map<std::string, std::function<void()>> m_availableFunctions;
		std::unordered_map<std::string, std::function<void()>>::const_iterator m_recordFunctionIterator;
		std::string m_name;
		bool m_isInitialized;
		bool m_hasLoggedIn;

	};
}
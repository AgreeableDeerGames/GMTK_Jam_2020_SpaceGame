#include <ProjectTemplate/Core/ShipControlTerminalRegion.h>

using namespace PT;

ShipControlTerminalRegion::ShipControlTerminalRegion(sf::RenderWindow& window,
	std::shared_ptr<Ship> ship,
	std::vector<Ship::Stat> trackedStats,
	std::shared_ptr<DataPad> dataPad,
	std::unordered_map<std::string, std::function<void()>> availableFunctions,
	std::string terminalName) :

	TerminalRegion(window, std::move(ship), std::move(trackedStats), std::move(dataPad)),
	m_shouldBindLogOff(false),
	m_availableFunctions(std::move(availableFunctions)),
	m_recordFunctionIterator(m_availableFunctions.begin()),
	m_name(std::move(terminalName)),
	m_isInitialized(false),
	m_hasLoggedIn(false)
{
}

void ShipControlTerminalRegion::update(sf::Int64 elapsedTime)
{
	TerminalRegion::update(elapsedTime);

	if (m_shouldBindLogOff)
	{
		const NumberGestureBind* bind = m_dataPad->GetBindWithName(m_nextActionNameToBind);
		if (bind == nullptr)
		{
			m_terminal.m_displayedTerminal->setText("Recording data pad binding for " + m_nextActionNameToBind);
			m_isInRecordState = true;
		}
		else
		{
			m_shouldBindLogOff = false;
		}
		return;
	}
	
	if (m_terminal.IsLoggedIn())
	{
		m_hasLoggedIn = true;
		m_terminal.m_displayedTerminal->setText(m_name);
		m_terminal.m_displayedTerminal->addText("\n\n");

		if (!m_isInitialized)
		{
			// record Any available binds
			if (m_recordFunctionIterator != m_availableFunctions.end())
			{
				const NumberGestureBind* bind = m_dataPad->GetBindWithName(m_recordFunctionIterator->first);
				if (bind == nullptr)
				{
					m_terminal.m_displayedTerminal->addText("Recording data pad binding for " + m_recordFunctionIterator->first);
					m_isInRecordState = true;
					m_nextActionNameToBind = m_recordFunctionIterator->first;
					m_nextActionToBind = m_recordFunctionIterator->second;
				}
				else
				{
					++m_recordFunctionIterator;
				}

			}
			else
			{
				// We have recorded all available binds
				m_isInitialized = true;
			}
		}
		else
		{
			m_terminal.m_displayedTerminal->addText("Welcome back! ");
			m_terminal.m_displayedTerminal->addText("All available controls have already been bound to your data pad!");
		}
	}
	else
	{
		m_terminal.m_displayedTerminal->setText(m_name);
		m_terminal.m_displayedTerminal->addText("\n\n");
		if (!m_hasLoggedIn)
		{
			// Give user login info
			m_terminal.m_displayedTerminal->addText("New user identified ");
			m_terminal.m_displayedTerminal->addText("Your new password is: ");
			m_terminal.m_displayedTerminal->addText(StringifyGesture(m_terminal.GetPasscode()));
		}
		else
		{
			m_terminal.m_displayedTerminal->addText("Please log in");
		}
	}

}
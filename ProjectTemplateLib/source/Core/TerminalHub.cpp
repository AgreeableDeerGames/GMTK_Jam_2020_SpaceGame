#include <ProjectTemplate/Core/TerminalHub.h>

#include <ProjectTemplate/Core/TerminalTutorial.h>
#include <ProjectTemplate/Core/ShipControlTerminalRegion.h>

#include <string>
#include <sstream>

using namespace PT;

TerminalHub::TerminalHub(sf::RenderWindow& window, std::shared_ptr<Ship> ship, std::shared_ptr<DataPad> dataPad) :
	TemplateRegion(),
	m_regions(),
	m_dataPad(std::make_shared<DataPad>()),
	m_ship(std::make_shared<Ship>()),
	m_terminal(window, ship, {}, m_dataPad)
{
	m_regions.emplace_back(std::make_unique<TerminalTutorial>(window, m_ship, m_dataPad));
	m_terminal.LogIn();
}

tgui::Gui& TerminalHub::GetGui()
{
	return m_terminal.GetGui();
}

bool TerminalHub::handleEvent(sf::Int64 elapsedTime, const sf::Event& event)
{
	if (event.type != sf::Event::KeyPressed)
	{
		return false;
	}

	switch (event.key.code)
	{
	case sf::Keyboard::Key::Numpad1:
	case sf::Keyboard::Key::Num1:
	{
		SwapToTerminalOne();
		break;
	}
	case sf::Keyboard::Key::Numpad2:
	case sf::Keyboard::Key::Num2:
	{
		SwapToTerminalTwo();
		break;
	}
	case sf::Keyboard::Key::Numpad3:
	case sf::Keyboard::Key::Num3:
	{
		SwapToTerminalThree();
		break;
	}
	case sf::Keyboard::Key::Numpad4:
	case sf::Keyboard::Key::Num4:
	{
		break;
	}
	default:
	{
		break;
	}
	}
}

void TerminalHub::update(sf::Int64 elpsedTime)
{
	m_terminal.m_displayedTerminal->setText("Remote Log In: \n");
	m_terminal.m_displayedTerminal->addText("Please select a terminal\n\n");
	for (std::size_t i = 0; i < m_regions.size(); ++i)
	{
		if (auto controlRegion = dynamic_cast<ShipControlTerminalRegion*>(m_regions[i].get());
			controlRegion != nullptr)
		{
			std::stringstream messageBuilder;
			messageBuilder << "[" << i + 1 << "] " << controlRegion->m_name << "\n";
			m_terminal.m_displayedTerminal->addText(messageBuilder.str());
		}
	}
}

void TerminalHub::SwapToTerminalHub()
{
	for (auto& region : m_regions)
	{
		if (region->m_terminal.IsLoggedIn())
		{
			region->m_terminal.LogOut();
			region->setNextRegion(*this);
		}
	}
}

void TerminalHub::SwapToTerminalOne()
{
	this->setNextRegion(*m_regions[0]);
}

void TerminalHub::SwapToTerminalTwo()
{
	this->setNextRegion(*m_regions[1]);
}

void TerminalHub::SwapToTerminalThree()
{
	this->setNextRegion(*m_regions[2]);
}

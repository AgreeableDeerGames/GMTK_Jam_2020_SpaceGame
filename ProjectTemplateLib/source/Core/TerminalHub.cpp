#include <ProjectTemplate/Core/TerminalHub.h>

#include <ProjectTemplate/Core/TerminalOne.h>



using namespace PT;

TerminalHub::TerminalHub(sf::RenderWindow& window, std::shared_ptr<Ship> ship, std::shared_ptr<DataPad> dataPad) :
	TemplateRegion(),
	m_regions(),
	m_dataPad(std::make_shared<DataPad>()),
	m_ship(std::make_shared<Ship>()),
	m_gui(window)
{
	m_regions.emplace_back(std::make_unique<TerminalOne>(window, m_ship, m_dataPad));
}

tgui::Gui& TerminalHub::GetGui()
{
	return m_gui;
}


void TerminalHub::SwapToTerminalOne()
{
	this->setNextRegion(*m_regions[0]);
}

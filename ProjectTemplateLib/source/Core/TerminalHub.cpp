#include <ProjectTemplate/Core/TerminalHub.h>

#include <ProjectTemplate/Core/TerminalOne.h>



using namespace PT;

TerminalHub::TerminalHub(sf::RenderWindow& window, std::shared_ptr<Ship> ship, std::shared_ptr<DataPad> dataPad) :
	TemplateRegion(),
	m_gui(window)
{
	m_regions.emplace_back(std::make_unique<TerminalOne>(window, std::make_shared<Ship>(), std::make_shared<DataPad>()));
}

tgui::Gui& TerminalHub::GetGui()
{
	return m_gui;
}


void TerminalHub::SwapToTerminalOne()
{
	this->setNextRegion(*m_regions[0]);
}

#include <ProjectTemplate/Core/TerminalHub.h>



using namespace PT;

TerminalHub::TerminalHub(sf::RenderWindow& window, std::shared_ptr<Ship> ship) :
	TemplateRegion(),
	m_gui(window)
{

}


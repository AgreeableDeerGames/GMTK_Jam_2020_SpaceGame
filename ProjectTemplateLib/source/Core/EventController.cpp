#include <ProjectTemplate/Core/EventController.h>

#include <string>

using namespace PT;

#define APP_NAME "ProjectTemplate"

EventController::EventController() : CoreEventController(APP_NAME),
	m_ship(std::make_shared<Ship>()),
	mainRegion(getWindow(), m_ship)
{
	setActiveRegion(&mainRegion);
}

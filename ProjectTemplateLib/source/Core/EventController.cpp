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

void PT::EventController::draw()
{
	GB::CoreEventController::draw();
	PostDraw();
}

void PT::EventController::PostDraw()
{
	static_cast<TemplateRegion*>(getActiveRegion())->m_gui.draw();
}
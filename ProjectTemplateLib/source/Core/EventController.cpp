#include <ProjectTemplate/Core/EventController.h>

#include <string>

using namespace PT;

#define APP_NAME "ProjectTemplate"

EventController::EventController() : CoreEventController(APP_NAME),
	m_mainMenuRegion(getWindow())
{
	setActiveRegion(&m_mainMenuRegion);
}

void PT::EventController::draw()
{
	GB::CoreEventController::draw();
	PostDraw();
}

void PT::EventController::PostDraw()
{
	static_cast<TemplateRegion*>(getActiveRegion())->GetGui().draw();
}
#include <ProjectTemplate/Core/EventController.h>

#include <string>

using namespace PT;

#define APP_NAME "ProjectTemplate"

EventController::EventController() : CoreEventController(APP_NAME), mainRegion()
{
	setActiveRegion(&mainRegion);
}

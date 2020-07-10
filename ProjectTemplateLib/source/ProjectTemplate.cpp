#include <ProjectTemplate.h>

#include <ProjectTemplate/Core/EventController.h>

using namespace PT;
ProjectTemplate::ProjectTemplate()
{
	// Initialize an instance of DemoCoreEventController
	EventController controller;
	// Start the loop on the DemoCoreEventController to start the Demo
	controller.runLoop();
}
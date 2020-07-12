#include <ProjectTemplate/Core/EventController.h>

#include <string>

using namespace PT;

#define APP_NAME "ProjectTemplate"

EventController::EventController() : CoreEventController(APP_NAME),
	m_mainMenuRegion(getWindow()),
	m_gameLostRegion(getWindow())
{
	s_mainMenuRegion = &m_mainMenuRegion;
	s_gameLostRegion = &m_gameLostRegion;
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

MainMenuRegion* PT::EventController::GetGlobalMainMenuRegion()
{
	return s_mainMenuRegion;
}

GameLostRegion* PT::EventController::GetGlobalGameLostRegion()
{
	return s_gameLostRegion;
}
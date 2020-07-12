#pragma once

#include <ProjectTemplate/Core/MainMenuRegion.h>
#include <ProjectTemplate/Core/GameLostRegion.h>
#include <ProjectTemplate/Core/MainMenuRegion.h>
#include <ProjectTemplate/Core/Ship.h>
#include <ProjectTemplate/Core/TemplateRegion.h>
#include <ProjectTemplate/Core/TerminalOne.h>
#include <ProjectTemplate/Core/TerminalRegion.h>
#include <ProjectTemplate/Utils/DllUtils.h>

#include <GameBackbone/Core/CoreEventController.h>

namespace PT
{
	class libProjectTemplate EventController final : public GB::CoreEventController
	{
	public:
		// Constructors
		EventController();
		EventController(const EventController& other) = delete;
		EventController(EventController&& other) = default;
		EventController& operator=(const EventController& other) = delete;
		EventController& operator=(EventController&& other) = default;
		virtual ~EventController() = default;

		void draw() override;

		static MainMenuRegion* GetGlobalMainMenuRegion();
		static GameLostRegion* GetGlobalGameLostRegion();

	private:
		void PostDraw();
		MainMenuRegion m_mainMenuRegion;
		GameLostRegion m_gameLostRegion;
		inline static MainMenuRegion* s_mainMenuRegion = nullptr;
		inline static GameLostRegion* s_gameLostRegion = nullptr;
	};
}

#pragma once

#include <framework/TimerManager.h>
#include <framework/World.h>


namespace ly
{
	class Actor;
	class PlayerSpaceship;
	class LevelOne : public World
	{
	public:
		LevelOne(Application* owningApplication);

	private:
		virtual void BeginPlay() override; 
		virtual void InitGameStages() override;

		weak_ptr<PlayerSpaceship> _testPlayerSpaceship;

		TimerHandle _timerHandle_Test;

	};
}

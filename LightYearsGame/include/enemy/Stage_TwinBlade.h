#pragma once

#include <framework/TimerManager.h>
#include <gameplay/GameStage.h>
#include <SFML/Graphics.hpp>

namespace ly
{
	class Stage_TwinBlade : public GameStage
	{
	public:
		Stage_TwinBlade(World* owningWorld);

		virtual void StartStage() override;

	private:
		void SpawnTwinbBlade();

		virtual void StageFinished() override;

		float _spawnInterval;
		float _switchInterval;
		float _spawnDistanceToCenter;

		sf::Vector2f _leftSpawnLoc;
		sf::Vector2f _rightSpawnLoc;
		sf::Vector2f _spawnLoc;

		TimerHandle _spawnTimerHandle;

		int _spawnAmount;
		int _currentTwinBladeCount;
	};
}

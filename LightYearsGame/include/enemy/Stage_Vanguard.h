#pragma once

#include <framework/TimerManager.h>
#include <gameplay/GameStage.h>
#include <SFML/Graphics.hpp>

namespace ly
{
	class Stage_Vanguard : public GameStage
	{
	public:
		Stage_Vanguard(World* owningWorld);

		virtual void StartStage() override;

	private:
		void SpawnVangurd();
		void SwitchRow();

		virtual void StageFinished() override;

		float _spawnInterval;
		float _switchInterval;
		float _spawnDistanceToEdge;

		sf::Vector2f _leftSpawnLoc;
		sf::Vector2f _rightSpawnLoc;
		sf::Vector2f _spawnLoc;

		TimerHandle _spawnTimerHandle;
		TimerHandle _switchTimerHandle;

		int _rowsToSpawn;
		int _rowsSpawnCount;

		int _vanguardsPerRow;
		int _currentRowVanguardCount;

	};
}

#pragma once

#include <framework/TimerManager.h>
#include <gameplay/GameStage.h>
#include <SFML/Graphics.hpp>

namespace ly
{
	class Stage_Hexagon : public GameStage
	{
	public:
		Stage_Hexagon(World* owningWorld);

		virtual void StartStage() override;

	private:
		virtual void StageFinished() override;
		void SpawnHexegon();

		float _spawnInterval;
		float _sideSpawnOffset;

		int _spawnGroupAmount;
		int _currentSpawnCount;

		sf::Vector2f _midSpawnLoc;
		sf::Vector2f _leftSpawnLoc;
		sf::Vector2f _rightSpawnLoc;

		TimerHandle _spawnTimer;
	};
}

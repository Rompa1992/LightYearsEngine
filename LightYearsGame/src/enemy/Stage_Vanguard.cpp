#include "enemy/Stage_Vanguard.h"

#include "enemy/Enemy_Vanguard.h"
#include <framework/World.h>

namespace ly
{

	/// Public Members
	/// --------------
	Stage_Vanguard::Stage_Vanguard(World* owningWorld)
		: GameStage{ owningWorld },
		_spawnInterval{ 1.f },
		_switchInterval{ 2.f },
		_spawnDistanceToEdge{ 100.f },
		_leftSpawnLoc{ 0.f, 0.f },
		_rightSpawnLoc{ 0.f, 0.f },
		_spawnLoc{ 0.f, 0.f },
		_rowsToSpawn{ 1 },
		_rowsSpawnCount{ 0 },
		_vanguardsPerRow{ 5 },
		_currentRowVanguardCount{ 0 }
	{
	}

	/// override
	void Stage_Vanguard::StartStage()
	{
		auto windowSize = GetWorld()->GetWindowSize();
		_leftSpawnLoc = sf::Vector2f{ _spawnDistanceToEdge, -100.f };
		_rightSpawnLoc = sf::Vector2f{ windowSize.x - _spawnDistanceToEdge, -100.f };

		SwitchRow();
	}

	/// Private Members
	/// ---------------

	/// void
	void Stage_Vanguard::SpawnVangurd()
	{
		weak_ptr<Enemy_Vanguard> newVanguard = GetWorld()->SpawnActor<Enemy_Vanguard>();
		newVanguard.lock()->SetActorLocation(_spawnLoc);
		++_currentRowVanguardCount;

		if (_currentRowVanguardCount == _vanguardsPerRow)
		{
			TimerManager::Get().ClearTimer(_spawnTimerHandle);
			_switchTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &Stage_Vanguard::SwitchRow, _switchInterval, false);
			_currentRowVanguardCount = 0;
		}
	}

	void Stage_Vanguard::SwitchRow()
	{
		if (_rowsSpawnCount == _rowsToSpawn)
		{
			FinsishStage();
			return;
		}

		if (_spawnLoc == _leftSpawnLoc)
			_spawnLoc = _rightSpawnLoc;
		else
			_spawnLoc = _leftSpawnLoc;

		_spawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &Stage_Vanguard::SpawnVangurd, _spawnInterval, true);

		++_rowsSpawnCount;
	}

	/// override
	void Stage_Vanguard::StageFinished()
	{
		TimerManager::Get().ClearTimer(_spawnTimerHandle);
		TimerManager::Get().ClearTimer(_switchTimerHandle);
	}

}

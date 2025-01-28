#include "enemy/Stage_TwinBlade.h"

#include "enemy/Enemy_TwinBlade.h"
#include <framework/World.h>

namespace ly
{

	/// Public Members
	/// --------------
	Stage_TwinBlade::Stage_TwinBlade(World* owningWorld)
		: GameStage{ owningWorld },
		_spawnInterval{ 1.f },
		_switchInterval{ 2.f },
		_spawnDistanceToCenter{ 100.f },
		_leftSpawnLoc{ owningWorld->GetWindowSize().x/2.f - _spawnDistanceToCenter, -100.f },
		_rightSpawnLoc{ owningWorld->GetWindowSize().x/2.f + _spawnDistanceToCenter, -100.f },
		_spawnLoc{ _leftSpawnLoc },
		_spawnAmount{ 10 },
		_currentTwinBladeCount{ 0 }
	{
	}

	/// override
	void Stage_TwinBlade::StartStage()
	{
		_spawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &Stage_TwinBlade::SpawnTwinbBlade, _spawnInterval, true);
	}

	/// Private Members
	/// ---------------

	/// void
	void Stage_TwinBlade::SpawnTwinbBlade()
	{
		weak_ptr<Enemy_TwinBlade> newTwinBlade = GetWorld()->SpawnActor<Enemy_TwinBlade>();
		newTwinBlade.lock()->SetActorLocation(_spawnLoc);

		if (_spawnLoc == _leftSpawnLoc)
			_spawnLoc = _rightSpawnLoc;
		else
			_spawnLoc = _leftSpawnLoc;

		++_currentTwinBladeCount;

		if (_currentTwinBladeCount == _spawnAmount)
			FinsishStage();
	}

	/// override
	void Stage_TwinBlade::StageFinished()
	{
		TimerManager::Get().ClearTimer(_spawnTimerHandle);
	}

}

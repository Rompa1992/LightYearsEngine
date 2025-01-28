#include "enemy/Stage_Hexagon.h"

#include "enemy/Enemy_Hexagon.h"
#include "framework/World.h"

namespace ly
{


	/// Public Members
	/// --------------
	Stage_Hexagon::Stage_Hexagon(World* owningWorld)
		: GameStage{ owningWorld },
		_spawnInterval{ 3.f },
		_sideSpawnOffset{ 80.f },
		_spawnGroupAmount{ 5 },
		_currentSpawnCount{ 0 },
		_midSpawnLoc{ owningWorld->GetWindowSize().x/2.f, -100.f},
		_leftSpawnLoc{ owningWorld->GetWindowSize().x/2.f - _sideSpawnOffset, -100.f - _sideSpawnOffset},
		_rightSpawnLoc{ owningWorld->GetWindowSize().x/2.f + _sideSpawnOffset, -100.f - _sideSpawnOffset }
	{
	}

	/// override
	void Stage_Hexagon::StartStage()
	{
		_spawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &Stage_Hexagon::SpawnHexegon, _spawnInterval, true);
	}

	/// Private Members
	/// ---------------
	void Stage_Hexagon::StageFinished()
	{
		TimerManager::Get().ClearTimer(_spawnTimer);
	}

	void Stage_Hexagon::SpawnHexegon()
	{
		weak_ptr<Enemy_Hexagon> newHexagon = GetWorld()->SpawnActor<Enemy_Hexagon>();
		newHexagon.lock()->SetActorLocation(_midSpawnLoc);

		newHexagon = GetWorld()->SpawnActor<Enemy_Hexagon>();
		newHexagon.lock()->SetActorLocation(_leftSpawnLoc);

		newHexagon = GetWorld()->SpawnActor<Enemy_Hexagon>();
		newHexagon.lock()->SetActorLocation(_rightSpawnLoc);

		if (++_currentSpawnCount == _spawnGroupAmount)
			FinsishStage();
		
	}

}

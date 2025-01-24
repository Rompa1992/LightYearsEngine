#include "levels/LevelOne.h"
#include "enemy/Enemy_Vanguard.h"
#include "player/PlayerSpaceship.h"

#include <framework/Actor.h>
#include <framework/AssetManager.h>
#include <framework/TimerManager.h>

namespace ly
{
	bool operator==(const TimerHandle& lhs, const TimerHandle& rhs)
	{
		return lhs.GetTimerKey() == rhs.GetTimerKey();
	}

	/// Public Functions
	/// -----------------
	LevelOne::LevelOne(Application* owningApplication)
		: World{owningApplication}
	{
		_testPlayerSpaceship = SpawnActor<PlayerSpaceship>();
		_testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));

		weak_ptr<Enemy_Vanguard> testSpaceship = SpawnActor<Enemy_Vanguard>();
		testSpaceship.lock()->SetActorLocation(sf::Vector2f{ 100.f, 50.f });

	}

	void LevelOne::BeginPlay()
	{
		_timerHandle_Test = TimerManager::Get().SetTimer(GetWeakRef(), &LevelOne::TimerCallback_Test, 2, true);
	}

	void LevelOne::TimerCallback_Test()
	{
		LOG("callback called! lvl one");
		TimerManager::Get().ClearTimer(_timerHandle_Test);
	}

	/// Void


	/// Override


	/// Setters


	/// Getters



	/// Private Functions
	/// -----------------
}

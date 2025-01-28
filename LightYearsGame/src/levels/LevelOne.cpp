#include "levels/LevelOne.h"
#include <framework/Actor.h>
#include <framework/AssetManager.h>
#include <framework/TimerManager.h>
#include <gameplay/GameStage.h>
#include "enemy/Stage_Hexagon.h"
#include "enemy/Stage_TwinBlade.h"
#include "enemy/Stage_Vanguard.h"
#include "gameplay/WaitStage.h"
#include "player/PlayerSpaceship.h"


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

	}

	/// Void
	void LevelOne::BeginPlay()
	{
		
	}

	void LevelOne::InitGameStages()
	{
		AddStage(shared_ptr<Stage_Vanguard>{ new Stage_Vanguard{ this }});
		AddStage(shared_ptr<WaitStage>{ new WaitStage{ this, 5.f }});
		AddStage(shared_ptr<Stage_TwinBlade>{ new Stage_TwinBlade{ this }});
		AddStage(shared_ptr<WaitStage>{ new WaitStage{ this, 5.f }});
		AddStage(shared_ptr<Stage_Hexagon>{ new Stage_Hexagon{ this }});
	}


}

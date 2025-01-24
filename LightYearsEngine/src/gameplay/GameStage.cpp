#include "gameplay/GameStage.h"

#include "framework/Core.h"

namespace ly
{


	/// Public Members
	/// --------------
	GameStage::GameStage(World* owningWorld)
		: _world{ owningWorld  },
		_stageFinished { false }
	{

	}

	/// void
	void GameStage::FinsishStage()
	{
		onStageFinished.BroadCast();
		_stageFinished = true;
		StageFinsihed();
	}

	/// virtual void
	void GameStage::StartStage()
	{
		LOG("stage started");
	}

	void GameStage::TickStage(float deltaTime)
	{
		LOG("stage Ticking");
	}

	/// Set


	/// Get


	/// Private Members
	/// ---------------
	void GameStage::StageFinsihed()
	{
		LOG("stage Finished");
	}

}

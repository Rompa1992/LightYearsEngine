#include "gameplay/WaitStage.h"

#include "framework/TimerManager.h"

namespace ly
{
	WaitStage::WaitStage(World* owningWorld, const float waitDuration)
		: GameStage{owningWorld},
		_waitDuration{ waitDuration }
	{
	}

	void WaitStage::StartStage()
	{
		TimerManager::Get().SetTimer(GetWeakRef(), &WaitStage::FinsishStage, _waitDuration, false);
	}

}

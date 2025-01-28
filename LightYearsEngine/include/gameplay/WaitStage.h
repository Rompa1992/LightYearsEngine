#pragma once

#include "gameplay/GameStage.h"

namespace ly
{
	class WaitStage : public GameStage
	{
	public:
		WaitStage(World* owningWorld, const float waitDuration);

		virtual void StartStage() override;

	private:
		const float _waitDuration;

	};
}

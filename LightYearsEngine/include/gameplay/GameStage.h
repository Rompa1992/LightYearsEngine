#pragma once

#include "framework/Delegate.h"
#include "framework/Object.h"

namespace ly
{
	class World;
	class GameStage : public Object
	{
	public:
		GameStage(World* owningWorld);

		void FinsishStage();

		virtual void StartStage();
		virtual void TickStage(float deltaTime);

		bool IsStageFinished() const { return _stageFinished; }

		const World* GetWorld() const { return _world; }
		World* GetWorld() { return _world; }

		Delegate<> onStageFinished;

	private:
		virtual void StageFinsihed();

		World* _world;
		bool _stageFinished;

	};
}

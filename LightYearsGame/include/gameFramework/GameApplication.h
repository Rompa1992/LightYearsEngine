#pragma once
#include <framework/Application.h>
#include <framework/Core.h>

namespace ly
{
	class Actor;
	class PlayerSpaceship;
	class GameApplication : public Application																				// Public members of Application remain public in GameApplication.
	{
	public:
		GameApplication();

		virtual void Tick(float deltaTime) override;
	private:
		float _counter;
		weak_ptr<PlayerSpaceship> _testPlayerSpaceship;
	};
}
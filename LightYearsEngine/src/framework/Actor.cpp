#include "framework/Actor.h"
#include "framework/Core.h"


namespace ly
{
	Actor::Actor(World* owningWorld)
		: _owningWorld{ owningWorld },
		  _hasBeganPlay{ false }
	{

	}

	void ly::Actor::BeginPlayInternal()
	{
		if (!_hasBeganPlay)
		{
			_hasBeganPlay = true;
			BeginPlay();
		}
	}

	void ly::Actor::BeginPlay()
	{
		LOG("Actor began play");
	}

	void Actor::Tick(float deltaTime)
	{
		LOG("Actor Ticking");
	}
}

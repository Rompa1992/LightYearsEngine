#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"

namespace ly 
{
	World::World(Application* owningApp)
		: _owningApp{owningApp},
		  _hasBeganPlay{false},
		  _actors{},
		  _pendingActors{}
	{


	}

	void World::BeginPlayInternal()
	{
		if (!_hasBeganPlay) 
		{
			_hasBeganPlay = true;
			BeginPlay();
		}
	}

	void World::BeginPlay()
	{
		LOG("Begin play");
	}

	void World::TickInternal(float deltaTime)
	{
		for (shared_ptr<Actor> actor : _pendingActors)
		{
			_actors.push_back(actor);
			actor->BeginPlayInternal();
		}

		_pendingActors.clear();

		for (shared_ptr<Actor> actor : _actors)
		{
			actor->Tick(deltaTime);
		}

		Tick(deltaTime);
	}

	void World::Tick(float deltaTime)
	{
		LOG("Tick at frame rate: %f", 1.f / deltaTime);
	}

	World::~World()
	{

	}

}


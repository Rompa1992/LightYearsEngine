#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/Application.h"
#include "framework/Core.h"

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

		for (auto iter = _actors.begin(); iter != _actors.end();)																// CodeExplanations->World.cpp: 'TickInternal()'
		{
			if (iter->get()->IsPendingDestroy())
				iter = _actors.erase(iter);
			else
			{
				iter->get()->TickInternal(deltaTime);
				++iter;
			}
		}

		Tick(deltaTime);
	}

	void World::Render(sf::RenderWindow& window)
	{
		for (auto actor : _actors)
		{
			actor->Render(window);
		}
	}

	sf::Vector2u World::GetWindowSize() const
	{
		return _owningApp->GetWindowSize(); 
	}

	void World::Tick(float deltaTime)
	{
		//LOG("Tick at frame rate: %f", 1.f / deltaTime);
	}

	World::~World()
	{

	}

}


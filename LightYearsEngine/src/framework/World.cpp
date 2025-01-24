#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/Application.h"
#include "framework/Core.h"
#include "gameplay/GameStage.h"

namespace ly 
{
	World::World(Application* owningApp)
		: _owningApp{owningApp},
		_hasBeganPlay{false},
		_actors{},
		_pendingActors{},
		_currentStageIndex{}
	{


	}

	void World::BeginPlayInternal()
	{
		if (!_hasBeganPlay) 
		{
			_hasBeganPlay = true;
			BeginPlay();
			InitGameStages();
			NextGameStage();
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
			iter->get()->TickInternal(deltaTime);																				// Clean cylcle implementation added to function "World::CleanCycle()"
			++iter;
		}

		if (_currentStageIndex >= 0 && _currentStageIndex < _gameStages.size())													// Game Stages Tick
			_gameStages[_currentStageIndex]->TickStage(deltaTime);

		Tick(deltaTime);
	}

	void World::Render(sf::RenderWindow& window)
	{
		for (auto actor : _actors)
		{
			actor->Render(window);
		}
	}

	void World::CleanCycle()
	{
		for (auto iter = _actors.begin(); iter != _actors.end();)																// CodeExplanations->World.cpp: 'TickInternal()'
		{
			if (iter->get()->IsPendingDestroy())
				iter = _actors.erase(iter);
			else
				++iter;
		}

		for (auto iter = _gameStages.begin(); iter != _gameStages.end();)
		{
			if (iter->get()->IsStageFinished())
				iter = _gameStages.erase(iter);
			else
				++iter;
		}
	}

	void World::AddStage(const shared_ptr<GameStage>& newStage)
	{
		_gameStages.push_back(newStage);
	}

	sf::Vector2u World::GetWindowSize() const
	{
		return _owningApp->GetWindowSize(); 
	}

	void World::Tick(float deltaTime)
	{
		//LOG("Tick at frame rate: %f", 1.f / deltaTime);
	}

	void World::InitGameStages()
	{

	}

	void World::AllGameStagesFinished()
	{

	}

	void World::NextGameStage()
	{
		++_currentStageIndex;

		if (_currentStageIndex >= 0 && _currentStageIndex < _gameStages.size())
		{
			_gameStages[_currentStageIndex]->onStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
			_gameStages[_currentStageIndex]->StartStage();
		}
		else
		{
			AllGameStagesFinished();
		}
	}

	World::~World()
	{

	}

}


#pragma once

#include <SFML/Graphics.hpp>

#include "framework/Core.h"
#include "framework/Object.h"

namespace ly
{
	class Actor;																										// CodeExplanations->When to Forward Declare vs Include
	class Application;
	class GameStage;

	class World : public Object 
	{
	public:
		World(Application* owningApp);

		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		void Render(sf::RenderWindow& window);
		void CleanCycle();
		void AddStage(const shared_ptr<GameStage>& newStage);

		sf::Vector2u GetWindowSize() const;

		template<typename ActorType, typename... Args>
		weak_ptr<ActorType> SpawnActor(Args... args);

		virtual ~World();																								// Use a virtual destructor in base classes to ensure proper cleanup of derived class objects. This ensures that derived class destructors are called properly during deletion, preventing resource leaks or undefined behaviour

	private:
		void NextGameStage();
		void StartStages();

		virtual void BeginPlay();
		virtual void Tick(float deltaTime);

		virtual void InitGameStages();
		virtual void AllGameStagesFinished();

		Application* _owningApp;
		bool _hasBeganPlay;

		List<shared_ptr<Actor>> _actors;
		List<shared_ptr<Actor>> _pendingActors;
		List<shared_ptr<GameStage>> _gameStages;
		List<shared_ptr<GameStage>>::iterator _currentStage;

	};

	template<typename ActorType, typename... Args>
	weak_ptr<ActorType> World::SpawnActor(Args... args)
	{
		shared_ptr<ActorType> newActor{ new ActorType(this, args...) };
		_pendingActors.push_back(newActor);
		return newActor;
	}

}
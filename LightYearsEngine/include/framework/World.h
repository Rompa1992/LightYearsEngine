#pragma once

#include <SFML/Graphics.hpp>

#include "framework/Core.h"

namespace ly
{
	class Actor;
	class Application;

	class World
	{
	public:
		World(Application* owningApp);

		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		void Render(sf::RenderWindow& window);

		sf::Vector2u GetWindowSize() const;

		template<typename ActorType>
		weak_ptr<ActorType> SpawnActor();

		virtual ~World();																										// Use a virtual destructor in base classes to ensure proper cleanup of derived class objects. This ensures that derived class destructors are called properly during deletion, preventing resource leaks or undefined behaviour

	private:
		void BeginPlay();
		void Tick(float deltaTime);

		Application* _owningApp;
		bool _hasBeganPlay;

		List<shared_ptr<Actor>> _actors;
		List<shared_ptr<Actor>> _pendingActors;
	};

	template<typename ActorType>
	weak_ptr<ActorType> World::SpawnActor()
	{
		shared_ptr<ActorType> newActor{ new ActorType{this} };
		_pendingActors.push_back(newActor);
		return newActor;
	}

}
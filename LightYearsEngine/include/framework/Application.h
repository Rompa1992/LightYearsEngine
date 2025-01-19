#pragma once 

#include <SFML/Graphics.hpp>
#include "framework/Core.h"

namespace ly
{
	class World;																													// Forward declaration of the World class to reduce dependencies and improve compilation times.

	class Application																												// CodeExplanations->Application Process
	{
	public:
		Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style);
		void Run();

		template<typename WorldType>
		weak_ptr<WorldType> LoadWorld();																							// Returns a weak_ptr to avoid directly managing the lifetime of the loaded world.

		sf::Vector2u GetWindowSize() const;

	private:
		void TickInternal(float deltaTime);
		void RenderInternal();

		virtual void Tick(float deltaTime);
		virtual void Render();

		sf::RenderWindow _window; 
		float _targetFrameRate;   
		sf::Clock _tickClock;     

		shared_ptr<World> _currentWorld;																							// Shared pointer to the currently loaded world, managing its lifetime.
		sf::Clock _cleanCycleClock;
		float _CleanCycleInterval;

	};

	template<typename WorldType>
	weak_ptr<WorldType> Application::LoadWorld()
	{
		shared_ptr<WorldType> newWorld{ new WorldType{this} };																		// Create a new world instance using a shared_ptr, which ensures proper memory management.
		_currentWorld = newWorld;																									// Update the current world with the newly loaded one.
		_currentWorld->BeginPlayInternal();
		return newWorld;																											// Return a weak_ptr to avoid strong ownership by the caller.
	}

}

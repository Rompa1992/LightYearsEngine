#include "framework/Application.h"
#include "framework/AssetManager.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "framework/PhysicsSystem.h"

namespace ly
{
	Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style)
		: _window{ sf::VideoMode(windowWidth, windowHeight), title, style },
		_targetFrameRate{ 60.f },
		_tickClock{},
		_currentWorld{ nullptr },
		_cleanCycleClock{},
		_CleanCycleInterval{2.f}
	{

	}

	void Application::Run()																											// called in the EntryPoint.cpp through GetApplication which returns a GameApplication
	{
		_tickClock.restart();
		float accumulatedTime = 0.f;
		float targetDeltaTime = 1.f / _targetFrameRate;																				// DeltaTime = 1s / FrameRate

		while (_window.isOpen())
		{
			sf::Event windowEvent;
			while (_window.pollEvent(windowEvent))
			{
				if (windowEvent.type == sf::Event::EventType::Closed)
					_window.close();
			}

			accumulatedTime += _tickClock.restart().asSeconds();																	// _tickClock.restart() restarts the time and returns the amount of time that has elapsed. 

			while (accumulatedTime > targetDeltaTime)
			{
				accumulatedTime -= targetDeltaTime;
				TickInternal(targetDeltaTime);
				RenderInternal();
			}
		}
	}

	sf::Vector2u Application::GetWindowSize() const
	{
		return _window.getSize();
	}

	void Application::TickInternal(float deltaTime)
	{
		Tick(deltaTime);
		
		if (_currentWorld)
		{
			_currentWorld->TickInternal(deltaTime);
		}

		PhysicsSystem::Get().Step(deltaTime);

		if (_cleanCycleClock.getElapsedTime().asSeconds() >= _CleanCycleInterval)
		{
			_cleanCycleClock.restart();
			AssetManager::Get().CleanCycle();

			if (_currentWorld)
				_currentWorld->CleanCycle();
		}
	}

	void Application::Tick(float deltaTime)
	{
		//LOG("ticking at framerate: %f", 1.f / deltaTime);																		    // A macro like LOG is processed during the preprocessing phase, which occurs before the actual compilation step.
	}

	void Application::RenderInternal()
	{
		_window.clear();
		Render();
		_window.display();
	}

	void Application::Render()
	{
		if (_currentWorld)
		{
			_currentWorld->Render(_window);
		}
	}
}
  

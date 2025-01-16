#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"

namespace ly
{
	Application::Application()
		: _window{ sf::VideoMode(1024, 1440), "Light Years Window" },
		_targetFrameRate{ 60.f },
		_tickClock{},
		_currentWorld{ nullptr }
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

	void Application::TickInternal(float deltaTime)
	{
		Tick(deltaTime);
		
		if (_currentWorld)
		{
			_currentWorld->TickInternal(deltaTime);
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

	}
}
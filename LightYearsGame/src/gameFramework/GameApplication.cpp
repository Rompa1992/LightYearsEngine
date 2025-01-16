#include "gameFramework/gameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"

ly::Application* GetApplication()
{
	return new ly::GameApplication;																							// Why dynamic allocation? (Heap) Ensures the GameApplication object persists beyond GetApplication's scope and remains valid until explicitly deleted.

	/**
	 * GetApplication():
	 * - Calls the global function GetApplication(), which creates a new GameApplication object
	 *   and returns a pointer to it.
	 * - The GameApplication object is treated as an Application due to inheritance.
	 *
	 * app->Run(): (called from EntryPoint.cpp)
	 * - Executes the Run() method of the Application class. If GameApplication overrides Run(),
	 *   the overridden version is called (thanks to polymorphism).
	 * - This is where the main loop and application logic are executed.
	 */
}

namespace ly
{
	GameApplication::GameApplication()
	{
		weak_ptr<World> newWorld = LoadWorld<World>();

		newWorld.lock()->SpawnActor<Actor>();																				 // Converts weak_ptr to shared_ptr to ensure safe access before using the object.
	}
}
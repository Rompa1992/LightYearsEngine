#include "gameFramework/gameApplication.h"
#include "player/PlayerSpaceship.h"

#include <framework/Actor.h>
#include <framework/AssetManager.h>
#include <config.h>
#include <framework/World.h>


ly::Application* GetApplication()
{
	return new ly::GameApplication;																							// Why dynamic allocation? (Heap) Ensures the GameApplication object persists beyond GetApplication's scope and remains valid until explicitly deleted.

}

namespace ly
{
	GameApplication::GameApplication()
		: Application{600, 980, "Light Years", sf::Style::Titlebar | sf::Style::Close}
	{
		AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
		weak_ptr<World> newWorld = LoadWorld<World>();

		newWorld.lock()->SpawnActor<Actor>();																				 // Converts weak_ptr to shared_ptr to ensure safe access before using the object.
		_testPlayerSpaceship = newWorld.lock()->SpawnActor<PlayerSpaceship>();
		_testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
		_counter = 0;
	}
	void GameApplication::Tick(float deltaTime)
	{
		_counter += deltaTime;

		if (_counter > 20.f && !_testPlayerSpaceship.expired())
			_testPlayerSpaceship.lock()->Destroy();	
	}
}
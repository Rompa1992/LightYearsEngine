#include "gameFramework/gameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "config.h"

ly::Application* GetApplication()
{
	return new ly::GameApplication;																							// Why dynamic allocation? (Heap) Ensures the GameApplication object persists beyond GetApplication's scope and remains valid until explicitly deleted.

}

namespace ly
{
	GameApplication::GameApplication()
		: Application{600, 980, "Light Years", sf::Style::Titlebar | sf::Style::Close}
	{
		weak_ptr<World> newWorld = LoadWorld<World>();

		newWorld.lock()->SpawnActor<Actor>();																				 // Converts weak_ptr to shared_ptr to ensure safe access before using the object.
		_actorToDestroy = newWorld.lock()->SpawnActor<Actor>();
		_actorToDestroy.lock()->SetTexture(GetResourceDir() + "SpaceShooterRedux/PNG/playerShip1_blue.png");
		_actorToDestroy.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
		_actorToDestroy.lock()->SetActorRotation(90.f);

		_counter = 0;
	}
	void GameApplication::Tick(float deltaTime)
	{
		_counter += deltaTime;

		if (_counter > 2.f && !_actorToDestroy.expired())
			_actorToDestroy.lock()->Destroy();	
	}
}
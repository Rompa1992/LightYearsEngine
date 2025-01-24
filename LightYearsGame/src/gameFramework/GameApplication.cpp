#include "gameFramework/gameApplication.h"
#include "levels/LevelOne.h"

#include <config.h>
#include <framework/AssetManager.h>


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
		weak_ptr<LevelOne> newWorld = LoadWorld<LevelOne>();

	}

	void GameApplication::Tick(float deltaTime)
	{
	}
}
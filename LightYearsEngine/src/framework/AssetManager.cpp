#include "framework/AssetManager.h"

namespace ly
{
	unique_ptr<AssetManager> AssetManager::_assetManager{ nullptr };

	AssetManager& AssetManager::Get()																							// CodeExplanations->AssetManager: `AssetManager::Get
	{
		if (!_assetManager)
			_assetManager = std::move(unique_ptr<AssetManager>{ new AssetManager });
		
		return *_assetManager;
	}

	shared_ptr<sf::Texture> AssetManager::LoadTexture(const std::string& path)													// CodeExplanations->AssetManager: `LoadTexture()`
	{
		auto found = _loadedTextureMap.find(path);																				// returns an iterator
		
		if (found != _loadedTextureMap.end())
			return found->second;

		shared_ptr<sf::Texture> newTexture{ new sf::Texture };

		if (newTexture->loadFromFile(path))
		{
			_loadedTextureMap.insert({ path, newTexture });
			return newTexture;
		}

		return shared_ptr<sf::Texture> {nullptr};
	}

	void AssetManager::CleanCycle()																								// CodeExplanation->AssetManager: `CleanCycle()`
	{
		for (auto iter = _loadedTextureMap.begin(); iter != _loadedTextureMap.end();)
		{
			if (iter->second.unique())
			{
				LOG("Cleaning texture: %s", iter->first.c_str());
				iter = _loadedTextureMap.erase(iter);
			}
			else
				++iter;
		}

	}


	AssetManager::AssetManager()
	{

	}
}


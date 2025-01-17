#pragma once

#include <SFML/Graphics.hpp>

#include "framework/Core.h"

namespace ly
{
	// Singleton Class
	class AssetManager																												// CodeExplanations->Class Explanation: `AssetManager`
	{
	public:
		static AssetManager& Get();
		shared_ptr<sf::Texture> LoadTexture(const std::string& path);																// CodeExplanations->AssetManager: `LoadTexture()`
		void CleanCycle();																											// CodeExplanation->AssetManager: `CleanCycle()`

	protected:
		AssetManager();																												// Even though this class is a "singleton" we can still make child classes of this.

	private:
		static unique_ptr<AssetManager> _assetManager;
		Dictionary<std::string, shared_ptr<sf::Texture>> _loadedTextureMap;
	};
}
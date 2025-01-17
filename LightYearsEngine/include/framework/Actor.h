#pragma once 

#include <SFML/Graphics.hpp>

#include "framework/Core.h"
#include "framework/Object.h"

namespace ly
{
	class World;

	class Actor : public Object
	{
	public:
		Actor(World* owningWorld, const std::string& texturePath = "");
		virtual ~Actor();

		void BeginPlayInternal();
		virtual void BeginPlay();
		void TickInternal(float deltaTime);
		virtual void Tick(float deltaTime); 
		void SetTexture(const std::string& texturePath);
		void Render(sf::RenderWindow& window);

		void SetActorLocation(const sf::Vector2f& newLocation);
		void SetActorRotation(const float newRotation);

		sf::Vector2f GetActorLocation() const;
		float GetActorRotation() const;
		sf::Vector2f GetActorForwardDirection() const;
		sf::Vector2f GetActorForwardRight() const;


		void AddActorLocationOffset(const sf::Vector2f& offsetAmount);
		void AddActorRotationOffset(const float offsetAmount);

	private:
		void CenterPivot();																									// called in SetTexture();
		World* _owningWorld;
		bool _hasBeganPlay;

		sf::Sprite _sprite;
		shared_ptr<sf::Texture> _texture;

	};
}
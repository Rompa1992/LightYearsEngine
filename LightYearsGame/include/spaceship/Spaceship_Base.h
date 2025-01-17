#pragma once

#include <framework/Actor.h>

namespace ly
{
	class Spaceship_Base : public Actor
	{
	public:
		Spaceship_Base(World* owningWorld, const std::string& texturePath = "");

		virtual void Tick(float deltaTime) override;
		
		void SetVelocity(const sf::Vector2f& newVelocity);

		sf::Vector2f GetVelocity() const { return _velocity; }

	private:
		sf::Vector2f _velocity;
	};

}
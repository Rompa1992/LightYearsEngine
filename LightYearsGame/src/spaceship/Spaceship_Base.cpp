#include "spaceship/Spaceship_Base.h"

namespace ly
{
	Spaceship_Base::Spaceship_Base(World* owningWorld, const std::string& texturePath)
		: Actor{owningWorld, texturePath},
		_velocity{}
	{
	}
	void Spaceship_Base::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorLocationOffset(GetVelocity() * deltaTime);
	}

	void Spaceship_Base::Shoot()
	{
	}

	void Spaceship_Base::SetVelocity(const sf::Vector2f& newVelocity)
	{
		_velocity = newVelocity;
	}
}



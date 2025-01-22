#include "spaceship/Spaceship_Base.h"

#include <functional>

namespace ly
{
	Spaceship_Base::Spaceship_Base(World* owningWorld, const std::string& texturePath)
		: Actor{owningWorld, texturePath},
		_velocity{},
		_healthComponent{100.f, 100.f}
	{
	}
	void Spaceship_Base::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorLocationOffset(GetVelocity() * deltaTime);
	}

	void Spaceship_Base::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);

		std::function<void(float)> func = [](float var)																		// CodeExplanations->Lambda Functions in C++
			{
				LOG("the value of var is %f", var);
			};
	}

	void Spaceship_Base::Shoot()
	{
	}

	void Spaceship_Base::SetVelocity(const sf::Vector2f& newVelocity)
	{
		_velocity = newVelocity;
	}
}



#pragma once
#include "spaceship/Spaceship_Base.h"

namespace ly
{
	class Enemy_Base : public Spaceship_Base
	{
	public:
		Enemy_Base(World* owningWorld, const std::string& texturePath, float collisionDamage = 200.f);

		virtual void Tick(float deltaTime) override;
		virtual void BeginPlay() override;

	private:
		virtual void OnBeginActorOverlap(Actor* other) override;

		float _collisionDamage;

	};
}

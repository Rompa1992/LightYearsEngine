#include "enemy/Enemy_Base.h"

namespace ly
{


	/// Public Functions
	/// -----------------
	Enemy_Base::Enemy_Base(World* owningWorld, const std::string& texturePath, float collisionDamage)
		: Spaceship_Base{owningWorld, texturePath}, 
		_collisionDamage{ collisionDamage }
	{
		SetTeamID(2);
		SetActorRotation(180.f);
	}


	/// Void


	/// Override
	void Enemy_Base::Tick(float deltaTime)
	{
		Spaceship_Base::Tick(deltaTime);
		if (IsActorOutOfWindowBounds(GetActorGlobalBounds().width))
			Destroy();
	}

	void Enemy_Base::BeginPlay()
	{
		Spaceship_Base::BeginPlay();
	}


	/// Setters


	/// Getters


	/// Private Functions
	/// -----------------

	/// Override
	void Enemy_Base::OnBeginActorOverlap(Actor* other)
	{
		Spaceship_Base::OnBeginActorOverlap(other);

		if (IsOtherTeamHostile(other))
			other->ApplyDamage(_collisionDamage);
	}
}

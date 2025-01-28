#include "enemy/Enemy_TwinBlade.h"

#include "weapon/BulletShooter.h"

namespace ly
{


	/// Public Functions
	/// -----------------
	Enemy_TwinBlade::Enemy_TwinBlade(World* owningWorld, const std::string& texturePath, const sf::Vector2f& velocity)
		: Enemy_Base{ owningWorld, texturePath },
		_shooterLeft{ new BulletShooter{ this, 1.f, { 50.f, -20.f } } },
		_shooterRight{ new BulletShooter{ this, 1.f, { 50.f, 20.f } } }
	{
		SetVelocity(velocity);
	}


	/// Void


	/// Override
	void Enemy_TwinBlade::Tick(float deltaTime)
	{
		Enemy_Base::Tick(deltaTime);
		Shoot();
	}

	/// Private Functions
	/// -----------------

	/// Override
	void Enemy_TwinBlade::Shoot()
	{
		_shooterLeft->Shoot();
		_shooterRight->Shoot();
	}
}

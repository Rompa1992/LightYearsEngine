#include "enemy/Enemy_Vanguard.h"
#include "weapon/BulletShooter.h"

namespace ly
{


	/// Public Functions
	/// -----------------
	Enemy_Vanguard::Enemy_Vanguard(World* owningWorld, const std::string& texturePath, const sf::Vector2f& velocity)
		: Enemy_Base{owningWorld, texturePath},
		_shooter{ new BulletShooter{ this, 1.f, {50.f, 0.f }} }
	{
		SetVelocity(velocity);
	}

	/// Override
	void Enemy_Vanguard::Tick(float deltaTime)
	{
		Enemy_Base::Tick(deltaTime);
		Shoot();
	}

	/// Private Functions
	/// -----------------

	/// Override
	void Enemy_Vanguard::Shoot()
	{
		_shooter->Shoot();
	}
}

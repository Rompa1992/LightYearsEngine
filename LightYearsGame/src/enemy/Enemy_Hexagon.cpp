#include "enemy/Enemy_Hexagon.h"

#include "weapon/BulletShooter.h"

namespace ly
{
	/// Public Members
	/// --------------
	Enemy_Hexagon::Enemy_Hexagon(World* owningWorld, const std::string& texturePath, const sf::Vector2f& velocity)
		: Enemy_Base{ owningWorld, texturePath },
		_shooter1{ new BulletShooter{ this, 1.f, sf::Vector2f{ 20.f, 50.f }, 30.f } },
		_shooter2{ new BulletShooter{ this, 1.f, sf::Vector2f{ 20.f, -50.f }, -30.f } },
		_shooter3{ new BulletShooter{ this, 1.f, sf::Vector2f{ 50.f, 0.f }} },
		_shooter4{ new BulletShooter{ this, 1.f, sf::Vector2f{ -50.f, 0.f }, 180.f} },
		_shooter5{ new BulletShooter{ this, 1.f, sf::Vector2f{ -20.f, 50.f }, 120.f } },
		_shooter6{ new BulletShooter{ this, 1.f, sf::Vector2f{ -20.f, -50.f }, -120.f } }
	{
		SetVelocity(velocity);
	}


	/// Void


	/// Override
	void Enemy_Hexagon::Tick(float deltaTime)
	{
		Enemy_Base::Tick(deltaTime);
		Shoot();
	}

	/// Private Functions
	/// -----------------

	/// Override
	void Enemy_Hexagon::Shoot()
	{
		_shooter1->Shoot();
		_shooter2->Shoot();

		_shooter3->Shoot();
		_shooter4->Shoot();

		_shooter5->Shoot();
		_shooter6->Shoot();
	}

}

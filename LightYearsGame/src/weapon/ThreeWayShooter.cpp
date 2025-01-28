#include "weapon/ThreeWayShooter.h"

namespace ly
{
	/// Public Members
	/// --------------
	ThreeWayShooter::ThreeWayShooter(Actor* owner, float coolDownTime, const sf::Vector2f& localOffset)
		: Shooter{owner},
		_shooterLeft{owner, coolDownTime, localOffset + sf::Vector2f{10, -10}, -30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
		_shooterMiddle{ owner, coolDownTime, localOffset, 0.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png" },
		_shooterRight{ owner, coolDownTime, localOffset + sf::Vector2f{10, 10}, 30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png" }
	{
	}

	void ThreeWayShooter::ShootImplementation()
	{
		_shooterLeft.Shoot();
		_shooterMiddle.Shoot();
		_shooterRight.Shoot();
	}

}

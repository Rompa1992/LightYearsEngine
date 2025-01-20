#include "weapon/Shooter.h"

namespace ly
{
	Shooter::Shooter(Actor* owner)
		: _owner{owner}
	{

	}

	void Shooter::Shoot()
	{
		if (CanShoot() && !IsOnCoolDown())
			ShootImplementation();
	}
}
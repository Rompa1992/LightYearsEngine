#include "weapon/BulletShooter.h"
#include "weapon/Bullet.h"
#include <framework/Core.h>
#include <framework/World.h>

namespace ly
{
	
	BulletShooter::BulletShooter(Actor* owner, float cooldownTime)
		: Shooter{owner},
		_cooldownCLock{},
		_cooldownTime{cooldownTime}

	{
	}

	bool BulletShooter::IsOnCoolDown() const
	{
		if (_cooldownCLock.getElapsedTime().asSeconds() > _cooldownTime)
			return false;
		else
			return true;
	}

	void BulletShooter::ShootImplementation()
	{
		_cooldownCLock.restart();
		weak_ptr<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
		newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation());
		newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation());
	}

}


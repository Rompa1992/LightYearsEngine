#include "weapon/BulletShooter.h"
#include "weapon/Bullet.h"
#include <framework/Core.h>
#include <framework/World.h>

namespace ly
{
	
	BulletShooter::BulletShooter(Actor* owner, float cooldownTime, const sf::Vector2f& localPositionOffset, 
							     const float localRotationOffset, const std::string& bulletTexturePath)
		: Shooter{owner},
		_cooldownCLock{},
		_cooldownTime{cooldownTime},
		_localPositionOffset{ localPositionOffset },
		_localRotationOffset{ localRotationOffset },
		_bulletTexturePath{ bulletTexturePath }
	{
	}

	bool BulletShooter::IsOnCoolDown() const
	{
		if (_cooldownCLock.getElapsedTime().asSeconds() > _cooldownTime)
			return false;
		else
			return true;
	}

	void BulletShooter::SetShootCoolDown(float newCoolDownTime)
	{
		_cooldownTime = newCoolDownTime;
	}

	void BulletShooter::SetBulletTexturePath(const std::string& bulletTexturePath)
	{
		_bulletTexturePath = bulletTexturePath;
	}

	void BulletShooter::ShootImplementation()
	{
		sf::Vector2f ownerForawrdDir = GetOwner()->GetActorForwardDirection();
		sf::Vector2f ownerRightDir = GetOwner()->GetActorRightDirection();

		_cooldownCLock.restart();
		weak_ptr<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), _bulletTexturePath);
		newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation() + ownerForawrdDir * _localPositionOffset.x + ownerRightDir * _localPositionOffset.y);
		newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation() + _localRotationOffset);
	}
}


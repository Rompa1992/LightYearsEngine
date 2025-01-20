#pragma once 

#include <SFML/System.hpp>
#include "weapon/Shooter.h"

namespace ly
{
	class BulletShooter : public Shooter
	{
	public:
		BulletShooter(Actor* owner, float cooldownTime = 0.25f);

		virtual bool IsOnCoolDown() const override;

	private:
		virtual void ShootImplementation() override;
		sf::Clock _cooldownCLock;
		float _cooldownTime;

	};
}
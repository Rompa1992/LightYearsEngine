#pragma once

#include "SFML/Graphics.hpp"
#include "weapon/BulletShooter.h"

namespace ly
{
	class ThreeWayShooter : public Shooter
	{
	public:
		ThreeWayShooter(Actor* owner, float coolDownTime = 0.3, const sf::Vector2f& localOffset = { 0.f, 0.f });

		BulletShooter _shooterLeft;
		BulletShooter _shooterMiddle;
		BulletShooter _shooterRight;

	private:
		virtual void ShootImplementation();
	};
}

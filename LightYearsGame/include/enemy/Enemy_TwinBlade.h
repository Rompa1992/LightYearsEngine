#pragma once

#include "enemy/Enemy_Base.h"

namespace ly
{
	class BulletShooter;
	class Enemy_TwinBlade : public Enemy_Base
	{
	public:
		Enemy_TwinBlade(World* owningWorld, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlack1.png", const sf::Vector2f& velocity = { 0.f, 125.f });

		virtual void Tick(float deltaTime) override;

		virtual void Shoot() override;
	private:

		unique_ptr<BulletShooter> _shooterLeft;
		unique_ptr<BulletShooter> _shooterRight;
	};
}

#pragma once

#include "enemy/Enemy_Base.h"

namespace ly
{
	class BulletShooter;
	class Enemy_Hexagon : public Enemy_Base
	{
	public:
		Enemy_Hexagon(World* owningWorld, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyGreen4.png", const sf::Vector2f& velocity = { 0.f, 100.f });

		virtual void Tick(float deltaTime) override;

		virtual void Shoot() override;
	private:

		unique_ptr<BulletShooter> _shooter1;
		unique_ptr<BulletShooter> _shooter2;

		unique_ptr<BulletShooter> _shooter3;
		unique_ptr<BulletShooter> _shooter4;

		unique_ptr<BulletShooter> _shooter5;
		unique_ptr<BulletShooter> _shooter6;
	};
}

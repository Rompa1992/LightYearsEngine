#pragma once
#include "enemy/Enemy_Base.h"

namespace ly
{
	class BulletShooter;
	class Enemy_Vanguard : public Enemy_Base
	{
	public:
		Enemy_Vanguard(World* owningWorld, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyRed3.png", const sf::Vector2f& velocity = { 0.f, 100.f });

		virtual void Tick(float deltaTime) override;

	private:
		virtual void Shoot() override;

		unique_ptr<BulletShooter> _shooter;
	};
}

#pragma once 

#include <SFML/System.hpp>
#include "weapon/Shooter.h"

namespace ly
{
	class BulletShooter : public Shooter
	{
	public:
		BulletShooter(Actor* owner, float cooldownTime = 0.25f, const sf::Vector2f& localPositionOffset = { 0.f, 0.f }, 
					  const float localRotationOffset = { 0.f }, const std::string& bulletTexturePath = "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");

		virtual bool IsOnCoolDown() const override;

		void SetShootCoolDown(float newCoolDownTime);

		void SetBulletTexturePath(const std::string& bulletTexturePath);

	private:
		virtual void ShootImplementation() override;
		sf::Clock _cooldownCLock;
		float _cooldownTime;

		const sf::Vector2f _localPositionOffset;
		const float _localRotationOffset;
		std::string _bulletTexturePath;

	};
}
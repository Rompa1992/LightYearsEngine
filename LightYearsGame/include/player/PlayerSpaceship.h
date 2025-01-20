#pragma once
#include "spaceship/Spaceship_Base.h"

namespace ly
{
	class BulletShooter;
	class PlayerSpaceship : public Spaceship_Base
	{
	public:
		PlayerSpaceship(World* owningWorld, const std::string& texturePath = "SpaceShooterRedux/PNG/playerShip1_blue.png");

		virtual void Tick(float deltaTime) override;
		virtual void Shoot();

		void SetSpeed(float newSpeed) { _speed = newSpeed; }

		float GetSpeed() const { return _speed; }
	private:
		void HandleInput();
		void NormalizeInput();
		void ClampInputEdge();
		void ConsumeInput(float deltaTime);
		sf::Vector2f _moveInput;
		float _speed;

		unique_ptr<BulletShooter> _shooter;
	};
}
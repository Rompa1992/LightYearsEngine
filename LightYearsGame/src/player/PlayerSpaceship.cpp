#include "player/PlayerSpaceship.h"
#include "weapon/BulletShooter.h"

#include <SFML/System.hpp>
#include <framework/MathUtility.h>

namespace ly
{
	PlayerSpaceship::PlayerSpaceship(World* owningWorld, const std::string& texturePath)
		: Spaceship_Base{ owningWorld, texturePath },
		_moveInput{},
		_speed{ 500 },
		_shooter{ new BulletShooter{this, 0.15f} }
	{
		SetTeamID(1);
	}

	void PlayerSpaceship::Tick(float deltaTime)
	{
		Spaceship_Base::Tick(deltaTime);
		HandleInput();
		ConsumeInput(deltaTime);
	}

	void PlayerSpaceship::Shoot()
	{
		if (_shooter)
		{
			_shooter->Shoot();
		}
	}

	// Private Functions ----------------------
	// ----------------------------------------
	void PlayerSpaceship::HandleInput()
	{
		// movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			_moveInput.y = -1.f;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			_moveInput.y = 1.f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			_moveInput.x = 1.f;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			_moveInput.x = -1.f;

		ClampInputEdge();
		NormalizeInput();

		// shoot
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
			Shoot();
	}

	void PlayerSpaceship::NormalizeInput()
	{
		NormalizeVector(_moveInput);
		//LOG("move input: %f, %f", _moveInput.x, _moveInput.y);
	}

	void PlayerSpaceship::ClampInputEdge()
	{
		sf::Vector2f actorLocation = GetActorLocation();

		if (actorLocation.x < 0 && _moveInput.x == -1)
			_moveInput.x = 0.f;

		if (actorLocation.x > GetWindowSize().x && _moveInput.x == 1)
			_moveInput.x = 0.f;

		if (actorLocation.y < 0 && _moveInput.y == -1)
			_moveInput.y = 0.f;

		if (actorLocation.y > GetWindowSize().y && _moveInput.y == 1)
			_moveInput.y = 0.f;
	}

	void PlayerSpaceship::ConsumeInput(float deltaTime)
	{
		SetVelocity(_moveInput * _speed);
			_moveInput.x = _moveInput.y = 0.f;
	}
}


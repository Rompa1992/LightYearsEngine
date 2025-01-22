#include "spaceship/Spaceship_Base.h"
#include <framework/MathUtility.h>
#include "VFX/Explosion.h"

namespace ly
{
	Spaceship_Base::Spaceship_Base(World* owningWorld, const std::string& texturePath)
		: Actor{ owningWorld, texturePath },
		_velocity{},
		_healthComponent{ 100.f, 100.f },
		_blinkTime{ 0.f },
		_blinkDuration{ 0.1f },
		_blinkColorOffset{ 255, 0, 0, 255 }
	{
	}

	/// override
	void Spaceship_Base::ApplyDamage(float amount)
	{
		_healthComponent.ChangeHealth(-amount);
	}

	/// virtual
	void Spaceship_Base::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorLocationOffset(GetVelocity() * deltaTime);
		UpdateBlink(deltaTime);
	}

	void Spaceship_Base::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);

		_healthComponent.onHealthChanged.BindAction(GetWeakRef(), &Spaceship_Base::OnHealthChanged);					// without parentheses we are refrencing the function (pointing to it) and not calling it. 
		_healthComponent.onTakenDamage.BindAction(GetWeakRef(), &Spaceship_Base::OnDamageTaken);
		_healthComponent.onHealthEmpty.BindAction(GetWeakRef(), &Spaceship_Base::OnDeath);
		_healthComponent.onHealthRegen.BindAction(GetWeakRef(), &Spaceship_Base::OnHealthRegen);
	}

	void Spaceship_Base::Shoot()
	{

	}

	/// setters
	void Spaceship_Base::SetVelocity(const sf::Vector2f& newVelocity)
	{
		_velocity = newVelocity;
	}

	/// Private
	/// -------
	void Spaceship_Base::OnHealthChanged(float amount, float currentHealth, float maxHealth)
	{
		LOG("health changed by: %f, and is now: %f/%f", amount, currentHealth, maxHealth);
	}

	void Spaceship_Base::OnDamageTaken(float amount, float currentHealth, float maxHealth)
	{
		Blink();
	}

	void Spaceship_Base::OnDeath()
	{
		Explosion* explosion = new Explosion();
		explosion->SpawnExplosion(GetWorld(), GetActorLocation());
		Destroy();
		delete explosion;
	}

	void Spaceship_Base::OnHealthRegen(float amount, float currentHealth, float maxHealth)
	{

	}

	void Spaceship_Base::Blink()
	{
		if (_blinkTime == 0.f)
			_blinkTime = _blinkDuration;
	}

	void Spaceship_Base::UpdateBlink(float deltaTime)
	{
		if (_blinkTime > 0)
		{
			_blinkTime -= deltaTime;
			_blinkTime = _blinkTime > 0 ? _blinkTime : 0.f;

			GetSprite().setColor(LerpColor(sf::Color::White, _blinkColorOffset, _blinkTime));
		}
	}
}



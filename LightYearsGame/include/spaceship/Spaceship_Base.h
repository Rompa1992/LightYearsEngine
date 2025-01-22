#pragma once

#include <actorComponents/HealthComponent.h>
#include <framework/Actor.h>

namespace ly
{
	class Spaceship_Base : public Actor
	{
	public:
		Spaceship_Base(World* owningWorld, const std::string& texturePath = "");

		virtual void ApplyDamage(float amount) override;

		virtual void Tick(float deltaTime) override;
		virtual void BeginPlay() override;
		virtual void Shoot();
		
		void SetVelocity(const sf::Vector2f& newVelocity);

		sf::Vector2f GetVelocity() const { return _velocity; }

	private:
		virtual void OnHealthChanged(float amount, float currentHealth, float maxHealth);											// CodeExamples->Understanding the Delegate System in `ly` Namespace
		virtual void OnDamageTaken(float amount, float currentHealth, float maxHealth);
		void OnDeath();
		virtual void OnHealthRegen(float amount, float currentHealth, float maxHealth);

		sf::Vector2f _velocity;
		HealthComponent _healthComponent;

		/// effects
		void Blink();
		void UpdateBlink(float deltaTime);
		float _blinkTime;
		float _blinkDuration;
		sf::Color _blinkColorOffset;
	};

}
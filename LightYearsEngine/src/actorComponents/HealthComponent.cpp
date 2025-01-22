#include "actorComponents/HealthComponent.h"
#include "framework/Core.h"

namespace ly
{
    HealthComponent::HealthComponent(float maxHealth, float currentHealth)
        : _maxHealth{ maxHealth },
        _currentHealth{currentHealth}
    {
    }

    void HealthComponent::ChangeHealth(float amount)
    {
        
        if (amount == 0) return;
        if (_currentHealth == 0) return;

        _currentHealth += amount;

        if (_currentHealth < 0)
            _currentHealth = 0;

        if (_currentHealth > _maxHealth)
            _currentHealth = _maxHealth;

        if (amount < 0)
        {
            OnDamageTaken(-amount);

            if (_currentHealth <= 0)
                OnHealthEmpty();
        }
        else
            OnHealthRegen(amount);

        onHealthChanged.BroadCast(amount, _currentHealth, _maxHealth);
    }

    void HealthComponent::OnDamageTaken(float amount)
    {
        onTakenDamage.BroadCast(amount, _currentHealth, _maxHealth);
    }

    void HealthComponent::OnHealthEmpty()
    {
        onHealthEmpty.BroadCast();
    }

    void HealthComponent::OnHealthRegen(float amount)
    {
        onHealthRegen.BroadCast(amount, _currentHealth, _maxHealth);
    }
}


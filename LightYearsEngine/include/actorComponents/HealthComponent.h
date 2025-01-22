#pragma once

#include "framework/Delegate.h"

namespace ly
{
    class HealthComponent
    {
    public:
        HealthComponent(float maxHealth, float currentHealth);

        void ChangeHealth(float amount);

        float GetCurrentHealth() const { return _currentHealth; }
        float GetMaxHealth() const { return _maxHealth; }

        Delegate<float, float, float> onHealthChanged;
        Delegate<float, float, float> onTakenDamage;
        Delegate<> onHealthEmpty;
        Delegate<float, float, float> onHealthRegen;

    private:
        void OnDamageTaken(float amount);
        void OnHealthEmpty();
        void OnHealthRegen(float amount);

        float _currentHealth;
        float _maxHealth;
    };
}

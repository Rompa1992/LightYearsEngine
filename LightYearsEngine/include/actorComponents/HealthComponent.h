#pragma once

namespace ly
{
    class HealthComponent
    {
    public:
        HealthComponent(float maxHealth, float currentHealth);

        void UpdateHealth(float amount);

        float GetCurrentHealth() const { return _currentHealth; }
        float GetMaxHealth() const { return _maxHealth; }

    private:
        void OnDamageTaken(float amount);
        void OnHealthEmpty();
        void OnHealthRegen(float amount);

        float _currentHealth;
        float _maxHealth;
    };
}

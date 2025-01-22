#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Actor.h"

namespace ly
{
    class Particle : public Actor
    {
    public:
        Particle(World* owningWorld, const std::string& texturePath);

        void RandomVelocity(float minSpeed, float maxSpeed);
        void RandomSize(float min, float max);
        void RandomLifeTime(float min, float max);
        
        virtual void BeginPlay() override;
        virtual void Tick(float deltaTime) override;

    private:
        void Move(float deltaTime);
        void Fade(float deltaTIme);

        sf::Vector2f _velocity;
        float _lifeTime;
        sf::Clock _timer;

    };
}

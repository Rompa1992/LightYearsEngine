#include "VFX/Particle.h"
#include "framework/MathUtility.h"

namespace ly
{
    Particle::Particle(World* owningWorld, const std::string& texturePath)
        : Actor{owningWorld, texturePath},
        _velocity{},
        _lifeTime{ 1.f },
        _timer{}
    {
    }

    /// Void
    void Particle::RandomVelocity(float minSpeed, float maxSpeed)
    {
        _velocity = RandomUnitVector() * RandomRange(minSpeed, maxSpeed);
    }

    void Particle::RandomSize(float min, float max)
    {
        float randomScale = RandomRange(min, max);

        GetSprite().setScale(randomScale, randomScale);
    }

    void Particle::RandomLifeTime(float min, float max)
    {
        _lifeTime = RandomRange(min, max);
    }

    /// Override
    void Particle::BeginPlay()
    {
        Actor::BeginPlay();
        SetEnablePhysics(false);
    }

    void Particle::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);

        Move(deltaTime);
        Fade(deltaTime);

        if (_timer.getElapsedTime().asSeconds() >= _lifeTime)
            Destroy();
    }

    /// Private
    /// -------
    void Particle::Move(float deltaTime)
    {
        AddActorLocationOffset(_velocity * deltaTime);
    }

    void Particle::Fade(float deltaTIme)
    {
        float elapsedTime = _timer.getElapsedTime().asSeconds();

        GetSprite().setColor(LerpColor(GetSprite().getColor(), sf::Color(255, 255, 255, 0), elapsedTime/_lifeTime));
        GetSprite().setScale(LerpVectorFloat(GetSprite().getScale(), sf::Vector2f{ 0.f, 0.f }, elapsedTime / _lifeTime));
    }
    
}


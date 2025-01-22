#include "VFX/Explosion.h"
#include <framework/MathUtility.h>
#include <framework/World.h>
#include <VFX/Particle.h>

namespace ly
{
	/// Public Functions
	/// -----------------
	Explosion::Explosion(int particleAmount, float lifeTimeMin, float lifeTimeMax, float sizeMin, float sizeMax, float speedMin, float speedMax, const sf::Color& particleColor, const List<std::string>& particleImagePaths)
		: _particleAmount{ particleAmount }, 
		_lifeTimeMin{ lifeTimeMin }, 
		_lifeTimeMax{ lifeTimeMax }, 
		_sizeMin{ sizeMin }, 
		_sizeMax{ sizeMax }, 
		_speedMin{ speedMin }, 
		_speedMax{ speedMax }, 
		_particleColor { particleColor },
		_particleImagePaths{ particleImagePaths }
	{
	}

	/// Void
	void Explosion::SpawnExplosion(World* world, const sf::Vector2f& actorLocation)
	{
		if (!world) return;

		for (int i = 0; i < _particleAmount; i++)
		{
			std::string particleImagePath = _particleImagePaths[(int)RandomRange(0, _particleImagePaths.size())];
			weak_ptr<Particle> newParticle = world->SpawnActor<Particle>(particleImagePath);

			newParticle.lock()->RandomLifeTime(_lifeTimeMin, _lifeTimeMax);
			newParticle.lock()->SetActorLocation(actorLocation);
			newParticle.lock()->RandomSize(_sizeMin, _sizeMax);
			newParticle.lock()->RandomVelocity(_speedMin, _speedMax);
			newParticle.lock()->GetSprite().setColor(_particleColor);
		}
	}

	/// Override


	/// Setters


	/// Getters


	/// Private Functions
	/// -----------------


}

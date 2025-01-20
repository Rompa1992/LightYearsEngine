#include "weapon/Bullet.h"

namespace ly
{
	Bullet::Bullet(World* world, Actor* owner, const std::string& texturePath, float speed, float damage)
		: Actor{world, texturePath},
		_owner{owner},
		_speed{speed},
		_damage{damage}
	{
	}

	void Bullet::SetSpeed(float newSpeed)
	{
		_speed = newSpeed;
	}

	void Bullet::SetDamage(float newDamage)
	{
		_damage = newDamage;
	}

	void Bullet::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		Move(deltaTime);

		if (IsActorOutOfWindowBounds())
			Destroy();

	}

	void Bullet::Move(float deltaTime)
	{
		AddActorLocationOffset(GetActorForwardDirection() * _speed * deltaTime);
	}
}
#pragma once

#include <framework/Actor.h>

namespace ly
{
	class Bullet : public Actor
	{
	public:
		Bullet(World* world, Actor* owner, const std::string& texturePath, float speed = 800.f, float damage = 10.f);

		virtual void Tick(float deltaTime) override;
		virtual void BeginPlay() override;

		void SetSpeed(float newSpeed);
		void SetDamage(float newDamage);


	private:
		void Move(float deltaTime);

		Actor* _owner;
		float _speed;
		float _damage;
	};
}
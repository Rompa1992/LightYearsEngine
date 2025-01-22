#pragma once 

#include <box2d/b2_world.h>
#include "framework/Core.h"

namespace ly
{
	class Actor;

	class PhysicsContactListener : public b2ContactListener
	{
		virtual void BeginContact(b2Contact* contact) override;
		virtual void EndContact(b2Contact* contact) override;
	};

	class PhysicsSystem
	{
	public:
		static PhysicsSystem& Get();																					// Called in application after world tick. Before clean cycle.	

		void Step(float deltaTime);

		b2Body* AddListener(Actor* listener);
		void RemoveListener(b2Body* bodyToRemove);

		static void CleanUp();

		float GetPhysicsScale() const { return _physicsScale; }
	protected:
		PhysicsSystem();

	private:
		void ProcessPendingRemoveListeners();

		static unique_ptr<PhysicsSystem> _physicsSystem;
		b2World _physicsWorld;
		float _physicsScale;
		int _velocityIterations;
		int _positionIterations;

		PhysicsContactListener _contactListener;
		Set<b2Body*> _pendingRemovalListeners;
	};
}
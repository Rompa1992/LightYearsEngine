#pragma once 

namespace ly
{
	class Actor;																										// CodeExplanations->When to Forward Declare vs Include
	class Shooter
	{
	public:
		void Shoot();

		virtual bool CanShoot() const { return true; }
		virtual bool IsOnCoolDown() const { return false; }

		Actor* GetOwner() const { return _owner; }																
	protected:
		Shooter(Actor* owner);

	private:
		virtual void ShootImplementation() = 0;																			// abstract class, cannot have instance of this class.
		
		Actor* _owner;
	};
}
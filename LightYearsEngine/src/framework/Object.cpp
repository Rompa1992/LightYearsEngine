#include "framework/Object.h"
#include "framework/Core.h"

namespace ly
{
	Object::Object()
		: _isPendingDestroy{false}
	{

	}

	Object::~Object()
	{
		LOG("Object was destroyed");
	}

	void Object::Destroy()
	{
		onDestroy.BroadCast(this);																								// TODO: implement 
		_isPendingDestroy = true;
	}

	weak_ptr<Object> Object::GetWeakRef() 
	{
		return weak_from_this();
	}

	weak_ptr<const Object> Object::GetWeakRef() const
	{
		return weak_from_this();
	}

}

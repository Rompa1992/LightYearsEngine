#include "framework/TimerManager.h"

namespace ly
{
	/// ------------------
	/// struct TimerHandle
	/// ------------------

	unsigned int TimerHandle::_timerKeyCounter = 0;
	
	/// Public Functions
	/// ----------------
	TimerHandle::TimerHandle()
		: _timerKey{ GetNextTimerKey() }
	{

	}

	/// ------------
	/// Struct Timer 
	/// ------------

	/// Public Functions
	/// ----------------
	Timer::Timer(weak_ptr<Object> weakRef, std::function<void()> callback, float duration, bool repeat)
		: _listener{ weakRef, callback },
		_duration{ duration },
		_repeat{ repeat },
		_timerCounter{ 0.f },
		_isExpired{ false }
	{
	}

	/// void
	void Timer::TickTIme(float deltaTime)
	{
		if (Expired()) return;

		_timerCounter += deltaTime;
		
		if (_timerCounter >= _duration)
		{
			_listener.second();

			if (_repeat)
				_timerCounter = 0.f;
			else
				SetExired();
		}
	}

	void Timer::SetExired()
	{
		_isExpired = true;
	}

	/// bool
	bool Timer::Expired() const
	{
		return _isExpired || _listener.first.expired() || _listener.first.lock()->IsPendingDestroy();
	}

	/// Private Functions
	/// -----------------


	/// ------------
	/// Class Timer 
	/// ------------
	
	unique_ptr<TimerManager> TimerManager::_timerManager{ nullptr };

	/// Public Functions
	/// -----------------

	/// void
	void TimerManager::UpdateTimer(float deltaTime)
	{
		for (auto iter = _timers.begin(); iter != _timers.end();)
		{
			if (iter->second.Expired())
			{
				iter = _timers.erase(iter);
			}
			else
			{
				iter->second.TickTIme(deltaTime);
				++iter;
			}
		}
	}

	void TimerManager::ClearTimer(TimerHandle timerHandle)
	{
		auto iter = _timers.find(timerHandle);

		if (iter != _timers.end())
			iter->second.SetExired();
	}

	/// Setters

	/// Getters
	TimerManager& TimerManager::Get()
	{
		if (!_timerManager)
			_timerManager = std::move(unique_ptr<TimerManager>(new TimerManager{}));

		return *_timerManager;
	}

	/// Protected Functions
	/// -------------------
	TimerManager::TimerManager()
	{
	}


	/// Private Functions
	/// -----------------

}

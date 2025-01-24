#pragma once
#include <functional>

#include "framework/Core.h"
#include "framework/Object.h"

namespace ly
{
	struct TimerHandle
	{
	public:
		TimerHandle();

		unsigned int GetTimerKey() const { return _timerKey; }

	private:
		unsigned int _timerKey;
		static unsigned int _timerKeyCounter;
		static unsigned int GetNextTimerKey() { return ++_timerKeyCounter; }
	};

	struct TimerHandleHashFunction
	{
	public:
		std::size_t operator()(const TimerHandle& timerHandle) const
		{
			return timerHandle.GetTimerKey();
		}
	};

	bool operator==(const TimerHandle& lhs, const TimerHandle& rhs);														// used to compare the hash function 

	struct Timer
	{
	public:
		Timer(weak_ptr<Object> weakRef, std::function<void()> callback, float duration, bool repeat);

		void TickTIme(float deltaTime);
		void SetExired();

		bool Expired() const;																								// Expired means when the timer is reached or when the weak_ptr is destroyed. 

	private:
		std::pair<weak_ptr<Object>, std::function<void()>> _listener;
		float _timerCounter;
		float _duration;
		bool _repeat;
		bool _isExpired;
	};

	class TimerManager
	{
	public:
		void UpdateTimer(float deltaTime);
		void ClearTimer(TimerHandle timerHandle);
		
		static TimerManager& Get();

		template<typename ClassName>
		TimerHandle SetTimer(weak_ptr<Object> weakRef, void(ClassName::* callback)(), float duration, bool repeat = false)
		{
			TimerHandle newTimerHandle{};

			_timers.insert({ newTimerHandle, Timer(weakRef, [=] {(static_cast<ClassName*>(weakRef.lock().get())->*callback)(); }, duration, repeat) });
		
			return newTimerHandle;
		}

	protected:
		TimerManager();


	private:
		static unique_ptr<TimerManager> _timerManager;

		Dictionary<TimerHandle, Timer, TimerHandleHashFunction> _timers;

	};
}

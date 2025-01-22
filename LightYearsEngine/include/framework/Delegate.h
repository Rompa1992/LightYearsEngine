#pragma once

#include <functional>
#include "framework/Core.h"

namespace ly
{
    class Object;

    template<typename... Args>                                                                                              // CodeExamples->Understanding the Delegate System in `ly` Namespace
    class Delegate
    {
    public:
        template<typename ClassName>
        void BindAction(weak_ptr<Object> object, void(ClassName::* callback)(Args...))
        {
            std::function<bool(Args...)> callbackFunc = [object, callback](Args... args)->bool
            {
                    if (!object.expired())
                    {
                        (static_cast<ClassName*>(object.lock().get())->*callback)(args...);

                        return true;
                    }

                    return false;
            };

            _callbacks.push_back(callbackFunc);
        }

        void BroadCast(Args... args)
        {
            for (auto iter = _callbacks.begin(); iter != _callbacks.end();)
            {
                if ((*iter)(args...))
                    ++iter;
                else
                    iter = _callbacks.erase(iter);
            }
        }

    private:
        List<std::function<bool(Args...)>> _callbacks;

    };
}

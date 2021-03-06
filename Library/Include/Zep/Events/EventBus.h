//
//  EventBus.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 30/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__EventBus__
#define __Zep__EventBus__

#include <utility>
#include <typeindex>
#include <map>
#include "Zep/Events/EventSignal.h"
#include "Zep/Events/EventSignalCallback.h"
#include "Zep/Events/EventSubscription.h"
#include "Zep/Events/Event.h"

namespace Zep {
    
    class EventBus {
        std::map<std::type_index, EventSignal*> signals;
        EventSignal& getSignal(std::type_index typeIndex);
    public:
        template <class T, typename ... Args>
        void emit(Args && ... args) {
            T event(std::forward<Args>(args) ...);
            auto index = std::type_index(typeid(T));
            auto &signal = getSignal(index);
            signal.emit(static_cast<Event&>(event));
        }
        template <class T>
        void emit(T event) {
            auto index = std::type_index(typeid(T));
            auto &signal = getSignal(index);
            signal.emit(static_cast<Event&>(event));
        }
        template <class T, class R>
        EventSubscription subscribe(R &receiver) {
            auto index = std::type_index(typeid(T));
            auto& signal = getSignal(index);
            void (R::*handle)(const T&) = &R::handle;
            EventSignalCallback<T> callback(std::bind(handle, &receiver, std::placeholders::_1));
            int id = signal.subscribe(callback);
            return EventSubscription(signal, id);
        }
    };
}

#endif

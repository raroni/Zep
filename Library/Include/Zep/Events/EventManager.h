//
//  EventManager.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 30/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__EventManager__
#define __Zep__EventManager__

#include <utility>
#include <typeindex>
#include <map>
#include "Zep/Events/EventSignal.h"
#include "Zep/Events/EventSignalCallback.h"
#include "Zep/Events/Event.h"

namespace Zep {
    
    class EventManager {
        std::map<std::type_index, EventSignal*> signals;
        EventSignal& getSignal(std::type_index typeIndex);
    public:
        template <class T, typename ... Args>
        void emit(Args && ... args) {
            T event(std::forward<Args>(args) ...);
            auto index = std::type_index(typeid(T));
            auto& signal = getSignal(index);
            signal.emit(static_cast<Event&>(event));
        }
        template <class T, class R>
        void subscribe(R &receiver) {
            auto index = std::type_index(typeid(T));
            auto& signal = getSignal(index);
            EventSignalCallback<T> callback(std::bind(&R::receive, &receiver, std::placeholders::_1));
            signal.subscribe(callback);
        }
    };
}

#endif

//
//  EventBus.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 30/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Zep/Events/EventBus.h"

namespace Zep {
    EventSignal& EventBus::getSignal(std::type_index typeIndex) {
        auto iterator = signals.find(typeIndex);
        if(iterator == signals.end()) {
            auto eventSignal = new EventSignal();
            signals[typeIndex] = eventSignal;
            return *eventSignal;
        } else {
            return *(iterator->second);
        }
    }
}

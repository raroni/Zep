//
//  EventSubscription.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 12/02/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Zep/Events/EventSignal.h"
#include "Zep/Events/EventSubscription.h"

namespace Zep {
    EventSubscription::EventSubscription(EventSignal &signal, int id) : signal(signal), id(id) { }
    
    EventSubscription::~EventSubscription() {
        signal.unsubscribe(id);
    }
}

//
//  EntityObserverProcessor.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 31/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Zep/Events/EventManager.h"
#include "Zep/Simulation/Database.h"
#include "Zep/Simulation/EntityIDAddition.h"
#include "Zep/Simulation/EntityObserverProcessor.h"

namespace Zep {
    void EntityObserverProcessor::initialize() {
        eventSubscriptionManager.initialize(*this, *eventManager);
        eventSubscriptionManager.add<EntityIDAddition>();
        componentMask = createComponentMask();
    }
    
    void EntityObserverProcessor::receive(const EntityIDAddition &addition) {
        EntityID id = addition.getID();
        if(database->hasComponents(id, componentMask)) {
            onAdded(id);
        }
    }
}

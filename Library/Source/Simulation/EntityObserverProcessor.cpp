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
#include "Zep/Simulation/EntityIDDestruction.h"
#include "Zep/Simulation/EntityObserverProcessor.h"

namespace Zep {
    void EntityObserverProcessor::initialize() {
        eventSubscriptionManager.initialize(*this, *eventManager);
        eventSubscriptionManager.add<EntityIDAddition>();
        eventSubscriptionManager.add<EntityIDDestruction>();
        componentMask = createComponentMask();
    }
    
    void EntityObserverProcessor::receive(const EntityIDAddition &addition) {
        EntityID id = addition.getID();
        if(database->hasComponents(id, componentMask)) {
            ids.insert(id);
            onAdded(id);
        }
    }
    
    void EntityObserverProcessor::receive(const EntityIDDestruction &destruction) {
        EntityID id = destruction.getID();
        auto iterator = ids.find(id);
        if(iterator != ids.end()) {
            ids.erase(iterator);
            onDestroyed(id);
        }
    }
}

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
#include "Zep/Simulation/EntityChange.h"
#include "Zep/Simulation/EntityObserverProcessor.h"

namespace Zep {
    void EntityObserverProcessor::initialize() {
        eventSubscriptionManager.initialize(*this, *eventManager);
        eventSubscriptionManager.add<EntityIDAddition>();
        eventSubscriptionManager.add<EntityIDDestruction>();
        eventSubscriptionManager.add<EntityChange>();
        onInitialize();
    }
    
    void EntityObserverProcessor::receive(const EntityIDAddition &addition) {
        EntityID id = addition.getID();
        if(match(id)) {
            add(id);
        }
    }
    
    void EntityObserverProcessor::receive(const EntityIDDestruction &destruction) {
        EntityID id = destruction.getID();
        auto iterator = ids.find(id);
        if(iterator != ids.end()) {
            remove(id);
        }
    }
    
    void EntityObserverProcessor::receive(const EntityChange &change) {
        EntityID id = change.getID();
        auto iterator = ids.find(id);
        bool existing = iterator != ids.end();
        
        if(match(id)) {
            if(!existing) add(id);
        } else if(existing) {
            remove(id);
        }
    }
    
    void EntityObserverProcessor::add(EntityID id) {
        ids.insert(id);
        onAdded(id);
    }
    
    void EntityObserverProcessor::remove(EntityID id) {
        ids.erase(id);
        onRemoved(id);
    }
}

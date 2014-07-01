//
//  EntityObserver.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 01/07/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "EntityObserver.h"

namespace Zep {
    EntityObserver::EntityObserver(EventManager &eventManager, EntityObserverDelegate &delegate) : delegate(delegate) {
        eventSubscriptionManager.initialize(*this, eventManager);
    }
    
    void EntityObserver::initialize() {
        eventSubscriptionManager.add<EntityIDAddition>();
        eventSubscriptionManager.add<EntityIDDestruction>();
    }
    
    void EntityObserver::receive(const EntityIDAddition &addition) {
        auto id = addition.getID();
        if(delegate.match(id)) {
            entityIDs.insert(id);
            delegate.handleAddition(id);
        }
    }
    
    void EntityObserver::receive(const EntityIDDestruction &destruction) {
        auto id = destruction.getID();
        auto iterator = entityIDs.find(id);
        if(iterator != entityIDs.end()) {
            delegate.handleRemoval(id);
        }
    }
}

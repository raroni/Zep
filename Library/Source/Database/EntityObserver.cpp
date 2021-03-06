//
//  EntityObserver.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 01/07/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "EntityObserver.h"

namespace Zep {
    EntityObserver::EntityObserver(EventBus &eventBus, EntityObserverDelegate &delegate) :
    delegate(delegate),
    eventSubscriptionManager(EventSubscriptionManager<EntityObserver>(*this, eventBus)) { }
    
    void EntityObserver::initialize() {
        eventSubscriptionManager.add<EntityIDAddition>();
        eventSubscriptionManager.add<EntityIDDestruction>();
        eventSubscriptionManager.add<EntityChange>();
    }
    
    void EntityObserver::handle(const EntityIDAddition &addition) {
        auto id = addition.getID();
        if(delegate.match(id)) {
            add(id);
        }
    }
    
    void EntityObserver::add(EntityID id) {
        ids.insert(id);
        delegate.handleAddition(id);
    }
    
    void EntityObserver::remove(EntityID id) {
        delegate.handleRemoval(id);
        ids.erase(id);
    }
    
    void EntityObserver::handle(const EntityIDDestruction &destruction) {
        auto id = destruction.getID();
        auto iterator = ids.find(id);
        if(iterator != ids.end()) {
            remove(id);
        }
    }
    
    void EntityObserver::handle(const EntityChange &change) {
        EntityID id = change.getID();
        auto iterator = ids.find(id);
        bool existing = iterator != ids.end();
        
        if(delegate.match(id)) {
            if(!existing) add(id);
        } else if(existing) {
            remove(id);
        }
    }
}

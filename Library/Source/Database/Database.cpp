//
//  Database.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 29/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Zep/Events/EventBus.h"
#include "Zep/Database/EntityIDAddition.h"
#include "Zep/Database/EntityChange.h"
#include "Zep/Database/EntityIDDestruction.h"
#include "Zep/Database/DatabaseConfig.h"
#include "Zep/Database/Database.h"

namespace Zep {
    Database::Database(EventBus &eventBus) : eventBus(eventBus), aspectTypes(AspectTypeRegistry(DatabaseConfig::maxAspectTypes)) { }
    
    void Database::initialize() {
        aspects.resize(DatabaseConfig::maxAspectTypes, nullptr);
        initialized = true;
    }
    
    EntityID Database::createEntityID() {
        if(!initialized) throw Exception("You must initialize database before creating entity IDs.");
        
        EntityID id;
        if(freedIDs.empty()) {
            id = nextUnusedID++;
            allocate(id+1);
        } else {
            id = freedIDs.back();
            freedIDs.pop_back();
        }
        newCreations.push_back(id);
        return id;
    }
    
    void Database::destroy(EntityID id) {
        pendingDestructions.push_back(id);
    }
    
    void Database::allocate(int newSize) {
        relationships.resize(newSize);
        for(AspectListInterface *list : aspects) {
            if(list != nullptr) list->resize(newSize);
        }
    }
    
    bool Database::hasAspect(EntityID entityID, AspectTypeID aspectTypeID) {
        return relationships[entityID].test(aspectTypeID);
    }
    
    void Database::update() {
        for(auto &pair : newRelationships) {
            relationships[pair.first] = pair.second;
        }
        
        for(EntityID id : newCreations) {
            eventBus.emit<EntityIDAddition>(id);
            newRelationships.erase(id);
        }
        newCreations.clear();
        
        for(EntityID id : pendingDestructions) {
            eventBus.emit<EntityIDDestruction>(id);
            freedIDs.push_back(id);
            relationships[id].reset();
            newRelationships.erase(id);
        }
        pendingDestructions.clear();
        
        for(auto &pair : newRelationships) {
            eventBus.emit<EntityChange>(pair.first);
        }
        newRelationships.clear();
    }
    
    EventBus& Database::getEventBus() const {
        return eventBus;
    }
    
    AspectMask& Database::getNewRelationshipAspectMask(EntityID entityID) {
        auto iterator = newRelationships.find(entityID);
        if(iterator != newRelationships.end()) {
            return iterator->second;
        } else {
            newRelationships[entityID] = relationships[entityID];
            return newRelationships[entityID];
        }
    }
    
    bool Database::hasAspects(EntityID entityID, AspectMask mask) {
        return (relationships[entityID] & mask) == mask;
    }
}

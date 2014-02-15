//
//  Database.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 29/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include <iostream>

#include "Zep/Events/EventManager.h"
#include "Zep/Simulation/EntityIDAddition.h"
#include "Zep/Simulation/EntityChange.h"
#include "Zep/Simulation/EntityIDDestruction.h"
#include "Zep/Simulation/SimulationConfig.h"
#include "Zep/Simulation/Database.h"

namespace Zep {
    Database::Database(EventManager &eventManager) : eventManager(eventManager), componentTypes(ComponentTypeRegistry(SimulationConfig::maxComponentTypes)) { }
    
    void Database::initialize() {
        components.resize(SimulationConfig::maxComponentTypes, nullptr);
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
        for(ComponentListInterface *list : components) {
            if(list != nullptr) list->resize(newSize);
        }
    }
    
    void Database::update() {
        for(auto &pair : newRelationships) {
            relationships[pair.first] = pair.second;
        }
        
        for(EntityID id : newCreations) {
            eventManager.emit<EntityIDAddition>(id);
            newRelationships.erase(id);
        }
        newCreations.clear();
        
        for(EntityID id : pendingDestructions) {
            eventManager.emit<EntityIDDestruction>(id);
            freedIDs.push_back(id);
            relationships[id].reset();
            newRelationships.erase(id);
        }
        pendingDestructions.clear();
        
        for(auto &pair : newRelationships) {
            eventManager.emit<EntityChange>(pair.first);
        }
        newRelationships.clear();
    }
    
    ComponentMask& Database::getNewRelationshipComponentMask(EntityID entityID) {
        auto iterator = newRelationships.find(entityID);
        if(iterator != newRelationships.end()) {
            return iterator->second;
        } else {
            newRelationships[entityID] = relationships[entityID];
            return newRelationships[entityID];
        }
    }
    
    bool Database::hasComponents(EntityID entityID, ComponentMask mask) {
        return (relationships[entityID] & mask).any();
    }
}

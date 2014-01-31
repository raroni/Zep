//
//  Database.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 29/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Zep/Events/EventManager.h"
#include "Zep/Simulation/EntityIDAddition.h"
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
    
    void Database::allocate(int newSize) {
        relationships.resize(newSize);
        for(ComponentListInterface *list : components) {
            if(list != nullptr) list->resize(newSize);
        }
    }
    
    void Database::update() {
        for(EntityID id : newCreations) {
            eventManager.emit<EntityIDAddition>(id);
        }
        newCreations.clear();
    }
    
    bool Database::hasComponents(EntityID entityID, ComponentMask mask) {
        return (relationships[entityID] & mask).any();
    }
}

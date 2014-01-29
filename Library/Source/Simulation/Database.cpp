//
//  Database.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 29/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Zep/Simulation/Database.h"

namespace Zep {
    Database::Database() {
        components.resize(Component::familyMaxCount, nullptr);
    }
    
    EntityID Database::createEntityID() {
        EntityID id;
        if(freedIDs.empty()) {
            id = nextUnusedID++;
            allocate(id+1);
        } else {
            id = freedIDs.back();
            freedIDs.pop_back();
        }
        return id;
    }
    
    void Database::allocate(int newSize) {
        relationships.resize(newSize);
        for(ComponentListInterface *list : components) {
            if(list != nullptr) list->resize(newSize);
        }
    }
    
    void update() {
        
    }
}

//
//  Database.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 29/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__Database__
#define __Zep__Database__

#include <bitset>
#include <vector>
#include "Zep/Simulation/EntityID.h"
#include "Zep/Simulation/Component.h"
#include "Zep/Simulation/ComponentList.h"
#include "Zep/Simulation/ComponentListInterface.h"

namespace Zep {
    class Database {
        std::vector<EntityID> freedIDs;
        EntityID nextUnusedID = 0;
        std::vector<ComponentListInterface*> components;
        std::vector<std::bitset<Component::familyMaxCount>> relationships;
        void allocate(int newSize);
    public:
        Database();
        EntityID createEntityID();
        template <class T>
        T& createComponent(EntityID entityID) {
            Component::FamilyID familyID = Component::getFamilyID<T>();
            ComponentList<T> *componentList;
            
            if(components[familyID] == nullptr) {
                componentList = new ComponentList<T>();
                componentList->resize(relationships.size());
                components[familyID] = componentList;
            } else {
                componentList = static_cast<ComponentList<T>*>(components[familyID]);
            }
            
            (*componentList)[entityID] = T();
            return (*componentList)[entityID];
        }
        template <class T>
        T& getComponent(EntityID entityID) {
            Component::FamilyID familyID = Component::getFamilyID<T>();
            auto& componentList = static_cast<ComponentList<T>&>(*components[familyID]);
            return componentList[entityID];
        }
        void update();
    };
}

#endif

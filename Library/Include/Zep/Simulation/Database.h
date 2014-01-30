//
//  Database.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 29/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__Database__
#define __Zep__Database__

#include <vector>
#include "Zep/Exception.h"
#include "Zep/Simulation/EntityID.h"
#include "ZEp/Simulation/FamilyID.h"
#include "Zep/Simulation/Component.h"
#include "Zep/Simulation/ComponentMask.h"
#include "Zep/Simulation/ComponentList.h"
#include "Zep/Simulation/ComponentListInterface.h"

namespace Zep {
    class EventManager;
    
    class Database {
        std::vector<EntityID> freedIDs;
        EntityID nextUnusedID = 0;
        std::vector<ComponentListInterface*> components;
        std::vector<ComponentMask> relationships;
        std::vector<EntityID> newCreations;
        void allocate(int newSize);
        EventManager &eventManager;
        bool initialized = false;
    public:
        Database(EventManager &eventManager);
        EntityID createEntityID();
        template <class T>
        T& createComponent(EntityID entityID) {
            if(!initialized) throw Exception("You must initialize database before creating components.");
            
            FamilyID familyID = Component::getFamilyID<T>();
            ComponentList<T> *componentList;
            
            if(components[familyID] == nullptr) {
                componentList = new ComponentList<T>();
                componentList->resize(relationships.size());
                components[familyID] = componentList;
            } else {
                componentList = static_cast<ComponentList<T>*>(components[familyID]);
            }
            
            (*componentList)[entityID] = T();
            relationships[entityID].set(familyID, 1);
            
            return (*componentList)[entityID];
        }
        template <class T>
        T& getComponent(EntityID entityID) {
            FamilyID familyID = Component::getFamilyID<T>();
            auto& componentList = static_cast<ComponentList<T>&>(*components[familyID]);
            return componentList[entityID];
        }
        void initialize();
        void update();
        template <class T>
        ComponentMask getComponentMask() {
            FamilyID familyID = Component::getFamilyID<T>();
            ComponentMask mask;
            mask.set(familyID, 1);
            return mask;
        }
        bool hasComponents(EntityID, ComponentMask mask);
    };
}

#endif

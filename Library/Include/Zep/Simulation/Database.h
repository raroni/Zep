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
#include "Zep/Simulation/Component.h"
#include "Zep/Simulation/ComponentMask.h"
#include "Zep/Simulation/ComponentList.h"
#include "Zep/Simulation/ComponentTypeRegistry.h"
#include "Zep/Simulation/SimulationConfig.h"
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
        ComponentTypeRegistry componentTypes;
    public:
        Database(EventManager &eventManager);
        EntityID createEntityID();
        template <class T>
        T& createComponent(EntityID entityID) {
            if(!initialized) throw Exception("You must initialize database before creating components.");
            
            int componentTypeID = componentTypes.getID<T>();
            ComponentList<T> *componentList;
            
            if(components[componentTypeID] == nullptr) {
                componentList = new ComponentList<T>();
                componentList->resize(relationships.size());
                components[componentTypeID] = componentList;
            } else {
                componentList = static_cast<ComponentList<T>*>(components[componentTypeID]);
            }
            
            (*componentList)[entityID] = T();
            relationships[entityID].set(componentTypeID, 1);
            
            return (*componentList)[entityID];
        }
        template <class T>
        T& getComponent(EntityID entityID) {
            int componentTypeID = componentTypes.getID<T>();
            auto& componentList = static_cast<ComponentList<T>&>(*components[componentTypeID]);
            return componentList[entityID];
        }
        void initialize();
        void update();
        template <class T>
        ComponentMask getComponentMask() {
            int componentTypeID = componentTypes.getID<T>();
            ComponentMask mask;
            mask.set(componentTypeID, 1);
            return mask;
        }
        bool hasComponents(EntityID, ComponentMask mask);
    };
}

#endif

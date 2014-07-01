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
#include <unordered_map>
#include "Zep/Exception.h"
#include "Zep/Database/EntityID.h"
#include "Zep/Database/Component.h"
#include "Zep/Database/ComponentMask.h"
#include "Zep/Database/ComponentList.h"
#include "Zep/Database/ComponentTypeRegistry.h"
#include "Zep/Database/DatabaseConfig.h"
#include "Zep/Database/ComponentListInterface.h"

namespace Zep {
    class EventManager;
    
    class Database {
        std::vector<EntityID> freedIDs;
        EntityID nextUnusedID = 0;
        std::vector<ComponentListInterface*> components;
        std::vector<ComponentMask> relationships;
        std::vector<EntityID> newCreations;
        std::unordered_map<EntityID, ComponentMask> newRelationships;
        std::vector<EntityID> pendingDestructions;
        void allocate(int newSize);
        EventManager &eventManager;
        bool initialized = false;
        ComponentTypeRegistry componentTypes;
        ComponentMask& getNewRelationshipComponentMask(EntityID id);
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
            
            ComponentMask &mask = getNewRelationshipComponentMask(entityID);
            mask.set(componentTypeID, 1);
            
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
        template <typename T1, typename T2, typename ... Components>
        ComponentMask getComponentMask() {
            return getComponentMask<T1>() | getComponentMask<T2, Components ...>();
        }
        template <class T>
        bool hasComponent(EntityID id) {
            ComponentMask mask = getComponentMask<T>();
            return hasComponents(id, mask);
        }
        void destroy(EntityID entityID);
        template <class T>
        void destroy(EntityID entityID) {
            int componentTypeID = componentTypes.getID<T>();
            ComponentMask &mask = getNewRelationshipComponentMask(entityID);
            mask.set(componentTypeID, 0);
        }
        bool hasComponents(EntityID, ComponentMask mask);
    };
}

#endif

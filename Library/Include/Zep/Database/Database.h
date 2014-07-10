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
#include "Zep/Database/Aspect.h"
#include "Zep/Database/AspectMask.h"
#include "Zep/Database/AspectList.h"
#include "Zep/Database/AspectTypeRegistry.h"
#include "Zep/Database/DatabaseConfig.h"
#include "Zep/Database/AspectListInterface.h"

namespace Zep {
    class EventManager;
    
    class Database {
        std::vector<EntityID> freedIDs;
        EntityID nextUnusedID = 0;
        std::vector<AspectListInterface*> aspects;
        std::vector<AspectMask> relationships;
        std::vector<EntityID> newCreations;
        std::unordered_map<EntityID, AspectMask> newRelationships;
        std::vector<EntityID> pendingDestructions;
        void allocate(int newSize);
        EventManager &eventManager;
        bool initialized = false;
        AspectTypeRegistry aspectTypes;
        AspectMask& getNewRelationshipAspectMask(EntityID id);
    public:
        Database(EventManager &eventManager);
        EntityID createEntityID();
        template <class T>
        T& createAspect(EntityID entityID) {
            if(!initialized) throw Exception("You must initialize database before creating aspects.");
            
            int aspectTypeID = aspectTypes.getID<T>();
            AspectList<T> *aspectList;
            
            if(aspects[aspectTypeID] == nullptr) {
                aspectList = new AspectList<T>();
                aspectList->resize(relationships.size());
                aspects[aspectTypeID] = aspectList;
            } else {
                aspectList = static_cast<AspectList<T>*>(aspects[aspectTypeID]);
            }
            
            (*aspectList)[entityID] = T();
            
            AspectMask &mask = getNewRelationshipAspectMask(entityID);
            mask.set(aspectTypeID, 1);
            
            return (*aspectList)[entityID];
        }
        template <class T>
        AspectTypeID getAspectTypeID() {
            return aspectTypes.getID<T>();
        }
        template <class T>
        T& getAspect(EntityID entityID, AspectTypeID aspectTypeID) {
            auto &aspectList = static_cast<AspectList<T>&>(*aspects[aspectTypeID]);
            return aspectList[entityID];
        }
        template <class T>
        T& getAspect(EntityID entityID) {
            AspectTypeID aspectTypeID = aspectTypes.getID<T>();
            return getAspect<T>(entityID, aspectTypeID);
        }
        void initialize();
        void update();
        template <class T>
        AspectMask getAspectMask() {
            int aspectTypeID = aspectTypes.getID<T>();
            AspectMask mask;
            mask.set(aspectTypeID, 1);
            return mask;
        }
        template <typename T1, typename T2, typename ... aspects>
        AspectMask getAspectMask() {
            return getAspectMask<T1>() | getAspectMask<T2, aspects ...>();
        }
        template <class T>
        bool hasAspect(EntityID id) {
            AspectMask mask = getAspectMask<T>();
            return hasAspects(id, mask);
        }
        void destroy(EntityID entityID);
        template <class T>
        void destroy(EntityID entityID) {
            int aspectTypeID = aspectTypes.getID<T>();
            AspectMask &mask = getNewRelationshipAspectMask(entityID);
            mask.set(aspectTypeID, 0);
        }
        bool hasAspects(EntityID, AspectMask mask);
    };
}

#endif

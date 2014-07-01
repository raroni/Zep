//
//  EntityObserver.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 01/07/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__EntityObserver__
#define __Zep__EntityObserver__

#include <set>
#include "Zep/Events/EventManager.h"
#include "Zep/Events/EventSubscriptionManager.h"
#include "Zep/Database/EntityObserverDelegate.h"
#include "Zep/Database/EntityIDAddition.h"
#include "Zep/Database/EntityIDDestruction.h"
#include "Zep/Database/EntityChange.h"

namespace Zep {
    class EntityObserver {
        EventSubscriptionManager<EntityObserver> eventSubscriptionManager;
        EntityObserverDelegate &delegate;
        std::set<EntityID> ids;
        void add(EntityID id);
        void remove(EntityID id);
    public:
        EntityObserver(EventManager &eventManager, EntityObserverDelegate &delegate);
        void initialize();
        void handle(const EntityIDAddition &addition);
        void handle(const EntityIDDestruction &destruction);
        void handle(const EntityChange &change);
    };
}

#endif

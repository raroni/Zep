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

namespace Zep {
    class EntityObserver {
        EventSubscriptionManager<EntityObserver> eventSubscriptionManager;
        EntityObserverDelegate &delegate;
        std::set<EntityID> entityIDs;
    public:
        EntityObserver(EventManager &eventManager, EntityObserverDelegate &delegate);
        void initialize();
        void receive(const EntityIDAddition &addition);
        void receive(const EntityIDDestruction &destruction);
    };
}

#endif

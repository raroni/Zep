//
//  EventSubscriptionManager.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 12/02/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__EventSubscriptionManager__
#define __Zep__EventSubscriptionManager__

#include "Zep/Events/EventManager.h"
#include "Zep/Events/EventSubscription.h"

namespace Zep {
    template <class ReceiverType>
    class EventSubscriptionManager {
        std::vector<EventSubscription*> subscriptions;
        ReceiverType *receiver;
        EventManager *eventManager;
    public:
        void initialize(ReceiverType &receiver, EventManager &eventManager) {
            this->receiver = &receiver;
            this->eventManager = &eventManager;
        }
        template <class EventType>
        void add() {
            auto subscription = eventManager->subscribe<EventType>(*receiver);
            subscriptions.push_back(subscription);
        }
        ~EventSubscriptionManager() {
            for(auto subscription : subscriptions) {
                delete subscription;
            }
        }
    };
}

#endif

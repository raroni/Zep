//
//  EventSubscriptionManager.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 12/02/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__EventSubscriptionManager__
#define __Zep__EventSubscriptionManager__

#include "Zep/Events/EventBus.h"
#include "Zep/Events/EventSubscription.h"

namespace Zep {
    template <class ReceiverType>
    class EventSubscriptionManager {
        std::vector<EventSubscription> subscriptions;
        ReceiverType &receiver;
        EventBus &eventBus;
    public:
        EventSubscriptionManager(ReceiverType &receiver, EventBus &eventBus) : receiver(receiver), eventBus(eventBus) { }
        template <class EventType>
        void add() {
            auto subscription = eventBus.subscribe<EventType>(receiver);
            subscriptions.push_back(subscription);
        }
        void cancelAll() {
            for(auto &subscription : subscriptions) {
                subscription.cancel();
            }
        }
        ~EventSubscriptionManager() {
            cancelAll();
        }
    };
}

#endif

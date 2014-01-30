//
//  Simulation.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 29/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__Simulation__
#define __Zep__Simulation__

#include <vector>
#include "Zep/Simulation/Database.h"

namespace Zep {
    class Processor;
    class EventManager;
    
    class Simulation {
        std::vector<Processor*> processors;
        bool initialized = false;
        EventManager* eventManager = nullptr;
        Database database;
    public:
        Simulation(EventManager &eventManager);
        void initialize();
        void update(int timeDelta);
        void add(Processor *processor);
        EntityID createEntityID();
        template <class T>
        T& createComponent(EntityID entityID) {
            return database.createComponent<T>(entityID);
        }
    };
}

#endif

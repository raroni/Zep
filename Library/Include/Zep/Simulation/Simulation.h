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
#include "Zep/Exception.h"

namespace Zep {
    class Processor;
    
    class Simulation {
        std::vector<Processor*> processors;
        bool initialized = false;
        Database database;
    public:
        void initialize();
        void update(int timeDelta);
        void add(Processor *processor);
        EntityID createEntityID();
        template <class T>
        T& createComponent(EntityID entityID) {
            if(!initialized) throw Exception("You must initialize to create components.");
            return database.createComponent<T>(entityID);
        }
    };
}

#endif

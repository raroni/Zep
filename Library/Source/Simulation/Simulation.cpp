//
//  Simulation.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 29/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Zep/Simulation/Processor.h"
#include "Zep/Simulation/Simulation.h"

namespace Zep {
    Simulation::Simulation(EventManager &eventManager) : database(Database(eventManager)) { }
    
    void Simulation::add(Processor *processor) {
        if(initialized) throw Exception("You cannot add systems after initialization.");
        processors.push_back(processor);
    }
    
    void Simulation::initialize() {
        for(Processor *processor : processors) {
            processor->initialize();
        }
        initialized = true;
    }
    
    void Simulation::update(int timeDelta) {
        database.update();
        for(Processor *processor : processors) {
            processor->update(timeDelta);
        }
    }
    
    EntityID Simulation::createEntityID() {
        if(!initialized) throw Exception("You must initialize to create entity IDs");
        return database.createEntityID();
    }
}

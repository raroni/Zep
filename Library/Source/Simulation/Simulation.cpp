//
//  Simulation.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 29/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Zep/Simulation/Processor.h"
#include "Zep/Exception.h"
#include "Zep/Simulation/Simulation.h"

namespace Zep {
    Simulation::Simulation(EventManager &eventManager) : database(Database(eventManager)) {
        this->eventManager = &eventManager;
    }
    
    void Simulation::add(Processor *processor) {
        if(initialized) throw Exception("You cannot add systems after initialization.");
        processor->setEventManager(*eventManager);
        processor->setDatabase(database);
        processors.push_back(processor);
    }
    
    void Simulation::initialize() {
        database.initialize();
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
        return database.createEntityID();
    }
}

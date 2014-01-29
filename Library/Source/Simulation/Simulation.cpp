//
//  Simulation.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 29/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Zep/Exception.h"
#include "Zep/Simulation/Processor.h"
#include "Zep/Simulation/Simulation.h"

namespace Zep {
    void Simulation::add(Zep::Processor *processor) {
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
        for(Processor *processor : processors) {
            processor->update(timeDelta);
        }
    }
}

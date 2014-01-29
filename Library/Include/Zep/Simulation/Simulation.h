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

namespace Zep {
    class Processor;
    
    class Simulation {
        std::vector<Processor*> processors;
        bool initialized = false;
    public:
        void initialize();
        void update(int timeDelta);
        void add(Processor *processor);
    };
}

#endif

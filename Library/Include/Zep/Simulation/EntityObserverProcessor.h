//
//  EntityObserverProcessor.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 31/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__EntityObserverProcessor__
#define __Zep__EntityObserverProcessor__

#include "Zep/Simulation/Processor.h"

namespace Zep {
    class EntityIDAddition;
    
    class EntityObserverProcessor : public Processor {
        ComponentMask componentMask;
        virtual ComponentMask createComponentMask() = 0;
        virtual void onAdded(EntityID id) = 0;
    public:
        void initialize();
        void receive(const EntityIDAddition &addition);
    };
}

#endif

//
//  Renderer3D.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 29/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__Renderer3D__
#define __Zep__Renderer3D__

#include "Zep/Simulation/ComponentMask.h"
#include "Zep/Simulation/EntityID.h"
#include "Zep/Simulation/EntityObserverProcessor.h"

namespace Zep {
    class EventManager;
    class EntityIDAddition;
    
    class Renderer3D : public EntityObserverProcessor {
        void onAdded(EntityID id);
        void onRemoved(EntityID id);
        bool match(EntityID id);
    public:
        void update(int timeDelta);
        void receive(const EntityIDAddition &addition);
    };
}

#endif

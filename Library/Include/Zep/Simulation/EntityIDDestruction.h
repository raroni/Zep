//
//  EntityIDDestruction.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 31/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__EntityIDDestruction__
#define __Zep__EntityIDDestruction__

#include "Zep/Simulation/EntityID.h"
#include "Zep/Events/Event.h"

namespace Zep {
    class EntityIDDestruction : public Event {
        EntityID id;
    public:
        EntityIDDestruction(EntityID id);
        EntityID getID() const;
    };
}

#endif

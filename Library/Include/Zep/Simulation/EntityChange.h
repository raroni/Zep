//
//  EntityChange.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 14/02/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__EntityChange__
#define __Zep__EntityChange__

#include "Zep/Events/Event.h"
#include "Zep/Simulation/EntityID.h"

namespace Zep {
    class EntityChange : public Event {
        EntityID id;
    public:
        EntityChange(EntityID id);
        EntityID getID() const;
    };
}

#endif

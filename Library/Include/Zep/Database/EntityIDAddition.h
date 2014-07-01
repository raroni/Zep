//
//  EntityIDAddition.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 30/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__EntityIDAddition__
#define __Zep__EntityIDAddition__

#include "Zep/Events/Event.h"
#include "Zep/Database/EntityID.h"

namespace Zep {
    class EntityIDAddition : public Event {
        EntityID id;
    public:
        EntityIDAddition(EntityID id) : id(id) { }
        EntityID getID() const;
    };
}

#endif

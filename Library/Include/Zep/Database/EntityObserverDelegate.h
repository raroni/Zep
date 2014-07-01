//
//  EntityObserverDelegate.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 01/07/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__EntityObserverDelegate__
#define __Zep__EntityObserverDelegate__

#include "Zep/Database/EntityID.h"

namespace Zep {
    class EntityObserverDelegate {
    public:
        virtual bool match(EntityID id) = 0;
        virtual void handleAddition(EntityID id) = 0;
        virtual void handleRemoval(EntityID id) = 0;
    };
}

#endif

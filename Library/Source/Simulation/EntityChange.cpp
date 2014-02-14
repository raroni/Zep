//
//  EntityChange.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 14/02/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "EntityChange.h"

namespace Zep {
    EntityChange::EntityChange(EntityID id) : id(id) { }
    
    EntityID EntityChange::getID() const {
        return id;
    }
}

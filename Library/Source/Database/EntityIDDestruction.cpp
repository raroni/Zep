//
//  EntityIDDestruction.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 31/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "EntityIDDestruction.h"

namespace Zep {
    EntityIDDestruction::EntityIDDestruction(EntityID id) : id(id) { }
    
    EntityID EntityIDDestruction::getID() const {
        return id;
    }
}

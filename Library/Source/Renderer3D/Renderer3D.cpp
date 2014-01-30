//
//  Renderer3D.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 29/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Zep/Events/EventManager.h"
#include "Zep/Simulation/EntityIDAddition.h"
#include "Zep/Renderer3D/Renderer3D.h"

namespace Zep {
    Renderer3D::Renderer3D(EventManager &eventManager) : eventManager(eventManager) {
        eventManager.subscribe<EntityIDAddition>(*this);
    }
    
    void Renderer3D::update(int timeDelta) {
        
    }
    
    void Renderer3D::receive(const EntityIDAddition &addition) {
        
    }
}

//
//  Renderer3D.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 29/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include <iostream>

#include "Zep/Simulation/Database.h"
#include "Zep/Renderer3D/MeshRendering.h"
#include "Zep/Simulation/Component.h"
#include "Zep/Events/EventManager.h"
#include "Zep/Simulation/EntityIDAddition.h"
#include "Zep/Renderer3D/Renderer3D.h"

namespace Zep {
    void Renderer3D::onInitialize() {
        meshRenderingMask = database->getComponentMask<MeshRendering>();
    }
    
    void Renderer3D::update(int timeDelta) {
        
    }
    
    bool Renderer3D::match(EntityID id) {
        return database->hasComponents(id, meshRenderingMask);
    }
    
    void Renderer3D::onAdded(EntityID id) {
        std::cout << "ADD!\n";
    }
    
    void Renderer3D::onRemoved(EntityID id) {
        std::cout << "DESTROY!\n";
    }
}

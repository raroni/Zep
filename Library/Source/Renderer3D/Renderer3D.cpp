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
    ComponentMask Renderer3D::createComponentMask() {
        return database->getComponentMask<MeshRendering>();
    }
    
    void Renderer3D::update(int timeDelta) {
        
    }
    
    void Renderer3D::onAdded(EntityID id) {
        std::cout << "ADD!\n";
    }
    
    void Renderer3D::onDestroyed(EntityID id) {
        std::cout << "DESTROY!\n";
    }
}

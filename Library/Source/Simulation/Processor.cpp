//
//  Processor.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 29/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Processor.h"

namespace Zep {
    void Processor::setEventManager(EventManager &eventManager) {
        this->eventManager = &eventManager;
    }
    
    void Processor::setDatabase(Database &database) {
        this->database = &database;
    }
}

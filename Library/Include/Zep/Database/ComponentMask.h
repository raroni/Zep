//
//  ComponentMask.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 30/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef Zep_ComponentMask_h
#define Zep_ComponentMask_h

#include <bitset>
#include "Zep/Database/DatabaseConfig.h"

namespace Zep {
    typedef std::bitset<DatabaseConfig::maxComponentTypes> ComponentMask;
}

#endif

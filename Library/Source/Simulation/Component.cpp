//
//  Component.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 29/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Zep/Simulation/Component.h"

namespace Zep {
    std::map<std::type_index, int> Component::familyIDs;
    FamilyID Component::nextUnusedFamilyID = 0;
}

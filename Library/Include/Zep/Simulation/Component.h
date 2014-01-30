//
//  Component.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 29/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__Component__
#define __Zep__Component__

#include <map>
#include <typeindex>
#include "Zep/Simulation/FamilyID.h"

namespace Zep {
    class Component {
    public:
        const static int familyMaxCount = 32;
    private:
        static FamilyID nextUnusedFamilyID;
        static std::map<std::type_index, FamilyID> familyIDs;
    public:
        template <class T>
        static int getFamilyID() {
            auto index = std::type_index(typeid(T));
            auto iterator = familyIDs.find(index);
            if(iterator == familyIDs.end()) {
                FamilyID id = nextUnusedFamilyID++;
                familyIDs[index] = id;
                return id;
            } else {
                return iterator->second;
            }
        }
    };
}

#endif

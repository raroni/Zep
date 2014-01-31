//
//  ComponentTypeRegistry.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 31/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__ComponentTypeRegistry__
#define __Zep__ComponentTypeRegistry__

#include <map>
#include <typeindex>
#include "Zep/Exception.h"

namespace Zep {
    class ComponentTypeRegistry {
        int max;
        int nextUnusedID = 0;
        std::map<std::type_index, int> ids;
    public:
        ComponentTypeRegistry(int max) : max(max) { }
        template <class T>
        int getID() {
            auto index = std::type_index(typeid(T));
            auto iterator = ids.find(index);
            if(iterator == ids.end()) {
                if(nextUnusedID == max) throw Exception("Maximum number of component types reached.");
                int id = nextUnusedID++;
                ids[index] = id;
                return id;
            } else {
                return iterator->second;
            }
        }
    };
}

#endif

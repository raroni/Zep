//
//  AspectTypeRegistry.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 31/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__AspectTypeRegistry__
#define __Zep__AspectTypeRegistry__

#include <map>
#include <typeindex>
#include "Zep/Exception.h"
#include "Zep/Database/AspectTypeID.h"

namespace Zep {
    class AspectTypeRegistry {
        int max;
        AspectTypeID nextUnusedID = 0;
        std::map<std::type_index, AspectTypeID> ids;
    public:
        AspectTypeRegistry(int max) : max(max) { }
        template <class T>
        AspectTypeID getID() {
            auto index = std::type_index(typeid(T));
            auto iterator = ids.find(index);
            if(iterator == ids.end()) {
                if(nextUnusedID == max) throw Exception("Maximum number of Aspect types reached.");
                AspectTypeID id = nextUnusedID++;
                ids[index] = id;
                return id;
            } else {
                return iterator->second;
            }
        }
    };
}

#endif

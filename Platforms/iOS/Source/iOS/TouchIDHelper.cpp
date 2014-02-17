//
//  TouchIDHelper.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 29/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Zep/Exception.h"
#include "Zep/iOS/TouchIDHelper.h"

namespace Zep {
    int TouchIDHelper::createID(intptr_t touchAddress) {
        int id;
        if(destroyedIDs.size() == 0) {
            id = nextUnusedID++;
        } else {
            id = destroyedIDs.back();
            destroyedIDs.pop_back();
        }
        map[touchAddress] = id;
        return id;
    }
    
    int TouchIDHelper::getID(intptr_t touchAddress) {
        auto iterator = find(touchAddress);
        return iterator->second;
    }
    
    void TouchIDHelper::destroyID(intptr_t touchAddress) {
        auto iterator = find(touchAddress);
        destroyedIDs.push_back(iterator->second);
        map.erase(iterator);
    }
    
    TouchIDHelper::Map::iterator TouchIDHelper::find(intptr_t touchAddress) {
        auto iterator = map.find(touchAddress);
        if(iterator == map.end()) throw Exception("Touch address not found.");
        return iterator;
    }
}

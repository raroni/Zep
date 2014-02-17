//
//  TouchIDHelper.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 29/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__TouchIDHelper__
#define __Zep__TouchIDHelper__

#include <map>
#include <vector>

namespace Zep {
    class TouchIDHelper {
        typedef std::map<intptr_t, int> Map;
        Map map;
        std::vector<int> destroyedIDs;
        int nextUnusedID = 1;
        Map::iterator find(intptr_t touchAddress);
    public:
        int createID(intptr_t touchAddress);
        void destroyID(intptr_t touchAddress);
        int getID(intptr_t touchAddress);
    };
}

#endif

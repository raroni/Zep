//
//  EventSignal.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 09/02/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__EventSignal__
#define __Zep__EventSignal__

#include <vector>
#include <unordered_map>

namespace Zep {
    class Event;
    
    class EventSignal {
        typedef std::function<void (const Event&)> Function;
        std::unordered_map<int, int> idIndexMap;
        std::vector<Function> functions;
        std::vector<int> freedIDs;
    public:
        size_t getSubscriptionsCount();
        int subscribe(Function function);
        void emit(Event &event);
        void unsubscribe(int id);
    };
}

#endif

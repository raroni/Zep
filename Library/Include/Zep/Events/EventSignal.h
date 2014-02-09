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
        std::vector<int> disconnectedIDs;
        std::unordered_map<int, Function> functions;
    public:
        int connect(Function function);
        void emit(Event &event);
        void disconnect(int id);
    };
}

#endif

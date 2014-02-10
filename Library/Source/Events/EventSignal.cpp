//
//  EventSignal.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 09/02/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Zep/Exception.h"
#include "Zep/Misc/SafeConversion.h"
#include "Zep/Events/EventSignal.h"

namespace Zep {
    int EventSignal::subscribe(EventSignal::Function function) {
        functions.push_back(function);
        int index = SafeConversion::toInt(functions.size()-1);
        int id;
        if(freedIDs.empty()) {
            id = index;
        } else {
            id = freedIDs.back();
            freedIDs.pop_back();
        }
        idIndexMap[id] = index;
        return id;
    }
    
    void EventSignal::emit(Event &event) {
        for(auto &function : functions) {
            function(event);
        }
    }
    
    void EventSignal::unsubscribe(int id) {
        auto iterator = idIndexMap.find(id);
        if(iterator == idIndexMap.end()) throw Exception("ID not found.");
        int index = idIndexMap[id];
        idIndexMap.erase(iterator);
        freedIDs.push_back(id);
        functions.erase(functions.begin()+index);
        for(auto &pair : idIndexMap) {
            if(pair.second > index) {
                pair.second--;
            }
        }
    }
}

//
//  EventSignal.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 09/02/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Zep/Misc/SafeConversion.h"
#include "Zep/Events/EventSignal.h"

namespace Zep {
    int EventSignal::connect(EventSignal::Function function) {
        int id;
        if(disconnectedIDs.empty()) {
            id = SafeConversion::toInt(functions.size());
            functions[id] = function;
        } else {
            id = disconnectedIDs.back();
            disconnectedIDs.pop_back();
        }
        functions[id] = function;
        return id;
    }
    
    void EventSignal::emit(Event &event) {
        for(auto pair : functions) {
            (pair.second)(event);
        }
    }
    
    void EventSignal::disconnect(int id) {
        auto iterator = functions.find(id);
        if(iterator == functions.end()) throw "Not found.";
        disconnectedIDs.push_back(iterator->first);
        functions.erase(iterator);
    }
}
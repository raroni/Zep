//
//  EventSignalCallback.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 30/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__EventSignalCallback__
#define __Zep__EventSignalCallback__

namespace Zep {
    template <class T>
    class EventSignalCallback {
        typedef std::function<void (const T&)> Function;
        Function function;
    public:
        EventSignalCallback(Function function) : function(function) { }
        void operator()(const Event &event) {
            function(static_cast<const T&>(event));
        }
    };
}

#endif

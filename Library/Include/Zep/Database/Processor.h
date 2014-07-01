//
//  Processor.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 29/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__Processor__
#define __Zep__Processor__

namespace Zep {
    class EventManager;
    class Database;
    
    class Processor {
    protected:
        EventManager *eventManager = nullptr;
        Database *database = nullptr;
    public:
        virtual void initialize() { }
        virtual void update(int timeDelta) = 0;
        void setEventManager(EventManager &eventManager);
        void setDatabase(Database &database);
    };
}

#endif

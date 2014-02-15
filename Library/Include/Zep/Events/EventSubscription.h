//
//  EventSubscription.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 12/02/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__EventSubscription__
#define __Zep__EventSubscription__

namespace Zep {
    class EventSignal;
    
    class EventSubscription {
        EventSignal &signal;
        int id;
    public:
        EventSubscription(EventSignal &signal, int id);
        void cancel();
    };
}

#endif

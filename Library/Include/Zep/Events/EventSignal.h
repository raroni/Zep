//
//  EventSignal.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 30/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__EventSignal__
#define __Zep__EventSignal__

#include "Zep/Events/Signal.h"

namespace Zep {
    class Event;
    typedef Signal<void (const Event&)> EventSignal;
}

#endif

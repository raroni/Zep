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
    class Processor {
    public:
        virtual void initialize() { }
        virtual void update(int timeDelta) = 0;
    };
}

#endif

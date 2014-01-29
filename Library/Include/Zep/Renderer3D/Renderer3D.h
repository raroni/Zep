//
//  Renderer3D.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 29/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__Renderer3D__
#define __Zep__Renderer3D__

#include "Zep/Simulation/Processor.h"

namespace Zep {
    class Renderer3D : public Processor {
    public:
        void update(int timeDelta);
    };
}

#endif

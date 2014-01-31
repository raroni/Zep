//
//  ComponentListInterface.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 29/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef Zep_ComponentListInterface_h
#define Zep_ComponentListInterface_h

namespace Zep {
    class ComponentListInterface {
    public:
        virtual void resize(size_t newSize) = 0;
    };
}

#endif

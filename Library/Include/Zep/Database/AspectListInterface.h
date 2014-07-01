//
//  AspectListInterface.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 29/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef Zep_AspectListInterface_h
#define Zep_AspectListInterface_h

namespace Zep {
    class AspectListInterface {
    public:
        virtual void resize(size_t newSize) = 0;
    };
}

#endif

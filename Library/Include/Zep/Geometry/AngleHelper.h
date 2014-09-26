//
//  AngleHelper.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 25/09/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__AngleHelper__
#define __Zep__AngleHelper__

namespace Zep {
    class AngleHelper {
    public:
        static float normalize(float angle);
        static float normalizeDifference(float angle);
    };
}

#endif

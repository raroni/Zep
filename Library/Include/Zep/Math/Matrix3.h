//
//  Matrix3.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 05/09/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__Matrix3__
#define __Zep__Matrix3__

namespace Zep {
    class Matrix3 {
    public:
        float components[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0 };
        static Matrix3 identity();
        float& operator[](const int index);
        const float& operator[](const int index) const;
    };
}

#endif

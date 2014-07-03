//
//  Vector3.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 03/07/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__Vector3__
#define __Zep__Vector3__

namespace Zep {
    class Vector3 {
        float components[3];
    public:
        Vector3();
        Vector3(float x, float y, float z);
        float& operator[](const int index);
        const float& operator[](const int index) const;
        Vector3 getNegated();
        Vector3& operator*=(float factor);
        void negate();
    };
}

#endif

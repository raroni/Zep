//
//  Vector4.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 27/09/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__Vector4__
#define __Zep__Vector4__

namespace Zep {
    class Vector4 {
    public:
        float components[4];
        Vector4();
        Vector4(float x, float y, float z, float a);
        float& operator[](const int index);
        const float& operator[](const int index) const;
    };
}

#endif

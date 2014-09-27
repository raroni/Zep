//
//  Vector4.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 27/09/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Vector4.h"

namespace Zep {
    Vector4::Vector4() {
        components[0] = 0;
        components[1] = 0;
        components[2] = 0;
        components[3] = 0;
    }

    Vector4::Vector4(float x, float y, float z, float a) {
        components[0] = x;
        components[1] = y;
        components[2] = z;
        components[3] = a;
    }

    float& Vector4::operator[](const int index) {
        return components[index];
    }

    const float& Vector4::operator[](const int index) const {
        return components[index];
    }

}

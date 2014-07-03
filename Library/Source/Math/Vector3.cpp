//
//  Vector3.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 03/07/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Vector3.h"

namespace Zep {
    Vector3::Vector3() {
        components[0] = 0;
        components[1] = 0;
        components[2] = 0;
    }
    
    Vector3::Vector3(float x, float y, float z) {
        components[0] = x;
        components[1] = y;
        components[2] = z;
    }

    void Vector3::negate() {
        operator*=(-1);
    }
    
    Vector3 Vector3::getNegated() {
        Vector3 negated = *this;
        negated.negate();
        return negated;
    }
    
    Vector3& Vector3::operator*=(float factor) {
        components[0] *= factor;
        components[1] *= factor;
        components[2] *= factor;
        return *this;
    }
    
    float& Vector3::operator[](const int index) {
        return components[index];
    }
    
    const float& Vector3::operator[](const int index) const {
        return components[index];
    }
}

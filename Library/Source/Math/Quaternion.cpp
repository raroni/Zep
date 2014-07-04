//
//  Quaternion.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 03/07/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Zep/Math/Vector3.h"
#include "Quaternion.h"

namespace Zep {
    Quaternion::Quaternion(float real, Vector3 imaginaries) : real(real), imaginaries(imaginaries) { }
    
    Quaternion Quaternion::operator*(Quaternion &other) {
        Quaternion result = *this;
        result *= other;
        return result;
    }
    
    Quaternion& Quaternion::operator*=(Quaternion other) {
        float resultReal = real*other.real - Vector3::dot(imaginaries, other.imaginaries);
        auto resultImaginaries = other.imaginaries*real + imaginaries*other.real + Vector3::cross(imaginaries, other.imaginaries);
        real = resultReal;
        imaginaries = resultImaginaries;
        return *this;
    }
    
    Quaternion Quaternion::identity() {
        return Quaternion(1, Zep::Vector3(0, 0, 0));
    }
}

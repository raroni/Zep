//
//  Point3D.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 03/07/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Point3D.h"

namespace Zep {
    Point3D::Point3D() { }
    
    Point3D::Point3D(float x, float y, float z) : vector(x, y, z) { }
    
    Vector3& Point3D::getVector() {
        return vector;
    }
    
    float& Point3D::operator[](const int index) {
        return vector[index];
    }
    
    const float& Point3D::operator[](const int index) const {
        return vector[index];
    }
}

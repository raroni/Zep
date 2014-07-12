//
//  Point3D.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 03/07/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Point3D.h"
#include "Zep/Math/Quaternion.h"

namespace Zep {
    Point3D::Point3D() { }
    
    Point3D::Point3D(Vector3 vector) : vector(vector[0], vector[1], vector[2]) { }
    
    Point3D::Point3D(float x, float y, float z) : vector(x, y, z) { }
    
    Vector3& Point3D::getVector() {
        return vector;
    }
    
    Point3D Point3D::operator-(Vector3 displacement) {
        return Point3D(vector-displacement);
    }
    
    Point3D::operator Vector3() {
        return vector;
    }
    
    Point3D Point3D::operator+(Vector3 vector) {
        Point3D result = *this;
        result += vector;
        return result;
    }
    
    Point3D& Point3D::operator+=(Vector3 other) {
        vector += other;
        return *this;
    }
    
    float& Point3D::operator[](const int index) {
        return vector[index];
    }
    
    const float& Point3D::operator[](const int index) const {
        return vector[index];
    }
    
    Point3D Point3D::getRotated(Quaternion &rotation) {
        Quaternion quaternionVector(0, vector);
        auto result = rotation*quaternionVector;
        result *= rotation.getConjugate();
        return Point3D(result.imaginaries);
    }
}

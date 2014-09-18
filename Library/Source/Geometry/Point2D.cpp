//
//  Point2D.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 28/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Point2D.h"

namespace Zep {
    Point2D::Point2D() { }
    
    Point2D::Point2D(Vector2 vector) : vector(vector[0], vector[1]) { }
    
    Point2D::Point2D(float x, float y) : vector(x, y) { }
    
    Point2D Point2D::operator-(Vector2 displacement) {
        return Point2D(vector-displacement);
    }
    
    Vector2 Point2D::getVector() {
        return vector;
    }
    
    Point2D& Point2D::operator*=(float factor) {
        vector *= factor;
        return *this;
    }

    void Point2D::reset() {
        vector.reset();
    }
    
    Point2D Point2D::operator*(float factor) {
        Point2D result = *this;
        result *= factor;
        return result;
    }
    
    float& Point2D::operator[](const int index) {
        return vector[index];
    }
    
    const float& Point2D::operator[](const int index) const {
        return vector[index];
    }
    
    Point2D::operator Vector2() {
        return vector;
    }
    
    Point2D Point2D::origin() {
        return Point2D(0, 0);
    }
}

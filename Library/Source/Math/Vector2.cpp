//
//  Vector2.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 28/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include <math.h>
#include "Zep/Math/Vector2.h"

namespace Zep {
    Vector2::Vector2(float x, float y) {
        this->components[0] = x;
        this->components[1] = y;
    }
    
    float* Vector2::getComponentsPointer() {
        return &this->components[0];
    }
    
    const float* Vector2::getComponentsPointer() const {
        return &this->components[0];
    }
    
    void Vector2::clamp(float maxLength) {
        float actualLength = getLength();
        if(actualLength > maxLength) {
            normalize();
            operator*=(maxLength);
        }
    }
    
    float& Vector2::operator[](const int index) {
        return getComponentsPointer()[index];
    }
    
    const float& Vector2::operator[](const int index) const {
        return getComponentsPointer()[index];
    }
    
    std::ostream& operator<<(std::ostream &ostream, Vector2 &vector) {
        ostream << "(" << vector[0] << ", " << vector[1] << ")";
        return ostream;
    }
    
    void Vector2::negate() {
        this->operator*=(-1);
    }
    
    Vector2 Vector2::getNegated() {
        Vector2 result = *this;
        result.negate();
        return result;
    }
    
    Vector2& Vector2::operator*=(float factor) {
        components[0] *= factor;
        components[1] *= factor;
        return *this;
    }
    
    Vector2 Vector2::operator*(float factor) {
        Vector2 result = *this;
        result *= factor;
        return result;
    }
    
    float Vector2::getDotProduct(const Vector2 vector) const {
        float dotProduct = components[0]*vector[0] + components[1]*vector[1];
        return dotProduct;
    }
    
    Vector2& Vector2::operator+=(Vector2 vector) {
        components[0] += vector[0];
        components[1] += vector[1];
        return *this;
    }
    
    Vector2 Vector2::operator+(Vector2 vector) {
        Vector2 result = *this;
        result += vector;
        return result;
    }
    
    Vector2& Vector2::operator/=(float divident) {
        components[0] /= divident;
        components[1] /= divident;
        return *this;
    }
    
    Vector2 Vector2::operator-(Vector2 other) {
        Vector2 result;
        result[0] = components[0] - other[0];
        result[1] = components[1] - other[1];
        return result;
    }
    
    float Vector2::getLength() {
        return sqrt(getSquaredLength());
    }
    
    bool Vector2::isZero() {
        return components[0] == 0 && components[1] == 0;
    }
    
    float Vector2::getSquaredLength() {
        return pow(components[0], 2) + pow(components[1], 2);
    }
    
    void Vector2::normalize() {
        operator/=(getLength());
    }
    
    void Vector2::reset() {
        components[0] = 0;
        components[1] = 0;
    }
    
    Vector2 Vector2::getNormalized() {
        Vector2 result = *this;
        result.normalize();
        return result;
    }
}

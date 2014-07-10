//
//  Quaternion.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 03/07/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include <cmath>
#include "Zep/Math/Vector3.h"
#include "Zep/Math/Matrix4.h"
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
    
    Quaternion Quaternion::getConjugate() {
        Quaternion conjugate(real, imaginaries.getNegated());
        return conjugate;
    }
    
    Quaternion::operator Matrix4() {
        auto matrix = Matrix4::identity();
        matrix[0] = 2*(std::pow(real, 2.0f) + std::pow(imaginaries[0], 2))-1;
        matrix[1] = 2*(imaginaries[0]*imaginaries[1]+real*imaginaries[2]);
        matrix[2] = 2*(imaginaries[0]*imaginaries[2]-real*imaginaries[1]);
        
        matrix[4] = 2*(imaginaries[0]*imaginaries[1]-real*imaginaries[2]);
        matrix[5] = 2*(std::pow(real, 2.0f) + std::pow(imaginaries[1], 2))-1;
        matrix[6] = 2*(imaginaries[1]*imaginaries[2]+real*imaginaries[0]);
        
        matrix[8] = 2*(imaginaries[0]*imaginaries[2]+real*imaginaries[1]);
        matrix[9] = 2*(imaginaries[1]*imaginaries[2]-real*imaginaries[0]);
        matrix[10] = 2*(std::pow(real, 2.0f) + std::pow(imaginaries[2], 2))-1;
        
        return matrix;
    }
    
    float Quaternion::getLength() {
        return std::sqrt(real*real + imaginaries[0]*imaginaries[0] + imaginaries[1]*imaginaries[1] + imaginaries[2]*imaginaries[2]);
    }
    
    Quaternion Quaternion::identity() {
        return Quaternion(1, Zep::Vector3(0, 0, 0));
    }
    
    Quaternion Quaternion::operator*(float factor) {
        Quaternion result = *this;
        result *= factor;
        return result;
    }
    
    Quaternion& Quaternion::operator*=(float factor) {
        real *= factor;
        imaginaries *= factor;
        return *this;
    }
    
    Quaternion Quaternion::operator+(Quaternion other) {
        Quaternion result = *this;
        result += other;
        return result;
    }
    
    Quaternion& Quaternion::operator+=(Quaternion other) {
        real += other.real;
        imaginaries += other.imaginaries;
        return *this;
    }
    
    Quaternion Quaternion::slerpWithLimit(Quaternion &origin, Quaternion &destination, float angleLimit) {
        float angle = std::acos(dot(origin, destination));
        float progress = angleLimit > angle ? 1 : angleLimit/angle;
        
        float inverseSine = 1/std::sin(angle);
        
        float q1 = std::sin(1-progress)*angle*inverseSine;
        float q2 = std::sin(progress*angle)*inverseSine;
        
        return origin*q1+destination*q2;
    }
    
    float Quaternion::dot(Quaternion &operandA, Quaternion &operandB) {
        return operandA.real*operandB.real + Vector3::dot(operandA.imaginaries, operandB.imaginaries);
    }
}

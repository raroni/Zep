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
    public:
        float components[3];
        Vector3();
        Vector3(float x, float y, float z);
        float& operator[](const int index);
        const float& operator[](const int index) const;
        Vector3 getNegated();
        Vector3& operator*=(float factor);
        Vector3& operator/=(float divident);
        void negate();
        Vector3 operator*(float factor);
        static float dot(Vector3 operand1, Vector3 operand2);
        static Vector3 cross(Vector3 operand1, Vector3 operand2);
        Vector3 operator+(Vector3 other);
        Vector3& operator+=(Vector3 other);
        Vector3 operator-(Vector3 other);
        Vector3& operator-=(Vector3 other);
        Vector3 getNormalized();
        void normalize();
        float getLength();
        float getSquaredLength();
    };
}

#endif

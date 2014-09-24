//
//  Vector2.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 28/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__Vector2__
#define __Zep__Vector2__

#include <ostream>

namespace Zep {
    class Vector2 {
    protected:
    public:
        float components[2] = {0, 0};
        Vector2(float x = 0, float y = 0);
        float* getComponentsPointer();
        const float* getComponentsPointer() const;
        friend std::ostream& operator<<(std::ostream &ostream, Vector2 &vector);
        float getDotProduct(const Vector2 vector) const;
        Vector2 operator-(Vector2 vector);
        void negate();
        Vector2& operator*=(float factor);
        Vector2 operator*(float factor);
        Vector2& operator+=(Vector2 vector);
        Vector2 operator+(Vector2 vector);
        Vector2& operator/=(float factor);
        float& operator[](const int index);
        const float& operator[](const int index) const;
        void clamp(float maxLength);
        void normalize();
        void reset();
        float getSquaredLength();
        float getLength();
        Vector2 getNegated();
        bool isZero();
        Vector2 getNormalized();
    };
}

#endif

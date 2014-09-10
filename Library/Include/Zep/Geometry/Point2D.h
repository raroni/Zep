//
//  Point2D.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 28/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__Point2D__
#define __Zep__Point2D__

#include "Zep/Math/Vector2.h"

namespace Zep {
    class Point2D {
        Vector2 vector;
    public:
        Point2D();
        Point2D(Vector2 vector);
        Vector2 getVector();
        Point2D(float x, float y);
        float& operator[](const int index);
        const float& operator[](const int index) const;
        Point2D operator-(Vector2 displacement);
        operator Vector2();
        static Point2D origin();
        Point2D& operator*=(float factor);
        Point2D operator*(float factor);
    };
}

#endif

//
//  Point3D.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 03/07/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__Point3D__
#define __Zep__Point3D__

#include "Zep/Math/Vector3.h"

namespace Zep {
    class Quaternion;
    
    class Point3D {
        Vector3 vector;
    public:
        Point3D(float x, float y, float z);
        Point3D(Vector3 vector);
        Point3D();
        Vector3& getVector();
        float& operator[](const int index);
        const float& operator[](const int index) const;
        Point3D operator-(Vector3 other);
        operator Vector3();
        Point3D getRotated(Quaternion &rotation);
    };
}

#endif

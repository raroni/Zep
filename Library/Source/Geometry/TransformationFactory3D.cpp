//
//  TransformationFactory3D.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 03/07/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Zep/Math/Matrix4.h"
#include "Zep/Geometry/Point3D.h"
#include "TransformationFactory3D.h"

namespace Zep {
    namespace TransformationFactory3D {
        Matrix4 translation(Vector3 translation) {
            Matrix4 matrix = Matrix4::identity();
            matrix[12] = translation[0];
            matrix[13] = translation[1];
            matrix[14] = translation[2];
            return matrix;
        }
    }
}

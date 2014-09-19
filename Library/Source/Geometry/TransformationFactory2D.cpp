//
//  TransformationFactory2D.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 05/09/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include <cmath>
#include "Zep/Geometry/TransformationFactory2D.h"
#include "Zep/Math/Matrix3.h"

namespace Zep {
    Matrix3 TransformationFactory2D::scaling(float x, float y) {
        auto scaling = Matrix3::identity();
        scaling[0] = x;
        scaling[4] = y;
        return scaling;
    }
    
    Matrix3 TransformationFactory2D::scaling(float factor) {
        return scaling(factor, factor);
    }

    Matrix3 TransformationFactory2D::rotation(float angle) {
        float cosAngle = std::cos(angle);
        float sinAngle = std::sin(angle);

        auto rotation = Matrix3::identity();
        rotation[0] = cosAngle;
        rotation[1] = sinAngle;
        rotation[3] = -sinAngle;
        rotation[4] = cosAngle;
        return rotation;
    }

    Matrix3 TransformationFactory2D::translation(float x, float y) {
        auto translation = Matrix3::identity();
        translation[6] = x;
        translation[7] = y;
        return translation;
    }
}

//
//  TransformationFactory2D.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 05/09/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

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
}

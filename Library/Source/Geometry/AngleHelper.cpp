//
//  AngleHelper.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 25/09/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include <cmath>
#include "Zep/Geometry/AngleHelper.h"

namespace Zep {
    float AngleHelper::normalize(float angle) {
        float result = fmod(angle, M_PI*2);
        result = fmod(result+M_PI*2, M_PI*2);
        return result;
    }

    float AngleHelper::normalizeDifference(float difference) {
        float x = std::round(difference/(M_PI*2))*M_PI*2;
        return difference-x;
    }
}

//
//  Matrix3.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 05/09/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Zep/Math/Matrix3.h"

namespace Zep {
    float& Matrix3::operator[](const int index) {
        return components[index];
    }
    
    const float& Matrix3::operator[](const int index) const {
        return components[index];
    }
    
    Matrix3 Matrix3::identity() {
        Matrix3 identity;
        identity[0] = 1;
        identity[4] = 1;
        identity[8] = 1;
        return identity;
    }
}

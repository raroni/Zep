//
//  Matrix4.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 03/07/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Matrix4.h"

namespace Zep {
    float& Matrix4::operator[](const int index) {
        return components[index];
    }
    
    const float& Matrix4::operator[](const int index) const {
        return components[index];
    }
    
    Matrix4 Matrix4::identity() {
        Matrix4 matrix;
        matrix[0] = 1;
        matrix[5] = 1;
        matrix[10] = 1;
        matrix[15] = 1;
        
        return matrix;
    }
}

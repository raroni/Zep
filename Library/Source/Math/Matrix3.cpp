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
    
    void Matrix3::reset() {
        for(int i=0; 9>i; i++) {
            components[i] = 0;
        }
    }
    
    Matrix3& Matrix3::operator*=(Matrix3 other) {
        Matrix3 original = *this;
        reset();
        
        int resultIndex;
        for(int row=0; 3>row; row++) {
            for(int column=0; 3>column; column++) {
                resultIndex = column*3+row;
                for(int step=0; 3>step; step++) {
                    components[resultIndex] += original[row+step*3] * other[column*3+step];
                }
            }
        }
        
        return *this;
    }
    
    Matrix3 Matrix3::operator*(Matrix3 other) {
        Matrix3 result = *this;
        result *= other;
        return result;
    }
    
    Matrix3 Matrix3::identity() {
        Matrix3 identity;
        identity[0] = 1;
        identity[4] = 1;
        identity[8] = 1;
        return identity;
    }
}

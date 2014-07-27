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
    
    Matrix4& Matrix4::operator*=(Matrix4 other) {
        Matrix4 original = *this;
        reset();
        
        int resultIndex;
        for(int row=0; 4>row; row++) {
            for(int column=0; 4>column; column++) {
                resultIndex = column*4+row;
                for(int step=0; 4>step; step++) {
                    components[resultIndex] += original[row+step*4] * other[column*4+step];
                }
            }
        }
        
        return *this;
    }
    
    void Matrix4::reset() {
        for(int i=0; 16>i; i++) {
            components[i] = 0;
        }
    }
    
    Matrix4 Matrix4::operator*(Matrix4 other) {
        Matrix4 result = *this;
        result *= other;
        return result;
    }
    
    std::ostream& operator<<(std::ostream &ostream, Matrix4 &matrix) {
        ostream << "\n";
        ostream << "[" << matrix[0] << ", " << matrix[4] << ", " << matrix[8] << ", " << matrix[12] << "]\n";
        ostream << "[" << matrix[1] << ", " << matrix[5] << ", " << matrix[9] << ", " << matrix[13] << "]\n";
        ostream << "[" << matrix[2] << ", " << matrix[6] << ", " << matrix[10] << ", " << matrix[14] << "]\n";
        ostream << "[" << matrix[3] << ", " << matrix[7] << ", " << matrix[11] << ", " << matrix[15] << "]\n";
        return ostream;
    }
}

//
//  Matrix4.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 03/07/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__Matrix4__
#define __Zep__Matrix4__

namespace Zep {
    class Matrix4 {
    public:
        float components[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        static Matrix4 identity();
        float& operator[](const int index);
        const float& operator[](const int index) const;
        Matrix4 operator*(Matrix4 matrix);
        Matrix4& operator*=(Matrix4 matrix);
        void reset();
    };
}

#endif

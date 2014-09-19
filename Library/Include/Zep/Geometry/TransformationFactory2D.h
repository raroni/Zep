//
//  TransformationFactory2D.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 05/09/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__TransformationFactory2D__
#define __Zep__TransformationFactory2D__


namespace Zep {
    class Matrix3;
    
    namespace TransformationFactory2D {
        Matrix3 scaling(float x, float y);
        Matrix3 scaling(float factor);
        Matrix3 rotation(float angle);
        Matrix3 translation(float x, float y);
    }
}

#endif

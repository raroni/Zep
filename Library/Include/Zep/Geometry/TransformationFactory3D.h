//
//  TransformationFactory3D.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 03/07/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__TransformationFactory3D__
#define __Zep__TransformationFactory3D__

namespace Zep {
    class Point3D;
    class Matrix4;
    
    namespace TransformationFactory3D {
        Matrix4 translation(Vector3 position);
    }
}

#endif

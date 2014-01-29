//
//  Screen.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 28/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__Screen__
#define __Zep__Screen__

#include "Zep/Math/Vector2.h"

namespace Zep {
    class Screen {
        Vector2 resolution;
    public:
        void setResolution(Vector2& resolution) {
            this->resolution = resolution;
        }
    };
}

#endif

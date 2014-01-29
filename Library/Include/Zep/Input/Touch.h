//
//  Touch.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 28/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__Touch__
#define __Zep__Touch__

#include "Zep/Geometry/Point2D.h"

namespace Zep {
    class Touch {
        Point2D position;
        int id;
    public:
        enum Status {
            Began,
            Moved,
            Stationary,
            Ended,
            Cancelled
        };
        Touch(int id, Point2D position);
        void setStatus(Status status);
        Status getStatus();
        void setPosition(Point2D position);
        Point2D getPosition();
        int getID();
    private:
        Status status = Began;
    };
}

#endif

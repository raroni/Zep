//
//  Touch.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 28/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Zep/Input/Touch.h"

namespace Zep {
    Touch::Touch(int id, Point2D position) : id(id), position(position) { }
    
    void Touch::setStatus(Touch::Status status) {
        this->status = status;
    }
    
    Touch::Status Touch::getStatus() {
        return status;
    }
    
    void Touch::setPosition(Point2D position) {
        this->position = position;
    }
    
    Point2D Touch::getPosition() {
        return position;
    }
    
    int Touch::getID() {
        return id;
    }
}

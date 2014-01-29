//
//  TouchSurface.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 28/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "TouchSurface.h"
#include "Point2D.h"
#include "Touch.h"

namespace Zep {
    void TouchSurface::cleanUp() {
        updateStationary();
        removeEnded();
        newTouches.clear();
    }
    
    void TouchSurface::registerTouch(int id, Point2D position) {
        Touch* touch = new Touch(id, position);
        touches.push_back(touch);
        
        map.insert(std::map<int, Touch*>::value_type(id, touch));
        justUpdatedTouches.push_back(touch);
        newTouches.push_back(touch);
    }
    
    void TouchSurface::updateTouch(int id, Point2D position) {
        Touch* touch = map.find(id)->second;
        touch->setPosition(position);
        touch->setStatus(Touch::Moved);
        justUpdatedTouches.push_back(touch);
    }
    
    void TouchSurface::endTouch(int id, Point2D position) {
        Touch* touch = map.find(id)->second;
        touch->setPosition(position);
        touch->setStatus(Touch::Ended);
        endedTouches.push_back(touch);
    }
    
    void TouchSurface::cancelTouch(int id, Point2D position) {
        Touch* touch = map.find(id)->second;
        touch->setPosition(position);
        touch->setStatus(Touch::Cancelled);
        endedTouches.push_back(touch);
    }
    
    void TouchSurface::updateStationary() {
        if(!justUpdatedTouches.empty()) {
            std::vector<Touch*>::iterator iterator;
            for(iterator = justUpdatedTouches.begin(); iterator != justUpdatedTouches.end(); ++iterator) {
                (*iterator)->setStatus(Touch::Stationary);
            }
            justUpdatedTouches.clear();
        }
    }
    
    void TouchSurface::removeEnded() {
        if(!endedTouches.empty()) {
            std::vector<Touch*>::iterator iterator;
            Touch* touch;
            for(iterator = endedTouches.begin(); iterator != endedTouches.end(); ++iterator) {
                touch = *iterator;
                touches.erase(std::remove(touches.begin(), touches.end(), touch));
                map.erase(touch->getID());
            }
            endedTouches.clear();
        }
    }
    
    std::vector<Touch*> TouchSurface::getNewTouches() {
        return newTouches;
    }
}

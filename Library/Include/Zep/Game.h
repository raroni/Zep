//
//  Game.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 28/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__Game__
#define __Zep__Game__

#include "Zep/Screen.h"
#include "Zep/Input/TouchSurface.h"

namespace Zep {
    class Game {
        Screen screen;
        TouchSurface touchSurface;
    public:
        virtual void update(int timeDelta) = 0;
        virtual void initialize() { }
        Screen& getScreen();
        TouchSurface& getTouchSurface();
        virtual ~Game() { }
    };
}

#endif

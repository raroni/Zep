//
//  Game.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 28/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Game.h"

namespace Zep {
    Screen& Game::getScreen() {
        return screen;
    }
    
    TouchSurface& Game::getTouchSurface() {
        return touchSurface;
    }
    
    ShaderProgramManager& Game::getShaderProgramManager() {
        return shaderProgramManager;
    }
}

//
//  ShaderProgramManager.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 16/02/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Zep/Exception.h"
#include "Zep/Rendering/ShaderProgram.h"
#include "Zep/Rendering/ShaderProgramManager.h"

namespace Zep {
    void ShaderProgramManager::add(std::string key, Zep::ShaderProgram *program) {
        if(programs.find(key) != programs.end()) {
            throw Exception("Key already used.");
        }
        programs[key] = program;
    }
    
    ShaderProgramManager::~ShaderProgramManager() {
        for(auto &pair : programs) {
            delete pair.second;
        }
    }
}

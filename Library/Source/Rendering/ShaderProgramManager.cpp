//
//  ShaderProgramManager.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 16/02/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include <iostream>

#include "Zep/Exception.h"
#include "Zep/Rendering/ShaderProgram.h"
#include "Zep/Rendering/ShaderProgramManager.h"

namespace Zep {
    void ShaderProgramManager::activate(std::string key, Zep::ShaderProgram *program) {
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
    
    void ShaderProgramManager::activate(std::string key) {
        auto iterator = bundledShaderProgramSources.find(key);
        if(iterator == bundledShaderProgramSources.end()) {
            throw Exception("Bundled shader program not found.");
        }
        auto &source = iterator->second;
        auto program = new ShaderProgram(source.vertex, source.fragment);
        activate(key, program);
    }
    
    std::unordered_map<std::string, ShaderProgramManager::ShaderProgramSource> ShaderProgramManager::bundledShaderProgramSources = {
        {
            "Simple",
            {
                #include "Zep/Rendering/Shaders/Simple.vertex"
                ,
                #include "Zep/Rendering/Shaders/Simple.fragment"
            }
        }
    };
}

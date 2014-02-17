//
//  ShaderProgramManager.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 16/02/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__ShaderProgramManager__
#define __Zep__ShaderProgramManager__

#include <unordered_map>

namespace Zep {
    class ShaderProgram;
    
    class ShaderProgramManager {
        std::unordered_map<std::string, ShaderProgram*> programs;
        struct ShaderProgramSource {
            std::string vertex;
            std::string fragment;
        };
        static std::unordered_map<std::string, ShaderProgramSource> bundledShaderProgramSources;
    public:
        void activate(std::string key, ShaderProgram *program);
        void activate(std::string key);
        ~ShaderProgramManager();
    };
}

#endif

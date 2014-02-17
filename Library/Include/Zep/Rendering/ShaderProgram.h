//
//  ShaderProgram.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 16/02/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#ifndef __Zep__ShaderProgram__
#define __Zep__ShaderProgram__

#include <string>
#include "Zep/Rendering/OpenGL.h"

namespace Zep {
    class ShaderProgram {
        void link();
        GLuint handle;
        GLuint compileShader(std::string source, GLenum type);
    public:
        ShaderProgram(std::string vertexShader, std::string fragmentShader);
    };
}

#endif

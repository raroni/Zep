//
//  ShaderProgram.cpp
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 16/02/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Zep/Exception.h"
#include "Zep/Rendering/ShaderProgram.h"

namespace Zep {
    ShaderProgram::ShaderProgram(std::string vertexShader, std::string fragmentShader) {
        handle = glCreateProgram();
        
        GLuint vertexShaderHandle = compileShader(vertexShader, GL_VERTEX_SHADER);
        GLuint fragmentShaderHandle = compileShader(fragmentShader, GL_FRAGMENT_SHADER);
        
        glAttachShader(handle, vertexShaderHandle);
        glAttachShader(handle, fragmentShaderHandle);
        
        link();
    }
    
    void ShaderProgram::link() {
        glLinkProgram(handle);
        
        GLint linkSuccess;
        glGetProgramiv(handle, GL_LINK_STATUS, &linkSuccess);
        if(linkSuccess == GL_FALSE) {
            GLint logLength;
            glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &logLength);
            
            GLchar *log = new GLchar[logLength+1];
            glGetProgramInfoLog(handle, logLength, NULL, log);
            
            delete[] log;
            
            throw Exception("GL program linking failed.");
        }
    }
    
    GLuint ShaderProgram::compileShader(std::string source, GLenum type) {
        GLuint shaderHandle = glCreateShader(type);
        
        const char *cString = source.c_str();
        glShaderSource(shaderHandle, 1, &cString, NULL);
        
        glCompileShader(shaderHandle);
        
        GLint compileSuccess;
        glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess);
        if(compileSuccess == GL_FALSE) {
            GLint logLength;
            glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &logLength);
            
            GLchar *log = new GLchar[logLength+1];
            glGetShaderInfoLog(shaderHandle, logLength, NULL, log);
            
            delete[] log;
            
            throw Exception("Compilation error in shader.");
        }
        
        return shaderHandle;
    }
}

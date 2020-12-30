#include <GL/glew.h>
#include "Shader.h"
#include "ErrorCatcher.h"
#include <direct.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Shader::Shader(const std::string &filepath) : m_FilePath(), m_RendererID(0) {
    ShaderSource source = parseShader(filepath);
    m_RendererID = createShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader() {
    GlCall(glDeleteProgram(m_RendererID));
}

ShaderSource Shader::parseShader(const std::string &filepath) {
    std::ifstream stream(filepath);
    char buff[FILENAME_MAX];
    _getcwd(buff, FILENAME_MAX);
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType shaderType = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                shaderType = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                shaderType = ShaderType::FRAGMENT;
            }
        } else {
            ss[(int) shaderType] << line << '\n';
        }
    }
    return ShaderSource({ss[0].str(), ss[1].str()});
}

unsigned int Shader::compileShader(unsigned int type, const std::string &source) {
    unsigned int id;
    GlCall(id = glCreateShader(type));
    const char *src = source.c_str();
    GlCall(glShaderSource(id, 1, &src, nullptr));
    GlCall(glCompileShader(id));

    int result;
    GlCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        int length;
        GlCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char message[length];
        GlCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!"
                  << std::endl;
        std::cout << message << std::endl;
        GlCall(glDeleteShader(id));
        return -1;
    }

    return id;
}


unsigned int Shader::createShader(const std::string &vertexShader, const std::string &fragmentShader) {
    unsigned int program;
    GlCall(program = glCreateProgram());
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GlCall(glAttachShader(program, vs));
    GlCall(glAttachShader(program, fs));

    GlCall(glLinkProgram(program));
    GlCall(glValidateProgram(program));

    GlCall(glDeleteShader(vs));
    GlCall(glDeleteShader(fs));
    return program;
}

void Shader::bind() const {
    GlCall(glUseProgram(m_RendererID));
}

void Shader::unbind() const {
    GlCall(glUseProgram(0));
}

void Shader::setUniform4f(const std::string &name, float f0, float f1, float f2, float f3) {
    GlCall(glUniform4f(getUniformLocation(name), f0, f1, f2, f3));
}

unsigned int Shader::getUniformLocation(const std::string &name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
        return m_UniformLocationCache[name];
    }
    int location;
    GlCall(location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1) {
        std::cout << "Warning: uniform '" << name << "' doesn't exist" << std::endl;
    }

    m_UniformLocationCache[name] = location;
    return location;
}




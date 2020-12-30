
#include <string>
#include <unordered_map>

struct ShaderSource {
    std::string vertexSource;
    std::string fragmentSource;
};


class Shader {
private:
    std::string m_FilePath;
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_UniformLocationCache;

public:
    Shader(const std::string &filepath);

    ~Shader();

    void bind() const;

    void unbind() const;

    void setUniform4f(const std::string &name, float f0, float f1, float f2, float f3);

private:
    ShaderSource parseShader(const std::string &filepath);

    unsigned int compileShader(unsigned int type, const std::string &source);

    unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader);

    unsigned int getUniformLocation(const std::string &name);

};


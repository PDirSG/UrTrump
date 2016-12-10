#ifndef shader_H
#    define shader_H

class shader
{
    GLuint loadShader(const char *shaderLocation, GLenum shaderType); 
        int linkProgram(GLuint shaderProgram); 

    GLuint
        program;
    GLuint loadProgram(const char *vertexShaderLocation, const char *fragmentShaderLocation);

    public:
        shader(const char *vertexShaderLocation, const char *fragmentShaderLocation);
       ~shader(void);

        void bind(void)
        {
            glUseProgram(this->program);
        }
};

#    include "shader.c"
#endif

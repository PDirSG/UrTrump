GLuint shader::loadShader(const char *shaderLocation, GLenum shaderType)
{
    FILE *filePointer = fopen(shaderLocation, "r");

    if(filePointer == NULL)
    {
        printf("Error (%s): %s \n", shaderLocation, "Shader source does not exists!");
        return 0;
    }

    fseek(filePointer, 0L, SEEK_END);
    size_t shaderLength = ftell(filePointer);
    fseek(filePointer, 0L, SEEK_SET);

    GLchar *shaderSource = new GLchar[shaderLength + 1];
        shaderSource[shaderLength] = '\0';
    if(fread(shaderSource, shaderLength, 1, filePointer) != 1)
    {
        printf("Error (%s): %s \n", shaderLocation, "Failed to read the shader source.");

        delete shaderSource;
        fclose(filePointer);

		return 0;
    }

    fclose(filePointer);

    GLuint shader = glCreateShader(shaderType); if(shader == 0)
    {
        printf("Error (%s): %s \n", shaderLocation, "Failed to create shader.");

        delete shaderSource;
        return 0;
    }
    glShaderSource(shader, 1, &shaderSource, NULL);

    delete shaderSource;


	glCompileShader(shader);

    GLint shaderCompileStatus; 
        glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompileStatus);
    
    if(!shaderCompileStatus)
	{
        GLint infoLogLength; 
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);	
        GLchar *infoLog = new GLchar[infoLogLength];

        glGetShaderInfoLog(shader, infoLogLength, &infoLogLength, infoLog);
            glDeleteShader(shader);
        printf("Error (%s): %s: %s. \n", shaderLocation, "Shader compiling error", infoLog);

        delete infoLog;

        return 0;
    }

    return shader;
}

int shader::linkProgram(GLuint shaderProgram)
{
    glLinkProgram(shaderProgram);

    GLint programLinkStatus; 
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &programLinkStatus);

    if(!programLinkStatus)
    {
        GLint infoLogLength; 
            glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *infoLog = new GLchar[infoLogLength];

        glGetProgramInfoLog(shaderProgram, infoLogLength, &infoLogLength, infoLog);
        printf("Error: %s: %s. \n", "Program linking error", infoLog);

        delete infoLog;

        return 0;
    }

    glValidateProgram(shaderProgram);

    GLint programValidateStatus;
        glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &programValidateStatus);

    if(!programValidateStatus)
    {
        GLint infoLogLength; 
            glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *infoLog = new GLchar[infoLogLength];

        glGetProgramInfoLog(shaderProgram, infoLogLength, &infoLogLength, infoLog);
        printf("Error: %s: %s. \n", "Program validation error", infoLog);

        delete infoLog;

        return 0;
    }

    return 1;
}

GLuint shader::loadProgram(const char *vertexShaderLocation, const char *fragmentShaderLocation)
{
    GLuint vertexShader = loadShader(vertexShaderLocation, GL_VERTEX_SHADER);

    if(!vertexShader)
		return 0;

    GLuint fragmentShader = loadShader(fragmentShaderLocation, GL_FRAGMENT_SHADER);

    if(!fragmentShader)
    {
        glDeleteShader(vertexShader);
		return 0;
    }

    GLuint program = glCreateProgram(); if(program == 0)
	{
        printf("Error (%s, %s): %s. \n", vertexShaderLocation, fragmentShaderLocation, "Failed to create shader program");

        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);	

		return 0;
	}

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    int programLinkingStatus = linkProgram(program);

    glDetachShader(program, fragmentShader);
    glDeleteShader(fragmentShader);

    glDetachShader(program, vertexShader);
    glDeleteShader(vertexShader);

    if(!programLinkingStatus)
    {
        glDeleteProgram(program);
		return 0;
    }

    return program;
}

shader:: shader(const char *vertexShaderLocation, const char *fragmentShaderLocation)
{
    program = 
        loadProgram(vertexShaderLocation, fragmentShaderLocation);

    if(program == 0)
        throw std::exception();
}

shader::~shader(void)
{
    glDeleteProgram(this->program);
}


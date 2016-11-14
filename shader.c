GLuint shader::loadShader(const char *shaderLocation, GLenum shaderType)
{
	FILE *filePointer = fopen(shaderLocation, "r");

	if(filePointer == NULL)
	{
		printf("Error: %s \n", "Shader source does not exists!");
		return 0;
	}

	fseek(filePointer, 0L, SEEK_END);
	size_t shaderLength = ftell(filePointer);
	fseek(filePointer, 0L, SEEK_SET);

	GLchar *shaderSource = new GLchar[shaderLength + 1]();
	if(fread(shaderSource, shaderLength, 1, filePointer) != 1)
	{
		printf("Error: %s \n", "Failed to read shader source.");
		throw std::exception();
	}

	fclose(filePointer);

	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);

	delete shaderSource;


	glCompileShader(shader);

	GLint shaderCompileStatus; glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompileStatus);
	if(!shaderCompileStatus)
	{
		GLint infoLogLength; glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *infoLog = new GLchar[infoLogLength];

		glGetShaderInfoLog(shader, infoLogLength, &infoLogLength, infoLog);
		printf("Error (%s): %s %s", shaderLocation, "Shader compiling error: ", infoLog);

		delete infoLog;


		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

int    shader::linkProgram(GLuint shaderProgram)
{
	glLinkProgram(shaderProgram);

	GLint programLinkStatus; glGetProgramiv(shaderProgram, GL_LINK_STATUS, &programLinkStatus);
	if(!programLinkStatus)
	{
		GLint infoLogLength; glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *infoLog = new GLchar[infoLogLength];

		glGetProgramInfoLog(shaderProgram, infoLogLength, &infoLogLength, infoLog);
		printf("Error: %s %s", "Program linking error: ", infoLog);

		delete infoLog;

		return 0;
	}

	glValidateProgram(shaderProgram);

	GLint programValidateStatus; glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &programValidateStatus);
	if(!programValidateStatus)
	{
		GLint infoLogLength; glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *infoLog = new GLchar[infoLogLength];

		glGetProgramInfoLog(shaderProgram, infoLogLength, &infoLogLength, infoLog);
		printf("Error: %s %s", "Program validation error: ", infoLog);

		delete infoLog;

		return 0;
	}

	return 1;
}

GLuint shader::loadProgram(const char *vertexShaderLocation, const char *fragmentShaderLocation)
{
	GLuint vertexShader = loadShader(vertexShaderLocation, GL_VERTEX_SHADER);

	if(!vertexShader)
		throw std::exception();

	GLuint fragmentShader = loadShader(fragmentShaderLocation, GL_FRAGMENT_SHADER);

	if(!fragmentShader)
	{
		glDeleteShader(vertexShader);
		throw std::exception();
	}

	GLuint program = glCreateProgram();

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
		throw std::exception();
	}

	return program;
}

shader:: shader(const char *vertexShaderLocation, const char *fragmentShaderLocation)
{
	program = loadProgram(vertexShaderLocation, fragmentShaderLocation);
}

shader::~shader(void)
{
	glDeleteProgram(this->program);
}


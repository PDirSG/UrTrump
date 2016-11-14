void gameWindow::errorCallback(int error, const char *description)
{
	printf("Error %d: %s. \n", error, description);
	throw std::exception();
}

gameWindow:: gameWindow(void)
{
	if(!glfwInit())
	{
		printf("Error: Failed to initialize GLFW. \n");
		throw std::exception();
	} 
	
	glfwSetErrorCallback(errorCallback);
	

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 					GL_TRUE);
	glfwWindowHint(		  GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
	window = glfwCreateWindow(800, 600, "GBox", NULL, NULL);
	
	if(window == NULL)
	{
		glfwTerminate();
		
		printf("Error: Failed to create the window. \n");
		throw std::exception();
	}
}

gameWindow::~gameWindow(void)
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void gameWindow::setIcon(void)
{
	//...
}

void gameWindow::setPosition(void)
{
    const GLFWvidmode *videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	const int monitorX = videoMode->width; const int monitorY = videoMode->height;
	
	glfwSetWindowPos
	(
		 window
	,
		(monitorX - 800) / 2
	,
		(monitorY - 600) / 2
	)
	;
}

void gameWindow::configureContext(void)
{
	glfwMakeContextCurrent(window); glfwSwapInterval(1);

	glewExperimental = GL_TRUE;
	GLenum Result = glewInit();

	if(Result != GLEW_OK)
	{
    	printf("Error: Failed to initialize GLEW: %s. \n", glewGetErrorString(Result));
		throw std::exception();
	}
}

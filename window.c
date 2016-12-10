void gameWindow::errorCallback(int error, const char *description)
{
    printf("Error %d: %s. \n", error, description);
    throw std::exception();
}

gameWindow:: gameWindow(void)
{
    if(!glfwInit())
    {
        puts("Error: Failed to initialize GLFW.");
        throw std::exception();
	} 
	
    glfwSetErrorCallback(errorCallback);
	

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    
    window = glfwCreateWindow(800, 600, "UrTrump", NULL, NULL);
	
    if(window == NULL)
    {
        glfwTerminate();
		
        puts("Error: Failed to create the window.");
        throw std::exception();
	}
}

gameWindow::~gameWindow(void)
{
    glfwDestroyWindow(window);
    glfwTerminate();
}


void gameWindow::configureContext(void)
{
    glfwMakeContextCurrent(window); 
		glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    GLenum Result = glewInit();

    if(Result != GLEW_OK)
    {
	    printf("Error: Failed to initialize GLEW: %s. \n", glewGetErrorString(Result));
	    throw std::exception();
    }
}

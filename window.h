#ifndef window_H
#   define window_H

class gameWindow
{
    static void errorCallback(int error, const char *description);
    
	GLFWwindow *window;
	    void configureContext(void);

    public:
        gameWindow(void);
       ~gameWindow(void);

        void configure(void)
        {
            const GLFWvidmode *videoMode = 
                glfwGetVideoMode(glfwGetPrimaryMonitor());

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

            configureContext();

            glfwSetInputMode(window,      GLFW_CURSOR,GLFW_CURSOR_DISABLED);
            glfwSetInputMode(window, GLFW_STICKY_KEYS,  		   GL_TRUE);
        }

        GLFWwindow *handler(void)
        {
            return window;
        }
};

#    include "window.c"
#endif


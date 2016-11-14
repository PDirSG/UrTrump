#ifndef window_H
#	define window_H

class gameWindow
{
	static void errorCallback(int error, const char *description);
	GLFWwindow *window;void setIcon(void); void setPosition(void);

	void configureContext(void);

	public:
		gameWindow(void);
	       ~gameWindow(void);

		void configure(void)
		{
			setIcon(); setPosition();

			
			configureContext();

			glfwSetInputMode(window,      GLFW_CURSOR,GLFW_CURSOR_DISABLED);
			glfwSetInputMode(window, GLFW_STICKY_KEYS,  		   GL_TRUE);
		}

		GLFWwindow *handler(void)
		{
			return window;
		}
};

#	include "window.c"
#endif


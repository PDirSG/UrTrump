#include "commonH.h"
#include "headers.h"

std::unique_ptr<gameWindow> window; std::unique_ptr<OpenAL> OpenALContext;

//Shader programs and other global variables...

bool gameRunning = false;

void configure(void)
{
	window = std::make_unique<gameWindow>(); window->configure();

	//Set the input handlers...

	glEnable(GL_DEPTH_TEST); glDepthFunc(GL_LESS); glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	OpenALContext = std::make_unique<OpenAL>();
}

void setupGame(void)
{
	//Load shader programs, font, models, maps, textures and sounds...
}

void render(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //...
}

int main(void)
{
	try
	{
		configure();
		setupGame();

	        glClearColor(1.0, 1.0, 1.0, 1.0);

		gameRunning = true; while(gameRunning && !glfwWindowShouldClose(window->handler()))
		{
			glfwPollEvents();

			render(); glfwSwapBuffers(window->handler());
		}

	}catch(...)
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

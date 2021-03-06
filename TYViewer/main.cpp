#include <iostream>
#include <string>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "application.h"
#include "config.h"

Application* application;

void onWindowResized(GLFWwindow* window, int width, int height)
{
	application->resize(width, height);
}

int main(int argc, char* argv[])
{
	if (!Config::load(Application::APPLICATION_PATH + "config.cfg"))
	{
		std::cout << "Failed to load config file." << std::endl <<
			"A config file will now be created where you can enter which model to load." << std::endl <<
			"Please relaunch after!" << std::endl << std::endl;

		if (!Config::save(Application::APPLICATION_PATH + "config.cfg"))
		{
			std::cout << "Failed to create config!" << std::endl <<
				"Check if program has write permission to executable folder." << std::endl;

			std::cin.get();

			return -1;
		}

		std::cout << "Created config file." << std::endl << std::endl;

		std::cout << "Press enter to exit program..." << std::endl;
		std::cin.get();

		return -1;
	}

	GLFWwindow* window;

	if (!glfwInit())
	{
		std::cout << "[FATAL] Failed to initialize GLFW!" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(Config::windowResolutionX, Config::windowResolutionY, "TYViewer", NULL, NULL);
	if (!window)
	{
		std::cout << "[FATAL] Failed to create GLFWwindow!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "[FATAL] Failed to initialize GLAD!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSetWindowSizeCallback(window, onWindowResized);


	application = new Application(window);
	application->initialize();
	application->run();

	return 0;
}
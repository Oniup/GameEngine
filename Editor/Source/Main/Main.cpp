#define GLFW_INCLUDE_NONE

#include "Kryos/Core/Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

int main(int argc, char** argv)
{
	glfwInit();
	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MINOR, 6);
	const glm::ivec2 winSize = glm::ivec2(600, 600);
	GLFWwindow* window = glfwCreateWindow(winSize.x, winSize.y, "Test Window", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.7f, 0.5f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
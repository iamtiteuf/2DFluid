#ifndef GLEW_INITIALIZE
#define GLEW_INITIALIZE

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include <glm/gtx/hash.hpp>
#include <vector>

extern glm::vec3 Camera_Position;
extern glm::vec3 halfboundsize;
extern float Ha, somek, mydx, mydt,pisAcc, cappa;
extern bool labH5,restart;
extern int range, myN,tmax;
struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
	glm::vec2 texUV;

};
struct Transform
{
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 rotation;
	glm::vec3 scale = glm::vec3(1, 1, 1);

	glm::vec3 force = glm::vec3(0, 0, 0);
	glm::vec3 velocity = glm::vec3(0, 0, 0);
	glm::vec3 acceleration = glm::vec3(0, 0, 0);
	float mass = 10.0f;
	float gravity = 10.0f;
	float raduis = 5000.0f;
	float property = 0;
};
extern float l_of_pipe;
extern float viscousity;
extern float flow_rate;
extern float pipe_raduis;
extern float area_of_pipe;

extern float speed_light;
extern float sigma;

extern GLFWwindow* MainWindow;

class Glew_Initialization
{
public:

	
	float width = 1920;
	float height = 1080;
	int Init_Glfw()
	{
		if (!glfwInit())
		{
			return EXIT_FAILURE;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		MainWindow = glfwCreateWindow(width, height, "Hartman", NULL, NULL);
		
		if (!MainWindow)
		{
			glfwTerminate();
			return EXIT_FAILURE;
		}
		glfwMakeContextCurrent(MainWindow);
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			glfwDestroyWindow(MainWindow);
			glfwTerminate();

			std::cout << "failed to initialize glew";
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

};


#endif

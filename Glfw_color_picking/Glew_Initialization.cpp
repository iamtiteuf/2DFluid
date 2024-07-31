#include "Glew_Initialization.h"

glm::vec3 halfboundsize = glm::vec3(10,10,10);
glm::vec3 Camera_Position = glm::vec3(0, 0, 20.0f);
GLFWwindow* MainWindow = nullptr;
float Ha = 1.0f;
bool labH5 = true;
int range = 10;
float l_of_pipe = 10.0f;
float viscousity = 0.01f;
float flow_rate = 4;
float pipe_raduis = 5;
float area_of_pipe = 3;
bool restart = true;
float speed_light = 3e8f;
float sigma = 0.02f;

int myN = 2;
int tmax = 1000;
float somek = 99;
float mydx = 1.e-3;
float mydt = 1.e-6;
float pisAcc = 1.e4;
float cappa = 1.0f;
#ifndef CLASS_TASK_H
#define CLASS_TASK_H
#include "Glew_Initialization.h"
#include <math.h>


class mult
{
public:
	glm::mat3 R3_w()
	{
		return glm::mat3(cos(w), sin(w), 0,
			             sin(w), cos(w), 0,
			             0, 0, 1);
	}
	glm::mat3 R3_omega()
	{
		return glm::mat3(cos(omega), -sin(omega), 0,
			             sin(omega), cos(omega), 0,
			             0, 0, 1);

	}
	glm::mat3 R3_i()
	{
		return glm::mat3(1, 0, 0,
			   0, cos(i), -sin(i), 
			   0, sin(i), cos(i));

	}
private:
	float w;
	float i;
	float omega;
};



#endif // !CLASS_TASK_H

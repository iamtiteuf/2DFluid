#ifndef PHYSICS_HANDLER_H
#define PHYSICS_HANDLER_H
#include "Glew_Initialization.h"
#include "autodiff/forward/dual.hpp"
#include "FADBAD++/fadiff.h"

#define P0  101325 // initial pressure
#define T0  295. //initial temperature
#define R   8.31447 //gas const
   //Cp/Cv
#define m  29.e-3 //g/mol
  //for viscosity coefficient
#define I 1000 //amount of grids
//#define L 1.
//#define CFL 3.
//pistone acceleration


#define CFL 3

autodiff::dual H_z(autodiff::dual x, autodiff::dual y, autodiff::dual z) {
	return 1 + x + y + z + x * y + y * z + x * z + x * y * z + exp(x / y + y / z);/* expression for H_z */;
}

autodiff::dual fff(autodiff::dual x, autodiff::dual y, autodiff::dual z)
{
	

	return 1 + x + y + z + x * y + y * z + x * z + x * y * z + exp(x / y + y / z);
}

class PhysicsHandler
{
private:
	float Y = 1.4f;
	
public:
	float dx = 1e-3f;
	std::vector<float> new_Pressure;//
	std::vector<float> before_Pressure;//
	std::vector<float> new_Density;
	std::vector<float> before_Density;
	std::vector<float> new_Velocity;
	std::vector<float> before_Velocity;
	std::vector<float> new_X;
	std::vector<float> before_X;
	std::vector<double> Veloci;
	std::vector<double> magnetic;
	std::vector<double> Z_axis;
	std::vector<double> magnetic_fie;
	std::vector<double> current;
	std::vector<double> Electric;
	float k = 0;
	double dt, a0, pi, vis, A, B, C, meuu,dq;


	static void Step(Transform& transform)
	{


	}
	void reset()
	{
		
	}
	PhysicsHandler()
	{
		
	}


	void Poisseulle()
	{

		Z_axis.clear();
		Veloci.clear();
		magnetic.clear();
		magnetic_fie.clear();
		current.clear();
		Electric.clear();
		for (float i = -range; i < range+0.1; i = i+0.1)
		{
			Z_axis.push_back(i);
			Veloci.push_back(Vz(i));
			magnetic.push_back(Vzf(i));
			magnetic_fie.push_back(Hz(i));
			current.push_back(Jz(i));
			Electric.push_back(Ez(i));
		}
	}

	double Vzf(float z)
	{
		//return -powf(l_of_pipe,2)*grad_p()* (1 - powf(z/l_of_pipe, 2)) / (2 * 0.01f);
		return -powf(l_of_pipe, 2) * grad_p() * (1 - powf(z / l_of_pipe, 2)) / (2 * viscousity);
	}
	double Vx()
	{
		//return -powf(l_of_pipe,2)*grad_p()* (1 - powf(z/l_of_pipe, 2)) / (2 * 0.01f);
		float x = (cosh(Ha) - 1) / (Ha * sinh(Ha));
		return -powf(l_of_pipe, 2) * grad_p() *x / (viscousity);
	}
	double Hz(float z)
	{
		float x = (sinh(Ha * z / l_of_pipe) - (z / l_of_pipe) * sinh(Ha)) / (cosh(Ha) - 1);
		return Vx() * 4 * sqrt(sigma * viscousity) * glm::pi<float>() * x / speed_light;
	}
	double Vz(float z)
	{
		return Vx() * (cosh(Ha) - cosh(Ha * z / l_of_pipe)) / (cosh(Ha) - 1);
	}
	double grad_p()
	{
		return 8 * viscousity * l_of_pipe * flow_rate / (glm::pi<float>() *powf(pipe_raduis, 4));
	}
	double Jz(float z)
	{
		return Cz(z).y;
	}
	
	glm::dvec3 Mag_field(float z)
	{
		double mini_H = (speed_light / l_of_pipe) * sqrt(viscousity / sigma) * Ha;
		return glm::dvec3(Hz(z), 0.00001, mini_H);
	}
	

	glm::dvec3 Cz(float Z)
	{
		
		autodiff::dual x = Mag_field(Z).x;
		autodiff::dual y = Mag_field(Z).y;
		autodiff::dual z = Mag_field(Z).z;

		autodiff::dual curl_H_x_val = 0;
		autodiff::dual curl_H_y_val = autodiff::derivative(H_z, autodiff::wrt(y), autodiff::at(x, y, z));;
		autodiff::dual curl_H_z_val = 0;

		autodiff::dual u = fff(x, y, z);
		//std::cout << "Before derivative computation:" << std::endl;
		//std::cout << "x: " << x << ", y: " << y << ", z: " << z << std::endl;
		//std::cout << "fff: " << u.val << std::endl;

		//autodiff::dual dudx = autodiff::derivative(fff, autodiff::wrt(x), autodiff::at(x, y, z));
		//autodiff::dual dudy = autodiff::derivative(fff, autodiff::wrt(y), autodiff::at(x, y, z));
		//autodiff::dual dudz = autodiff::derivative(fff, autodiff::wrt(z), autodiff::at(x, y, z));



		//std::cout << "After derivative computation:" << std::endl;
		//std::cout << "dudx: " << dudx.val << ", dudy: " << dudy.val << ", dudz: " << dudz.val << std::endl;

		double temp = speed_light / (4 * glm::pi<float>());
		//double dudx_float = dudx.val;
		//double dudy_float = dudy.val;
		//double dudz_float = dudz.val;

		//double dudx_float = curl_H_x_val.val;
		//double dudy_float = curl_H_y_val.val;
		//double dudz_float = curl_H_z_val.val;


		
		
		//return glm::dvec3(temp * dudx_float, temp * dudy_float, temp * dudz_float);
		
		glm::dvec3 curl_H = glm::cross(Mag_field(Z), glm::dvec3(0, 0, 1));
		//glm::dvec3 curl_H = glm::dvec3(curl_H_x_val, curl_H_y_val, curl_H_z_val);
		return  ((double)speed_light / (4 * glm::pi<double>()) * curl_H);

	}
	double Ez(float z)
	{
		float mini_H = (speed_light / l_of_pipe) * sqrt(viscousity / sigma) * Ha;
		glm::dvec3 bbb = (Cz(z) - (glm::cross((1 / (double)speed_light) * glm::dvec3(Vz(z) / mini_H, 0, 0), Mag_field(z)))) / (double)sigma;
		return bbb.y;
	}
};
#endif
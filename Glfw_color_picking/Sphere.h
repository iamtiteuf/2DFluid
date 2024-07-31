#ifndef SPHERE_CLASS
#define SPHERE_CLASS
#include "Glew_Initialization.h"

class GenSphere
{
	public:
		void generateSphere(float radius, unsigned int rings, unsigned int sectors, glm::vec3 color, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
			float const R = 1.0f / (float)(rings - 1);
			float const S = 1.0f / (float)(sectors - 1);

			vertices.resize(rings * sectors);
			std::vector<Vertex>::iterator v = vertices.begin();

			for (unsigned int r = 0; r < rings; ++r) {
				for (unsigned int s = 0; s < sectors; ++s) {
					float const y = sin(-glm::pi<float>() / 2 + glm::pi<float>() * r * R);
					float const x = cos(2 * glm::pi<float>() * s * S) * sin(glm::pi<float>() * r * R);
					float const z = sin(2 * glm::pi<float>() * s * S) * sin(glm::pi<float>() * r * R);

					v->position = glm::vec3(x, y, z) * radius;
					v->color = color;
					v->texUV = glm::vec2(s * S, r * R);
					v++;
				}
			}

			indices.resize(rings * sectors * 6);
			std::vector<unsigned int>::iterator i = indices.begin();
			for (unsigned int r = 0; r < rings - 1; ++r) {
				for (unsigned int s = 0; s < sectors - 1; ++s) {
					*i++ = r * sectors + s;
					*i++ = r * sectors + (s + 1);
					*i++ = (r + 1) * sectors + (s + 1);
					*i++ = (r + 1) * sectors + s;
					*i++ = r * sectors + s;
					*i++ = (r + 1) * sectors + (s + 1);
				}
			}
		}
};
#endif
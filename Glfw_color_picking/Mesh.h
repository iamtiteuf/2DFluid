#ifndef MESH_CLASS
#define MESH_CLASS
#include "Glew_Initialization.h"

class mesh
{
private:
	float sizeofline;
	std::vector<Vertex> vertices;
	std::vector<Vertex> line_vertices;
	std::vector<unsigned int> indices;

	GLuint VAO, VBO, IBO;
	GLuint VAO_l, VBO_l, IBO_l;
public:
	float length = 5000.0f;
	bool show_line = false;
	bool Line_Attached = false;
	glm::vec3 line_Color = glm::vec3(1,1,1);
	glm::vec3 Color = glm::vec3(1, 0, 0);
	bool RelativeTobody = false;


	
	Transform transform;
	
	glm::vec4 ColorID = glm::vec4(0, 0, 0,0);
	
	~mesh()
	{
		if (VBO != 0)
		{
			glDeleteBuffers(1, &VBO);
			VBO = 0;
		}

		if (IBO != 0)
		{
			glDeleteBuffers(1, &IBO);
			IBO = 0;
		}

		if (VAO != 0)
		{
			glDeleteVertexArrays(1, &VAO);
			VAO = 0;
		}
		if (VBO_l != 0)
		{
			glDeleteBuffers(1, &VBO_l);
			VBO_l = 0;
		}

		if (IBO_l != 0)
		{
			glDeleteBuffers(1, &IBO_l);
			IBO_l = 0;
		}

		if (VAO_l != 0)
		{
			glDeleteVertexArrays(1, &VAO_l);
			VAO_l = 0;
		}
	}
	void ClearMesh()
	{
		if (VBO != 0)
		{
			glDeleteBuffers(1, &VBO);
			VBO = 0;
		}

		if (IBO != 0)
		{
			glDeleteBuffers(1, &IBO);
			IBO = 0;
		}

		if (VAO != 0)
		{
			glDeleteVertexArrays(1, &VAO);
			VAO = 0;
		}
	}
	void UpdateColor(glm::vec3 Color)
	{

		for (auto& Vertex : vertices)
		{
			Vertex.color = Color;
		}

		if (VBO != 0)
		{
			glDeleteBuffers(1, &VBO);
			VBO = 0;
		}

		if (IBO != 0)
		{
			glDeleteBuffers(1, &IBO);
			IBO = 0;
		}

		if (VAO != 0)
		{
			glDeleteVertexArrays(1, &VAO);
			VAO = 0;
		}
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(9 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}



	void CreateMesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
	{
		this->indices = indices;
		this->vertices = vertices;

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(9 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}
	void RenderMesh(GLuint& shaderProgram, glm::mat4& CamMatrix)
	{
		
		glUseProgram(shaderProgram);


		

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, transform.position);
		model = glm::scale(model, transform.scale);

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "CamMatrix"), 1, GL_FALSE, glm::value_ptr(CamMatrix));
		if (glGetUniformLocation(shaderProgram, "aColor") == 1)
		{
			glUniform4fv(glGetUniformLocation(shaderProgram, "aColor"), 1, glm::value_ptr(ColorID));
		}

		
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		
	



		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		
		glUseProgram(0);
	}
	void CreateLine(std::vector<glm::vec3> LineLoc, glm::vec3 Color)
	{

		sizeofline = LineLoc.size();

		//LineLoc = { glm::vec3(-10,0,0),glm::vec3(10,0,0) };

		line_vertices.clear();
		for (int i = 0; i < LineLoc.size(); i++)
		{
			line_vertices.push_back({ LineLoc[i], Color, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f) });

		}


		glGenVertexArrays(1, &VAO_l);
		glBindVertexArray(VAO_l);

		glGenBuffers(1, &VBO_l);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_l);
		glBufferData(GL_ARRAY_BUFFER, line_vertices.size() * sizeof(Vertex), line_vertices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	void DrawLine(GLuint& shaderProgram, glm::mat4& CamMatrix)
	{

		if (VAO_l != 0)
		{
			glUseProgram(shaderProgram);
			glDisable(GL_DEPTH_TEST);
			glBindVertexArray(VAO_l);
			


			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, transform.position);

		
			// Perform the operation here
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "CamMatrix"), 1, GL_FALSE, glm::value_ptr(CamMatrix));


			glDrawArrays(GL_LINE_STRIP, 0, sizeofline);


			glBindVertexArray(0);


			glUseProgram(0);
			glEnable(GL_DEPTH_TEST);
		}
	}
};
#endif

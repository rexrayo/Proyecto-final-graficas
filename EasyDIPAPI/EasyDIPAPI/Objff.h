#pragma once


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

using std::vector;

class Objff {
	
	~Objff();

public:
	unsigned int VBO, VAO, EBO;
	float minX = 0, minY = 0, minZ = 0, maxX = 0, maxY = 0, maxZ = 0;
	glm::vec3 MaxX;
	glm::vec3 MaxY;
	glm::vec3 MaxZ;
	glm::vec3 MinX;
	glm::vec3 MinY;
	glm::vec3 MinZ;
	vector <glm::vec3> drawArrays;
	vector <glm::vec3> v;
	vector <glm::vec3> vn;
	vector <glm::vec3> vnArrays;
	vector <glm::vec3> vt;
	vector <glm::vec3> lv;
	bool white = false, off = false;
	bool Nv = false, Nf = false, isLuz= false, pun = false, lin = false, full = true, material1 = true, material2 = false, material3 = false;
	glm::mat4 transla;
	glm::mat4 escalamiento;
	glm::mat4 rota;
	glm::vec3 t = { 0.0f, -1.3f, 0.0f };
	glm::vec3 scale = { 1.0f, 1.0f, 1.0f };
	glm::vec3 rot = { 0.0f, 0.0f, 0.0f };
	float all = 1.0f;
	float cPuntos[3] = { 0.0f,0.0f,1.0f };
	float cFull[3] = { 1.0f,1.0f,1.0f };
	float cLine[3] = { 0.0f,0.0f,0.0f };
	glm::vec3 ambient{ 1,1,1 };
	glm::vec3 diffuse{ 1,1,1 };
	glm::vec3 specular{ 1,1,1 };
	float shininess = 8.0f;
	vector <glm::uvec3> f;
	vector <glm::vec3> fArray;
	vector <glm::vec3> fn;
	vector <glm::vec3> fc;
	void Draw();
	void Bind();
	void Box();
	void Nvert();
	void Nface();
};
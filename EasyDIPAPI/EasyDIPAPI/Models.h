#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include "Objff.h"

using std::vector;

class Models {
	static Models* instance;
	static unsigned int VBO, VAO;
	Models();
	~Models();
public:

	vector<Objff*> models;
	void Draw();
	void Bind();
	static Models* Instance();
};
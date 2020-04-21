#include "Objff.h"
//static OffC* instance;
//static unsigned int VBO, VAO, EBO;






Objff::~Objff() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Objff::Bind()
{
	glBindVertexArray(VAO);
}

void Objff::Box()
{

}

void Objff::Nvert()
{
	glBegin(GL_LINES);
	for (int i = 0; i < vn.size(); i++)
	{
		glVertex3d(v[i].x, v[i].y, v[i].z);
		glVertex3d(vn[i].x, vn[i].y, vn[i].z);
	}
	glEnd();
}

void Objff::Nface()
{
	glBegin(GL_LINES);
	for (int i = 0; i < fn.size(); i++)
	{
		glVertex3d(fc[i].x, fc[i].y, fc[i].z);
		glVertex3d(fn[i].x, fn[i].y, fn[i].z);
	}
	glEnd();
}

void Objff::Draw()
{
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}



#include "Models.h"

Models* Models::instance = nullptr;

Models::Models() {
	
}

Models::~Models() {

}

void Models::Bind()
{

}

void Models::Draw()
{
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
}

Models* Models::Instance() {
	if (!instance)
	{
		instance = new Models();
	}

	return instance;
}
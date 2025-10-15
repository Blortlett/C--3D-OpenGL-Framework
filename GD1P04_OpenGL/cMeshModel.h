#pragma once
#include <string>
#include <glew.h>

class cMeshModel
{
public:
	cMeshModel(std::string _FilePath);
	~cMeshModel();

	virtual void Update(float _DeltaTime);
	virtual void Render();

protected:
	GLuint VAO;
	GLuint DrawCount;
	int DrawType;
};
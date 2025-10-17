#pragma once
#include <string>
#include <glew.h>
#include <glm.hpp>

class cCamera;

class cMeshModel
{
public:
	cMeshModel(std::string _FilePath, glm::vec3 _Position = glm::vec3(0.0f),
		glm::vec3 _Scale = glm::vec3(1.0f), float _RotationAngle = 0.0f);
	~cMeshModel();

	virtual void Update(float _DeltaTime);
	virtual void Render();
	void bind();
	void unbind();

	// Transform methods
	void SetPosition(glm::vec3 _Position);
	void SetScale(glm::vec3 _Scale);
	void SetRotation(float _Angle, glm::vec3 _Axis = glm::vec3(0.0f, 0.0f, 1.0f));

	glm::vec3 GetPosition() const { return mPosition; }
	glm::vec3 GetScale() const { return mScale; }
	float GetRotation() const { return mRotationAngle; }

	// Matrix getters
	glm::mat4 GetTranslationMatrix() const { return mTranslationMat; }
	glm::mat4 GetRotationMatrix() const { return mRotationMat; }
	glm::mat4 GetScaleMatrix() const { return mScaleMat; }

	// Update transform matrices
	void UpdateTransforms();

	// Getters
	GLuint GetDrawCount() { return DrawCount; }
	GLenum GetDrawType() { return DrawType; }

protected:
	GLuint VAO;
	GLuint VBO;
	GLuint DrawCount;
	GLenum DrawType;

	// Transform properties
	glm::vec3 mPosition;
	glm::vec3 mScale;
	float mRotationAngle;
	glm::vec3 mRotationAxis;

	// Transform matrices
	glm::mat4 mTranslationMat;
	glm::mat4 mRotationMat;
	glm::mat4 mScaleMat;
};
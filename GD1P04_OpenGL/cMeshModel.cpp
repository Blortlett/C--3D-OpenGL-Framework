#define TINYOBJLOADER_IMPLEMENTATION

#include <tiny_obj_loader.h>
#include <iostream>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "cMeshModel.h"
#include "VertexStandard.h"
#include "cTextureLoader.h"

cMeshModel::cMeshModel(std::string _FilePath, glm::vec3 _Position,
	glm::vec3 _Scale, float _RotationAngle)
	: mPosition(_Position), mScale(_Scale), mRotationAngle(_RotationAngle),
	mRotationAxis(0.0f, 0.0f, 1.0f), VAO(0), VBO(0), DrawCount(0), DrawType(GL_TRIANGLES)
{
	// Initialize transform matrices
	mTranslationMat = glm::mat4(1.0f);
	mRotationMat = glm::mat4(1.0f);
	mScaleMat = glm::mat4(1.0f);

	// -= Parse File =-
	std::vector<VertexStandard> Vertices;
	tinyobj::ObjReaderConfig ReaderConfig;
	tinyobj::ObjReader Reader;

	if (!Reader.ParseFromFile(_FilePath, ReaderConfig)) {
		if (!Reader.Error().empty()) {
			std::cerr << "TinyObjReader Error: " << Reader.Error() << std::endl;
		}
		exit(1);
	}

	if (!Reader.Warning().empty()) {
		std::cout << "TinyObjReader Warning: " << Reader.Warning() << std::endl;
	}

	auto& Attrib = Reader.GetAttrib();
	auto& Shapes = Reader.GetShapes();

	// -= Load Model =-
	for (size_t ShapeIndex = 0; ShapeIndex < Shapes.size(); ShapeIndex++)
	{
		// Loop through the faces of the shape
		size_t readIndexOffset = 0;
		for (size_t FaceIndex = 0; FaceIndex < Shapes[ShapeIndex].mesh.num_face_vertices.size(); FaceIndex++)
		{
			size_t FaceVertexCount = size_t(Shapes[ShapeIndex].mesh.num_face_vertices[FaceIndex]);
			for (size_t VertexIndex = 0; VertexIndex < FaceVertexCount; VertexIndex++)
			{
				VertexStandard Vertex{};
				tinyobj::index_t TinyObjVertex = Shapes[ShapeIndex].mesh.indices[readIndexOffset + VertexIndex];

				// Get position data
				Vertex.position = {
					Attrib.vertices[3 * size_t(TinyObjVertex.vertex_index) + 0],
					Attrib.vertices[3 * size_t(TinyObjVertex.vertex_index) + 1],
					Attrib.vertices[3 * size_t(TinyObjVertex.vertex_index) + 2],
				};

				// Get texture coordinate data (if available)
				if (TinyObjVertex.texcoord_index >= 0) // Negative states no texCoordData
				{
					Vertex.texcoord = {
						Attrib.texcoords[2 * size_t(TinyObjVertex.texcoord_index) + 0],
						Attrib.texcoords[2 * size_t(TinyObjVertex.texcoord_index) + 1],
					};
				}

				Vertices.push_back(Vertex);
			}
			readIndexOffset += FaceVertexCount;
		}
	}

	// Store for use in Rendering
	DrawType = GL_TRIANGLES;
	DrawCount = (GLuint)Vertices.size();

	// -= Create the Vertex Array and associated buffers =-
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexStandard) * Vertices.size(),
		Vertices.data(), GL_STATIC_DRAW);

	// -= Setup VertexAttribPointers for Position and Texture coordinates =-
	// VertexStandard layout: vec3 position (12 bytes) + vec2 texcoord (8 bytes) = 20 bytes total

	// Position attribute (location = 0)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStandard), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Texture coordinate attribute (location = 2)
	// Offset: Skip past the position (3 floats = 12 bytes)
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexStandard),
		(GLvoid*)offsetof(VertexStandard, texcoord));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	std::cout << "Loaded OBJ model: " << _FilePath << " (" << DrawCount << " vertices)" << std::endl;
}

cMeshModel::~cMeshModel()
{
	if (VAO != 0) glDeleteVertexArrays(1, &VAO);
	if (VBO != 0) glDeleteBuffers(1, &VBO);
}

void cMeshModel::UpdateTransforms()
{
	mTranslationMat = glm::translate(glm::mat4(1.0f), mPosition);
	mRotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(mRotationAngle), mRotationAxis);
	mScaleMat = glm::scale(glm::mat4(1.0f), mScale);
}

void cMeshModel::Update(float _DeltaTime)
{
	// Leave blank - override in derived classes if needed
}

void cMeshModel::Render()
{
	glBindVertexArray(VAO);
	glDrawArrays(DrawType, 0, DrawCount);
	glBindVertexArray(0);
}

void cMeshModel::SetPosition(glm::vec3 _Position)
{
	mPosition = _Position;
}

void cMeshModel::SetScale(glm::vec3 _Scale)
{
	mScale = _Scale;
}

void cMeshModel::SetRotation(float _Angle, glm::vec3 _Axis)
{
	mRotationAngle = _Angle;
	mRotationAxis = _Axis;
}
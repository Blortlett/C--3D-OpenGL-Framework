#define TINYOBJLOADER_IMPLEMENTATION

#include <tiny_obj_loader.h>
#include <iostream>
#include "cMeshModel.h"
#include "VertexStandard.h"

cMeshModel::cMeshModel(std::string _FilePath)
{
	// -= Parse File =-
	std::vector<VertexStandard> Vertices;
	tinyobj::ObjReaderConfig ReaderConfig;
	tinyobj::ObjReader Reader;

	if (!Reader.ParseFromFile(_FilePath, ReaderConfig)) {
		if (!Reader.Error().empty()) {
			std::cerr << "TinyObjReader: " << Reader.Error();
		}
		exit(1);
	}

	if (!Reader.Warning().empty()) {
		std::cout << "TinyObjReader: " << Reader.Warning();
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
				Vertex.position = {
					Attrib.vertices[3 * size_t(TinyObjVertex.vertex_index) + 0],
					Attrib.vertices[3 * size_t(TinyObjVertex.vertex_index) + 1],
					Attrib.vertices[3 * size_t(TinyObjVertex.vertex_index) + 2],
				};
				if (TinyObjVertex.texcoord_index >= 0) // Negative states no texCoordData
				{
					Vertex.texcoord = {
						Attrib.texcoords[2 * size_t(TinyObjVertex.texcoord_index) + 0],
						Attrib.texcoords[2 * size_t(TinyObjVertex.texcoord_index) + 1],
					};
				}
				/*if (TinyOBjVertex.normal_index >= 0) // Negative states no Normal data
				{
					Vertex.Normal = {
						Attrib.normals[3 * size_t(TinyObjVertex.normal_index) + 0],
						Attrib.normals[3 * size_t(TinyObjVertex.normal_index) + 1],
						Attrib.normals[3 * size_t(TinyObjVertex.normal_index) + 2],
					};
				}*/
				Vertices.push_back(Vertex);
			}
			readIndexOffset += FaceVertexCount;
		}
	}


	// Store for use in Rendering
	DrawType = GL_TRIANGLES;
	DrawCount = (GLuint)Vertices.size();

	// Create the Vertex Array and associated buffers
	GLuint VBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexStandard) * Vertices.size(), Vertices.data(), GL_STATIC_DRAW);

	// ... Create the VertexAttribPointers for both Position and Texture coordinates
	// Keep in mind the new VertexStandard struct!
	// ...
}

cMeshModel::~cMeshModel()
{
}

void cMeshModel::Update(float _DeltaTime)
{
}

void cMeshModel::Render()
{
}

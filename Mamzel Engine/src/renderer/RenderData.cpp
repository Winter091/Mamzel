#include "RenderData.h"

std::shared_ptr<VertexBuffer> RenderData::triangleVB;
std::shared_ptr<IndexBuffer> RenderData::triangleIB;
std::shared_ptr<VertexArray> RenderData::triangleVA;

std::shared_ptr<VertexBuffer> RenderData::quadVB;
std::shared_ptr<IndexBuffer> RenderData::quadIB;
std::shared_ptr<VertexArray> RenderData::quadVA;

std::shared_ptr<VertexBuffer> RenderData::cubeVB;
std::shared_ptr<VertexArray> RenderData::cubeVA;

std::shared_ptr<VertexBuffer> RenderData::linesVB;
std::shared_ptr<VertexArray> RenderData::linesVA;

std::shared_ptr<Shader> RenderData::flatColorShader;
std::shared_ptr<Shader> RenderData::phongLightningShader;

void RenderData::Load()
{
	flatColorShader = Shader::Create("res/shaders/flatColor.glsl");
	phongLightningShader = Shader::Create("res/shaders/phongLightning.glsl");

	// Triangle data ================================================================================================
	float verticesTriangle[] = {
		// a_Position           a_TexCoord     a_Normal
		-0.5f, -0.5f,  0.0f,    0.0f, 0.0f,    0.0f,  0.0f,  1.0f,
		 0.0f,  0.5f,  0.0f,    0.5f, 1.0f,    0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.0f,    1.0f, 0.0f,    0.0f,  0.0f,  1.0f,
	};
	unsigned int indicesTriangle[] = { 0, 1, 2 };

	triangleVB = VertexBuffer::Create(verticesTriangle, sizeof(verticesTriangle));
	triangleIB = IndexBuffer::Create(indicesTriangle, sizeof(indicesTriangle));
	VertexBufferLayout layoutTriangle = {
		{ GL_FLOAT, 3, "a_Position" },
		{ GL_FLOAT, 2, "a_TexCoord" },
		{ GL_FLOAT, 3, "a_Normal" }
	};
	triangleVA = VertexArray::Create(triangleVB, triangleIB, layoutTriangle);

	// Quad data ====================================================================================================
	float verticesQuad[] = {
		// a_Position            a_TexCoord	     a_Normal
		-0.5f, -0.5f,  0.0f,     0.0f, 0.0f,     0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.0f,     0.0f, 1.0f,     0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.0f,     1.0f, 1.0f,     0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.0f,     1.0f, 0.0f,     0.0f,  0.0f,  1.0f
	};
	unsigned int indicesQuad[] = { 0, 1, 2, 2, 3, 0 };

	quadVB = VertexBuffer::Create(verticesQuad, sizeof(verticesQuad));
	quadIB = IndexBuffer::Create(indicesQuad, sizeof(indicesQuad));
	VertexBufferLayout layoutQuad = {
		{ GL_FLOAT, 3, "a_Position" },
		{ GL_FLOAT, 2, "a_TexCoord" },
		{ GL_FLOAT, 3, "a_Normal" }
	};
	quadVA = VertexArray::Create(quadVB, quadIB, layoutQuad);

	// Cube data ====================================================================================================
	float verticesCube[] = {
		// a_Position            a_TexCoord		 a_Normal
		-0.5f, -0.5f, -0.5f,     0.0f, 0.0f,     0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,     1.0f, 0.0f,     0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,     1.0f, 1.0f,     0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,     1.0f, 1.0f,     0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,     0.0f, 1.0f,     0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,     0.0f, 0.0f,     0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,     0.0f, 0.0f,     0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,     1.0f, 0.0f,     0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,     1.0f, 1.0f,     0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,     1.0f, 1.0f,     0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,     0.0f, 1.0f,     0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,     0.0f, 0.0f,     0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f,     1.0f, 0.0f,    -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,     1.0f, 1.0f,    -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,     0.0f, 1.0f,    -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,     0.0f, 1.0f,    -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,     0.0f, 0.0f,    -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,     1.0f, 0.0f,    -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,     1.0f, 0.0f,     1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,     1.0f, 1.0f,     1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,     0.0f, 1.0f,     1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,     0.0f, 1.0f,     1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,     0.0f, 0.0f,     1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,     1.0f, 0.0f,     1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,     0.0f, 1.0f,     0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,     1.0f, 1.0f,     0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,     1.0f, 0.0f,     0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,     1.0f, 0.0f,     0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,     0.0f, 0.0f,     0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,     0.0f, 1.0f,     0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,     0.0f, 1.0f,     0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,     1.0f, 1.0f,     0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,     1.0f, 0.0f,     0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,     1.0f, 0.0f,     0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,     0.0f, 0.0f,     0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,     0.0f, 1.0f,     0.0f,  1.0f,  0.0f
	};

	cubeVB = VertexBuffer::Create(verticesCube, sizeof(verticesCube));
	VertexBufferLayout layoutCube = {
		{ GL_FLOAT, 3, "a_Position" },
		{ GL_FLOAT, 2, "a_TexCoord" },
		{ GL_FLOAT, 3, "a_Normal" }
	};
	cubeVA = VertexArray::Create(cubeVB, layoutCube);

	// Lines data ====================================================================================================
	float verticesLines[] = {
		-0.5f,  0.0f,  0.0f,
		 0.5f,  0.0f,  0.0f,

		 0.0f, -0.5f,  0.0f,
		 0.0f,  0.5f,  0.0f,

		 0.0f,  0.0f, -0.5f,
		 0.0f,  0.0f,  0.5f
	};

	linesVB = VertexBuffer::Create(verticesLines, sizeof(verticesLines));
	VertexBufferLayout layoutLines = {
		{ GL_FLOAT, 3, "a_Position" }
	};
	linesVA = VertexArray::Create(linesVB, layoutLines);
}

void RenderData::Free()
{
	triangleVB = nullptr;
	triangleIB = nullptr;
	triangleVA = nullptr;

	quadVB = nullptr;
	quadIB = nullptr;
	quadVA = nullptr;

	cubeVB = nullptr;
	cubeVA = nullptr;

	linesVB = nullptr;
	linesVA = nullptr;

	flatColorShader = nullptr;
	phongLightningShader = nullptr;
}

#pragma once

#include <memory>

#include "buffers/VertexBuffer.h"
#include "buffers/IndexBuffer.h"
#include "buffers/VertexArray.h"
#include "Shader.h"

class RenderData
{
public:
	static std::shared_ptr<VertexBuffer> triangleVB;
	static std::shared_ptr<IndexBuffer> triangleIB;
	static std::shared_ptr<VertexArray> triangleVA;

	static std::shared_ptr<VertexBuffer> quadVB;
	static std::shared_ptr<IndexBuffer> quadIB;
	static std::shared_ptr<VertexArray> quadVA;

	static std::shared_ptr<VertexBuffer> cubeVB;
	static std::shared_ptr<VertexArray> cubeVA;

	static std::shared_ptr<VertexBuffer> linesVB;
	static std::shared_ptr<VertexArray> linesVA;

	static std::shared_ptr<Shader> flatColorShader;
	static std::shared_ptr<Shader> phongLightningShader;

public:
	static void Load();
	static void Free();
	
	RenderData() = delete;

};
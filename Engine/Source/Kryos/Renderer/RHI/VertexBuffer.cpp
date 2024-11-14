#include "Kryos/Renderer/RHI/VertexBuffer.h"
#include "Kryos/Core/Log.h"
#include <glad/glad.h>

namespace Kryos
{

	VertexBuffer::VertexBuffer(size_t stride, bool useIndexBuffer, bool dynamic)
		: m_Stride(stride), m_Dynamic(dynamic)
	{
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexBuffer);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		if (useIndexBuffer)
		{
			glGenBuffers(1, &m_IndexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		}
	}

	VertexBuffer::VertexBuffer(VertexBuffer&& vbo)
		: m_VertexArray(vbo.m_VertexArray), m_VertexBuffer(vbo.m_VertexBuffer), m_IndexBuffer(vbo.m_IndexBuffer), m_Stride(vbo.m_Stride), m_Dynamic(vbo.m_Dynamic), m_CurrentStride(vbo.m_CurrentStride)
	{
		vbo.m_VertexArray = KY_INVALID32;
		vbo.m_VertexBuffer = KY_INVALID32;
		vbo.m_IndexBuffer = KY_INVALID32;
	}

	VertexBuffer& VertexBuffer::operator=(VertexBuffer&& vbo)
	{
		Destroy();

		m_VertexArray = vbo.m_VertexArray;
		m_VertexBuffer = vbo.m_VertexBuffer;
		m_IndexBuffer = vbo.m_IndexBuffer;
		m_Stride = vbo.m_Stride;
		m_Dynamic = vbo.m_Dynamic;
		m_CurrentStride = vbo.m_CurrentStride;

		vbo.m_VertexArray = KY_INVALID32;
		vbo.m_VertexBuffer = KY_INVALID32;
		vbo.m_IndexBuffer = KY_INVALID32;

		return *this;
	}

	VertexBuffer::~VertexBuffer()
	{
		Destroy();
	}

	void VertexBuffer::Destroy()
	{
		if (m_VertexArray != KY_INVALID32)
		{
			glDeleteVertexArrays(1, &m_VertexArray);
			glDeleteBuffers(1, &m_VertexBuffer);
			m_VertexArray = KY_INVALID32;
			m_VertexBuffer = KY_INVALID32;

			if (m_IndexBuffer != KY_INVALID32)
			{
				glDeleteBuffers(1, &m_IndexBuffer);
				m_IndexBuffer = KY_INVALID32;
			}
		}
	}

	void VertexBuffer::Bind()
	{
		KY_ASSERT(m_VertexArray != KY_INVALID32, "Cannot bind invalid vertex array object");
		glBindVertexArray(m_VertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexArray);
		if (m_IndexBuffer != KY_INVALID32)
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
	}

	void VertexBuffer::Unbind()
	{
		glBindVertexArray(0);
	}

	void VertexBuffer::SetStride(size_t stride)
	{
		m_Stride = stride;
	}

	void VertexBuffer::RegisterElement(size_t size)
	{
		Bind();
		glEnableVertexAttribArray(m_ElementCount);
		glVertexAttribPointer(m_ElementCount, size, GL_FLOAT, GL_FALSE, sizeof(float) * m_Stride, (void*)(sizeof(float) * m_CurrentStride));
		m_CurrentStride += size;
		m_ElementCount++;
	}

	void VertexBuffer::SetIndices(const uint32_t* indices, size_t length)
	{
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * length, indices, m_Dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
		m_IndicesCount = length;
	}

	void VertexBuffer::SubmitDrawData()
	{
		Bind();
		if (m_IndexBuffer != KY_INVALID32)
			glDrawElements(GL_TRIANGLES, m_IndicesCount, GL_UNSIGNED_INT, 0);
		else
			glDrawArrays(GL_TRIANGLES, 0, m_VerticesCount);
	}

	void VertexBuffer::_SetVertices(const float* vertices, size_t length)
	{
		Bind();
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * length, vertices, m_Dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
		if (m_IndexBuffer == KY_INVALID32)
			m_VerticesCount = length / m_Stride;
	}

}
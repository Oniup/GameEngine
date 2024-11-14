#pragma once

#include "Kryos/Core/Defines.h"
#include "Kryos/Core/Log.h"
#include <vector>

namespace Kryos
{

	class VertexBuffer
	{
	public:
		VertexBuffer() = default;
		VertexBuffer(size_t stride, bool useIndexBuffer = false, bool dynamic = false);
		VertexBuffer(VertexBuffer&& vbo);
		VertexBuffer& operator=(VertexBuffer&& vbo);

		~VertexBuffer();
		void Destroy();

		void Bind();
		void Unbind();

		void SetStride(size_t stride);
		void RegisterElement(size_t size);
		void SubmitDrawData();

		void SetIndices(const uint32_t* indices, size_t length);

		template<typename TVertex>
		void SetVertices(const TVertex* vertices, size_t length)
		{
			const float* floatVertices = (float*)vertices;
			length = length * (sizeof(TVertex) / sizeof(float));
			SetVertices(floatVertices, length);
		}

		template<> 
		KY_FORCE_INLINE void SetVertices<float>(const float* vertices, size_t length) { _SetVertices(vertices, length); }

	private:
		uint32_t m_VertexArray = KY_INVALID32;
		uint32_t m_VertexBuffer = KY_INVALID32;
		uint32_t m_IndexBuffer = KY_INVALID32;
		size_t m_ElementCount = 0;
		size_t m_Stride = 0;
		bool m_Dynamic = false;
		size_t m_CurrentStride = 0;
		size_t m_IndicesCount = 0;
		size_t m_VerticesCount = 0;

		VertexBuffer(const VertexBuffer& vbo) = delete;
		VertexBuffer& operator=(const VertexBuffer& vbo) = delete;

		void _SetVertices(const float* vertices, size_t length);
	};

}

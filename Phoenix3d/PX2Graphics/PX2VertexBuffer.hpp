/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2VertexBuffer.hpp
*
* �汾		:	1.0 (2011/01/31)
*
* ����		��	more
*
*/

#ifndef PX2VERTEXBUFFER_HPP
#define PX2VERTEXBUFFER_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Buffer.hpp"

namespace PX2
{
	
	/// ���㻺������
	class VertexBuffer : public Buffer
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(VertexBuffer);

	public:
		VertexBuffer (int numVertices, int vertexSize, Usage usage = BU_STATIC);
		virtual ~VertexBuffer ();

		// ����buffer
		inline char* GetData () const;
	};

	PX2_REGISTER_STREAM(VertexBuffer);
	typedef Pointer0<VertexBuffer> VertexBufferPtr;
#include "PX2VertexBuffer.inl"

}

#endif

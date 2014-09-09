/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Dx9VertexBuffer.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2DX9VERTEXBUFFER_HPP
#define PX2DX9VERTEXBUFFER_HPP

#include "PX2Dx9RendererPre.hpp"
#include "PX2VertexBuffer.hpp"

namespace PX2
{

	class Renderer;

	class PdrVertexBuffer
	{
	public:
		PdrVertexBuffer (Renderer* renderer, const VertexBuffer* vbuffer);
		~PdrVertexBuffer ();

		void Enable (Renderer* renderer, unsigned int vertexSize,
			unsigned int streamIndex, unsigned int offset);
		void Disable (Renderer* renderer, unsigned int streamIndex);
		void* Lock (Buffer::Locking mode);
		void Unlock ();

	private:
		IDirect3DVertexBuffer9* mBuffer;
	};

}

#endif

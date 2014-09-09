/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Dx9VertexShader.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2DX9VERTEXSHADER_HPP
#define PX2DX9VERTEXSHADER_HPP

#include "PX2Dx9RendererPre.hpp"
#include "PX2Dx9Shader.hpp"
#include "PX2VertexShader.hpp"

namespace PX2
{

	class Renderer;

	class PdrVertexShader : public PdrShader
	{
	public:
		PdrVertexShader (Renderer* renderer, const VertexShader* vshader);
		~PdrVertexShader ();

		void Enable (Renderer* renderer, const VertexShader* vshader,
			const ShaderParameters* parameters);
		void Disable (Renderer* renderer, const VertexShader* vshader,
			const ShaderParameters* parameters);

	private:
		IDirect3DVertexShader9* mShader;
	};

}

#endif
/*
* Turandot 3D ��Ϸ���� Version 1.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	TdOpenGLES2VertexFormat.hpp
*
* �汾		:	1.0 (2011/07/20)
*
* ����		��	���
*
*/

#ifndef PX2OPENGLES2VERTEXSHADER_HPP
#define PX2OPENGLES2VERTEXSHADER_HPP

#include "PX2OpenGLES2RendererPre.hpp"
#include "PX2OpenGLES2Shader.hpp"
#include "PX2VertexShader.hpp"

namespace PX2
{

	class Renderer;

	class PdrVertexShader : public PdrShader
	{
	public:
		PdrVertexShader (Renderer* renderer, const VertexShader* vshader);
		virtual ~PdrVertexShader ();

		void Enable (Renderer* renderer, const VertexShader* vshader,
			const ShaderParameters* parameters);
		void Disable (Renderer* renderer, const VertexShader* vshader,
			const ShaderParameters* parameters);
	};

}

#endif

/*
* Turandot 3D 游戏引擎 Version 1.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	TdOpenGLES2VertexFormat.hpp
*
* 版本		:	1.0 (2011/07/20)
*
* 作者		：	许多
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

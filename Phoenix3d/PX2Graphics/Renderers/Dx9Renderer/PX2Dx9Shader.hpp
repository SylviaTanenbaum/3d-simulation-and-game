/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Dx9Shader.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2DX9SHADER_HPP
#define PX2DX9SHADER_HPP

#include "PX2Dx9RendererPre.hpp"
#include "PX2Dx9RendererData.hpp"
#include "PX2Shader.hpp"
#include "PX2ShaderParameters.hpp"

namespace PX2
{

	class Renderer;

	class PdrShader
	{
	public:
		PdrShader ();
		~PdrShader ();

	protected:
		void SetSamplerState (Renderer* renderer, const Shader* shader,
			int profile, const ShaderParameters* parameters, int maxSamplers,
			DWORD base, RendererData::SamplerState* currentSS);

		void DisableTextures (Renderer* renderer, const Shader* shader,
			int profile, const ShaderParameters* parameters, int maxSamplers,
			DWORD base);
	};

}

#endif
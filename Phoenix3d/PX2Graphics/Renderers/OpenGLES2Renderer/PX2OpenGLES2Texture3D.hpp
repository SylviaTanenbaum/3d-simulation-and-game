/*
* Turandot 3D ��Ϸ���� Version 1.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2OpenGLES2Texture3D.hpp
*
* �汾		:	1.0 (2011/07/12)
*
* ����		��	���
*
*/

#ifndef PX2OPENGLES2TEXTURE3D_HPP
#define PX2OPENGLES2TEXTURE3D_HPP

#include "PX2OpenGLES2RendererPre.hpp"
#include "PX2Texture3D.hpp"

namespace PX2
{

	class Renderer;

	class PdrTexture3D
	{
	public:
		PdrTexture3D (Renderer* renderer, const Texture3D* texture);
		~PdrTexture3D ();

		void Enable (Renderer* renderer, int textureUnit);
		void Disable (Renderer* renderer, int textureUnit);
		void* Lock (int level, Buffer::Locking mode);
		void Unlock (int level);
	};

}

#endif

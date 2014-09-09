/*
* Turandot 3D ��Ϸ���� Version 1.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2OpenGLES2TextureCube.hpp
*
* �汾		:	1.0 (2011/07/12)
*
* ����		��	���
*
*/

#ifndef PX2OPENGLES2TEXTURECUBE_HPP
#define PX2OPENGLES2TEXTURECUBE_HPP

#include "PX2OpenGLES2RendererPre.hpp"
#include "PX2TextureCube.hpp"

namespace PX2
{

	class Renderer;

	class PdrTextureCube
	{
	public:
		PdrTextureCube (Renderer* renderer, const TextureCube* texture);
		~PdrTextureCube ();

		void Enable (Renderer* renderer, int textureUnit);
		void Disable (Renderer* renderer, int textureUnit);
		void* Lock (int face, int level, Buffer::Locking mode);
		void Unlock (int face, int level);
	};

}

#endif
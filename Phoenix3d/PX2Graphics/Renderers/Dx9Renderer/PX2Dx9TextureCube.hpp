/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Dx9TextureCube.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2DX9TEXTURECUBE_HPP
#define PX2DX9TEXTURECUBE_HPP

#include "PX2Dx9RendererPre.hpp"
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

	private:
		IDirect3DCubeTexture9* mTexture;
	};

}

#endif

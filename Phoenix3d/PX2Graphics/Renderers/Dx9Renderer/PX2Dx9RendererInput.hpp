/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Dx9RendererInput.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2DX9RENDERERINPUT_HPP
#define PX2DX9RENDERERINPUT_HPP

#include "PX2Dx9RendererPre.hpp"

namespace PX2
{

	class RendererInput
	{
	public:
		IDirect3D9* mDriver;
		HWND mWindowHandle;
	};

}

#endif
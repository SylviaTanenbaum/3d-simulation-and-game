/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2OpenGLES2RendererInput.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2OPENGLES2RENDERERINPUT_HPP
#define PX2OPENGLES2RENDERERINPUT_HPP

#include "PX2OpenGLES2RendererPre.hpp"

namespace PX2
{

	class RendererInput
	{
	public:
        
#if defined(_WIN32) || defined(WIN32) || defined(__ANDROID__) || defined(__MARMALADE__)
		EGLNativeWindowType  mWindowHandle;
		EGLNativeDisplayType mRendererDC;
#endif
	};

}

#endif
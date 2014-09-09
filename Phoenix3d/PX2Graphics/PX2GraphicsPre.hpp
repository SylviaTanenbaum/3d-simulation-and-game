/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2GraphicsPre.hpp
*
* �汾		:	1.0 (2011/01/31)
*
* ����		��	more
*
*/

#ifndef PX2GRAPHICSPRERE_HPP
#define PX2GRAPHICSPRERE_HPP

#include "PX2MathematicsPre.hpp"

#if defined(__ANDROID__) || defined(__MARMALADE__) || defined(__APPLE__)
	#define PX2_USE_OPENGLES2
#endif

// ���ϴ˺������������Ƿ����������м�飬ֻ����һ����������飬ֻ
// ��Ҫ����һ����������
#ifdef _DEBUG
    #define PX2_VALIDATE_CAMERA_FRAME_ONCE
#endif

// ���ı���Shader::MAX_PROFILES����shader�־û���ȡʱʹ�ô˺�������ԡ�
#ifdef _DEBUG
    #define PX2_ASSERT_ON_CHANGED_MAX_PROFILES
#endif

// ��������꣬Renderer::Draw (const Renderable*, const MaterialInstance*)��Ⱦ
// ��ϣ��ڲ����ûص�ȱʡ��Ⱦ״̬��
#ifdef _DEBUG
	//#define PX2_RESET_STATE_AFTER_DRAW
#endif

// ���ϴ˺������Ⱦ�������ļ���
// Renderer::DrawPrimitive.
//#define PX2_QUERY_PIXEL_COUNT

#ifdef PX2_USE_OPENGL
    #ifndef __LINUX__
        #define PX2_USE_TEXT_DISPLAY_LIST
    #endif

    #ifndef __APPLE__
        #define PX2_USE_OPENGL2_NORMAL_ATTRIBUTES
    #endif
#endif

// Dx9��Ⱦ���е�һЩ���
#ifdef PX2_USE_DX9
    #ifdef _DEBUG
        //#define PX2_PDR_DEBUG
    #endif
#endif

#ifdef __ANDROID__
	#define PX2_USE_OPENGLES2
#endif

#endif
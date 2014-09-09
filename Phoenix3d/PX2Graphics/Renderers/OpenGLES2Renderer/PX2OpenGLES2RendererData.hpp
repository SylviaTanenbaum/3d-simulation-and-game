/*
* Turandot 3D ��Ϸ���� Version 1.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	TdOpenGLES2RendererData.hpp
*
* �汾		:	1.0 (2011/07/12)
*
* ����		��	���
*
*/

#ifndef PX2OPENGLES2RENDERERDATA_HPP
#define PX2OPENGLES2RENDERERDATA_HPP

#include "PX2Float4.hpp"
#include "PX2OpenGLES2RendererPre.hpp"

namespace PX2
{

	class AlphaProperty;
	class CullProperty;
	class DepthProperty;
	class OffsetProperty;
	class StencilProperty;
	class WireProperty;

	class RendererData
	{
	public:

		class RenderState
		{
		public:
			RenderState ();
			void Initialize (const AlphaProperty* astate,
				const CullProperty* cstate, const DepthProperty* dstate,
				const OffsetProperty* ostate, const StencilProperty* sstate,
				const WireProperty* wstate);

			// AlphaProperty
			bool mAlphaBlendEnabled;
			GLenum mAlphaSrcBlend;
			GLenum mAlphaDstBlend;
			bool mAlphaCompareEnabled;
			GLenum mCompareFunction;
			float mAlphaReference;
			Float4 mBlendColor;

			// CullState
			bool mCullEnabled;
			bool mCCWOrder;

			// DepthProperty
			bool mDepthEnabled;
			bool mDepthWriteEnabled;
			GLenum mDepthCompareFunction;

			// OffsetState
			bool mFillEnabled;
			bool mLineEnabled;
			bool mPointEnabled;
			float mOffsetScale;
			float mOffsetBias;

			// StencilProperty
			bool mStencilEnabled;
			GLenum mStencilCompareFunction;
			GLuint mStencilReference;
			GLuint mStencilMask;
			GLuint mStencilWriteMask;
			GLenum mStencilOnFail;
			GLenum mStencilOnZFail;
			GLenum mStencilOnZPass;

			// WireState
			bool mWireEnabled;
		};

		RenderState mCurrentRS;

		enum
		{
			MAX_NUM_VSAMPLERS = 4,  // VSModel 3 has 4, VSModel 2 has 0.
			MAX_NUM_PSAMPLERS = 16  // PSModel 2 and PSModel 3 have 16.
		};

		class SamplerState
		{
		public:
			SamplerState ();

			void GetCurrent (GLenum target);

			GLint mMagFilter;
			GLint mMinFilter;
			GLint mWrap[2];
		};
        
#if defined(_WIN32) || defined(WIN32) || defined(__ANDROID__) || defined(__MARMALADE__)

		// ƽ̨��ص�����
		EGLNativeWindowType  mWindowHandle;
		EGLNativeDisplayType mDisplayType;
		EGLDisplay mDisplay;
		EGLConfig mConfig;	
		EGLSurface mSurface;
		EGLContext mContext;
        
#endif

		SamplerState mCurrentSS[MAX_NUM_PSAMPLERS];

		// �豸����
		int mMaxVShaderImages;
		int mMaxPShaderImages;
		int mMaxCombinedImages;
	};

}

#endif
/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2RenderTarget.hpp
*
* �汾		:	1.0 (2011/01/31)
*
* ����		��	more
*
*/

#ifndef PX2RENDERTARGET_HPP
#define PX2RENDERTARGET_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Texture2D.hpp"

namespace PX2
{

	/// ��Ⱦ�����������
	class RenderTarget : public Object
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(RenderTarget);

	public:
		/// ���캯��
		/**
		* ֧�ֵ�render target������Ӳ����numTargets����Ϊ1��
		*/
		RenderTarget (int numTargets, Texture::Format tformat, int width,
			int height, bool hasMipmaps, bool hasDepthStencil);

		virtual ~RenderTarget ();

		// ��Ա����
		inline int GetNumTargets () const;
		inline Texture::Format GetFormat () const;
		inline int GetWidth () const;
		inline int GetHeight () const;
		inline Texture2D* GetColorTexture (int i) const;
		inline Texture2D* GetDepthStencilTexture () const;
		inline bool HasMipmaps () const;
		inline bool HasDepthStencil () const;

		void *PdrPointer;

	protected:
		int mNumTargets;
		Texture2DPtr* mColorTextures;
		Texture2DPtr mDepthStencilTexture;
		bool mHasMipmaps;
	};

	PX2_REGISTER_STREAM(RenderTarget);
	typedef Pointer0<RenderTarget> RenderTargetPtr;
#include "PX2RenderTarget.inl"

}

#endif

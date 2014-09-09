/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2TextureCube.hpp
*
* �汾		:	1.0 (2011/01/31)
*
* ����		��	more
*
*/

#ifndef PX2TEXTURECUBE_HPP
#define PX2TEXTURECUBE_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Texture.hpp"

namespace PX2
{
	
	/// ������������
	class TextureCube : public Texture
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(TextureCube);

	public:
		// cube����ÿ�����ά�ȱ���һ����dimension-by-dimension��
		TextureCube (Format tformat, int dimension, int numLevels,
			Buffer::Usage usage = Buffer::BU_TEXTURE);

		virtual ~TextureCube ();

		// ��õ�0����mipmap�Ŀ�Ⱥ͸߶�
		inline int GetWidth () const;
		inline int GetHeight () const;

		// mipmap����֧��
		void GenerateMipmaps ();
		bool HasMipmaps () const;

		// ע�⣺Texture::GetNumLevelBytes(level)����*one* face��level������ֽ�����
		// Texture::GetNumTotalBytes()����*all* faces��all levels�ֽ�������

		/// ������������
		char* GetData (int face, int level) const;

	protected:
		// mipmap������֧��
		void ComputeNumLevelBytes ();
		void GenerateNextMipmap (int dimension, const char* texels,
			int dimensionNext, char* texelsNext, Float4* rgba);

		// Begin TextureCube����
	public:
		static TextureCube* LoadPXtf (const std::string& name,
			int mode = FileIO::FM_DEFAULT_READ);
		// End TextureCube����
	};

	PX2_REGISTER_STREAM(TextureCube);
	typedef Pointer0<TextureCube> TextureCubePtr;
#include "PX2TextureCube.inl"

}

#endif
/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Texture2D.hpp
*
* �汾		:	1.0 (2011/01/31)
*
* ����		��	more
*
*/

#ifndef PX2TEXTURE2D_HPP
#define PX2TEXTURE2D_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Texture.hpp"

namespace PX2
{
	
	/// 2D������
	class Texture2D : public Texture
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(Texture2D);

	public:
		/**
		* ���numLevelsΪ0���Ὺ�����м���minmap�ռ䡣
		*/
		Texture2D (Format tformat, int dimension0, int dimension1,
			int numLevels, Buffer::Usage usage = Buffer::BU_TEXTURE);

		virtual ~Texture2D ();

		// ��õ�0����mipmap�Ŀ�Ⱥ͸߶�
		inline int GetWidth () const;
		inline int GetHeight () const;

		// minmap����֧��
		void GenerateMipmaps ();
		bool HasMipmaps () const;

		// ������������
		char* GetData (int level) const;

	protected:
		// mipmap������֧��
		void ComputeNumLevelBytes ();
		void GenerateNextMipmap (int width, int height, const char* texels,
			int widthNext, int heightNext, char* texelsNext, Float4* rgba);

		// Begin Texture2D����
	public:
		static Texture2D* LoadPXtf (const std::string& name,
			int mode = FileIO::FM_DEFAULT_READ);
		// End Texture2D����
	};

	PX2_REGISTER_STREAM(Texture2D);
	typedef Pointer0<Texture2D> Texture2DPtr;
#include "PX2Texture2D.inl"

}

#endif
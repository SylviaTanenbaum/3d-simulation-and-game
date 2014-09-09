/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Texture1D.hpp
*
* �汾		:	1.0 (2011/01/31)
*
* ����		��	more
*
*/

#ifndef PX2TEXTURE1D_HPP
#define PX2TEXTURE1D_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Texture.hpp"

namespace PX2
{
	
	/// 1D������
	class Texture1D : public Texture
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(Texture1D);

	public:
		Texture1D (Format tformat, int dimension0, int numLevels,
			Buffer::Usage usage = Buffer::BU_TEXTURE);

		virtual ~Texture1D ();

		// ��õ�0����mipmap�Ŀ��
		inline int GetLength () const;

		// mipmap����֧��
		void GenerateMipmaps ();
		bool HasMipmaps () const;

		// ������������
		char* GetData (int level) const;

	protected:
		// ����֧������mipmap
		void ComputeNumLevelBytes ();
		void GenerateNextMipmap (int length, const char* texels, int lengthNext,
			char* texelsNext, Float4* rgba);

		// Begin Texture1D����
	public:
		static Texture1D* LoadPXtf (const std::string& name,
			int mode = FileIO::FM_DEFAULT_READ);
		// End Texture1D����
	};

	PX2_REGISTER_STREAM(Texture1D);
	typedef Pointer0<Texture1D> Texture1DPtr;
#include "PX2Texture1D.inl"

}

#endif

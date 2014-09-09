/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2TriStrip.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2TRISTRIP_HPP
#define PX2TRISTRIP_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Triangles.hpp"

namespace PX2
{
	
	/// ������������
	class TriStrip : public Triangles
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(TriStrip);

	protected:
		TriStrip ();

	public:
		/**
		* indexSize�Ƕ���������һ��Ԫ�ص��ֽ�����
		*/
		TriStrip (VertexFormat* vformat, VertexBuffer* vbuffer, int indexSize);
		TriStrip (VertexFormat* vformat, VertexBuffer* vbuffer,
			IndexBuffer* ibuffer);

		virtual ~TriStrip ();

		void CalIndexs (int indexSize=2);

		virtual int GetNumTriangles () const;
		virtual bool GetTriangle (int i, int& v0, int& v1, int& v2) const;
	};

	PX2_REGISTER_STREAM(TriStrip);
	typedef Pointer0<TriStrip> TriStripPtr;

}

#endif

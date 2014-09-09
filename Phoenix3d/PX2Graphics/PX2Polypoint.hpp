/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Polypoint.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2POLYPOINT_HPP
#define PX2POLYPOINT_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Renderable.hpp"

namespace PX2
{
	
	/// ����ͼ�ε���
	class Polypoint : public Renderable
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(Polypoint);

	public:
		Polypoint (VertexFormat* vformat, VertexBuffer* vbuffer);
		virtual ~Polypoint ();

		int GetMaxNumPoints () const;
		void SetNumPoints (int numPoints);
		inline int GetNumPoints () const;

	protected:
		int mNumPoints;
	};

	PX2_REGISTER_STREAM(Polypoint);
	typedef Pointer0<Polypoint> PolypointPtr;
#include "PX2Polypoint.inl"

}

#endif

/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2WMatrixConstant.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2DEPTHPROPERTY_HPP
#define PX2DEPTHPROPERTY_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Object.hpp"

namespace PX2
{

	class DepthProperty : public Object
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(DepthProperty);

	public:
		DepthProperty ();
		virtual ~DepthProperty ();

		enum CompareMode
		{
			CM_NEVER,
			CM_LESS,
			CM_EQUAL,
			CM_LEQUAL,
			CM_GREATER,
			CM_NOTEQUAL,
			CM_GEQUAL,
			CM_ALWAYS,
			CM_QUANTITY
		};

		bool Enabled;         //< default: true
		bool Writable;        //< default: true
		CompareMode Compare;  //< default: CM_LEQUAL
	};

	PX2_REGISTER_STREAM(DepthProperty);
	typedef Pointer0<DepthProperty> DepthPropertyPtr;

}

#endif
/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2AlphaProperty.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2ALPHAPROPERTY_HPP
#define PX2ALPHAPROPERTY_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Object.hpp"
#include "PX2Float4.hpp"

namespace PX2
{

	class AlphaProperty : public Object
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(AlphaProperty);

	public:
		AlphaProperty ();
		virtual ~AlphaProperty ();

		enum SrcBlendMode
		{
			SBM_ZERO,
			SBM_ONE,
			SBM_DST_COLOR,
			SBM_ONE_MINUS_DST_COLOR,
			SBM_SRC_ALPHA,
			SBM_ONE_MINUS_SRC_ALPHA,
			SBM_SRC_COLOR,
			SBM_ONE_MINUS_SRC_COLOR,
			SBM_DST_ALPHA,
			SBM_ONE_MINUS_DST_ALPHA,
			SBM_SRC_ALPHA_SATURATE,
			SBM_CONSTANT_COLOR,
			SBM_ONE_MINUS_CONSTANT_COLOR,
			SBM_CONSTANT_ALPHA,
			SBM_ONE_MINUS_CONSTANT_ALPHA,
			SBM_QUANTITY
		};

		enum DstBlendMode
		{
			DBM_ZERO,
			DBM_ONE,
			DBM_SRC_COLOR,
			DBM_ONE_MINUS_SRC_COLOR,
			DBM_SRC_ALPHA,
			DBM_ONE_MINUS_SRC_ALPHA,
			DBM_DST_ALPHA,
			DBM_ONE_MINUS_DST_ALPHA,
			DBM_DST_COLOR,
			DBM_ONE_MINUS_DST_COLOR,
			DBM_CONSTANT_COLOR,
			DBM_ONE_MINUS_CONSTANT_COLOR,
			DBM_CONSTANT_ALPHA,
			DBM_ONE_MINUS_CONSTANT_ALPHA,
			DBM_QUANTITY
		};

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

		bool BlendEnabled;      //< default: false
		SrcBlendMode SrcBlend;  //< default: SBM_SRC_ALPHA
		DstBlendMode DstBlend;  //< default: DBM_ONE_MINUS_SRC_ALPHA
		bool CompareEnabled;    //< default: false
		CompareMode Compare;    //< default: CM_ALWAYS
		float Reference;        //< default: 0, always in [0,1]
		Float4 ConstantColor;   //< default: (0,0,0,0)
	};

	PX2_REGISTER_STREAM(AlphaProperty);
	typedef Pointer0<AlphaProperty> AlphaPropertyPtr;

}

#endif

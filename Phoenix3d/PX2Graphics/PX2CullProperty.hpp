/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2CullProperty.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2CULLPROPERTY_HPP
#define PX2CULLPROPERTY_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Object.hpp"

namespace PX2
{

	class CullProperty : public Object
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(CullProperty);

	public:
		CullProperty ();
		virtual ~CullProperty ();

		bool Enabled;   //< default: true
		bool CCWOrder;  //< default: true
	};

	PX2_REGISTER_STREAM(CullProperty);
	typedef Pointer0<CullProperty> CullPropertyPtr;

}

#endif

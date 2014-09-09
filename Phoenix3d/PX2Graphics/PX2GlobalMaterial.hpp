/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2GlobalMaterial.hpp
*
* �汾		:	1.0 (2011/01/31)
*
* ����		��	more
*
*/

#ifndef PX2GLOBALEFFECT_HPP
#define PX2GLOBALEFFECT_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Object.hpp"
#include "PX2Renderer.hpp"
#include "PX2VisibleSet.hpp"

namespace PX2
{

	class GlobalMaterial : public Object
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(GlobalMaterial);

	protected:
		GlobalMaterial ();
	public:
		virtual ~GlobalMaterial ();

		// ��globalMaterialָ�벻Ϊ��ʱ�����������Renderer::Draw(visibleSet,
		// globalMaterial)���á�
		virtual void Draw (Renderer* renderer, const VisibleSet& visibleSet) = 0;
	};

	PX2_REGISTER_STREAM(GlobalMaterial);
	typedef Pointer0<GlobalMaterial> GlobalMaterialPtr;

}

#endif

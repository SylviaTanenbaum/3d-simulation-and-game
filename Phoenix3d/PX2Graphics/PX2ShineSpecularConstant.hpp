/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2ShineSpecularConstant.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2MATERIALSPECULARCONSTANT_HPP
#define PX2MATERIALSPECULARCONSTANT_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2ShaderFloat.hpp"
#include "PX2Shine.hpp"

namespace PX2
{

	class ShineSpecularConstant : public ShaderFloat
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(ShineSpecularConstant);

	public:
		ShineSpecularConstant (Shine* shine);
		virtual ~ShineSpecularConstant ();

		Shine* GetShine ();

		virtual void Update (const Renderable* renderable, const Camera* camera);

	protected:
		ShinePtr mShine;
	};

	PX2_REGISTER_STREAM(ShineSpecularConstant);
	typedef Pointer0<ShineSpecularConstant> ShineSpecularConstantPtr;

}

#endif

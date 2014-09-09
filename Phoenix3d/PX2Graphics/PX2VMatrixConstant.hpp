/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2VMatrixConstant.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2VMATRIXCONSTANT_HPP
#define PX2VMATRIXCONSTANT_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2ShaderFloat.hpp"

namespace PX2
{

	class VMatrixConstant : public ShaderFloat
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(VMatrixConstant);

	public:
		VMatrixConstant ();
		virtual ~VMatrixConstant ();

		virtual void Update (const Renderable* renderable, const Camera* camera);
	};

	PX2_REGISTER_STREAM(VMatrixConstant);
	typedef Pointer0<VMatrixConstant> VMatrixConstantPtr;

}

#endif
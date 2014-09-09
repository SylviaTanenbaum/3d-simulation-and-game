/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2CameraWorldPositionConstant.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2CAMERAWORLDPOSITIONCONSTANT_HPP
#define PX2CAMERAWORLDPOSITIONCONSTANT_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2ShaderFloat.hpp"

namespace PX2
{

	class CameraWorldPositionConstant : public ShaderFloat
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(CameraWorldPositionConstant);

	public:
		CameraWorldPositionConstant ();
		virtual ~CameraWorldPositionConstant ();

		virtual void Update (const Renderable* renderable, const Camera* camera);
	};

	PX2_REGISTER_STREAM(CameraWorldPositionConstant);
	typedef Pointer0<CameraWorldPositionConstant> CameraWorldPositionConstantPtr;

}

#endif

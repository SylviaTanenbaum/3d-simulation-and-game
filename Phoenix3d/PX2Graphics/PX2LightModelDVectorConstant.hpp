/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2LightModelDVectorConstant.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2LIGHTMODELDVECTORCONSTANT_HPP
#define PX2LIGHTMODELDVECTORCONSTANT_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2ShaderFloat.hpp"
#include "PX2Light.hpp"

namespace PX2
{

	class LightModelDVectorConstant : public ShaderFloat
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(LightModelDVectorConstant);

	public:
		LightModelDVectorConstant (Light* light);
		virtual ~LightModelDVectorConstant ();

		void SetLight (Light *light);
		Light* GetLight ();

		virtual void Update (const Renderable* renderable, const Camera* camera);

	protected:
		LightPtr mLight;
	};

	PX2_REGISTER_STREAM(LightModelDVectorConstant);
	typedef Pointer0<LightModelDVectorConstant> LightModelDVectorConstantPtr;

}

#endif
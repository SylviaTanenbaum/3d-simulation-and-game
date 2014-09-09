/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2LightSpecularConstant.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2LIGHTSPECULARCONSTANT_HPP
#define PX2LIGHTSPECULARCONSTANT_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2ShaderFloat.hpp"
#include "PX2Light.hpp"

namespace PX2
{

	class LightSpecularConstant : public ShaderFloat
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(LightSpecularConstant);

	public:
		LightSpecularConstant (Light* light);
		virtual ~LightSpecularConstant ();

		void SetLight (Light *light);
		Light* GetLight ();

		virtual void Update (const Renderable* renderable, const Camera* camera);

	protected:
		LightPtr mLight;
	};

	PX2_REGISTER_STREAM(LightSpecularConstant);
	typedef Pointer0<LightSpecularConstant> LightSpecularConstantPtr;

}

#endif

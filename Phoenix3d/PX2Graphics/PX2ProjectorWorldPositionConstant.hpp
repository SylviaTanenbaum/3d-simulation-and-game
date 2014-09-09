/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2ProjectorWorldPositionConstant.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2PROJECTORWORLDPOSITIONCONSTANT_HPP
#define PX2PROJECTORWORLDPOSITIONCONSTANT_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Projector.hpp"
#include "PX2ShaderFloat.hpp"

namespace PX2
{

	class ProjectorWorldPositionConstant : public ShaderFloat
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(ProjectorWorldPositionConstant);

	public:
		ProjectorWorldPositionConstant (Projector* projector);
		virtual ~ProjectorWorldPositionConstant ();

		Projector* GetProjector ();

		virtual void Update (const Renderable* renderable, const Camera* camera);

	protected:
		ProjectorPtr mProjector;
	};

	PX2_REGISTER_STREAM(ProjectorWorldPositionConstant);
	typedef Pointer0<ProjectorWorldPositionConstant>
		ProjectorWorldPositionConstantPtr;

}

#endif
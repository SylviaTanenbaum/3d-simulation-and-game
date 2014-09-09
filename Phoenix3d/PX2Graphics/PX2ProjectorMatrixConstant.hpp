/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2ProjectorMatrixConstant.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2PROJECTORMATRIXCONSTANT_HPP
#define PX2PROJECTORMATRIXCONSTANT_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Projector.hpp"
#include "PX2ShaderFloat.hpp"

namespace PX2
{

	class ProjectorMatrixConstant : public ShaderFloat
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(ProjectorMatrixConstant);

	public:
		// Construction and destruction.  Set bsMatrix to 0 for the
		// bias-scale matrix that maps y' = (1-y)/2.  Set bsMatrix to 1 for the
		// bias-scale matrix that maps y' = (1-y)/2.
		ProjectorMatrixConstant (Projector* projector, bool biased,
			int bsMatrix);
		virtual ~ProjectorMatrixConstant ();

		Projector* GetProjector ();

		virtual void Update (const Renderable* renderable, const Camera* camera);

	protected:
		ProjectorMatrixConstant () {};

		ProjectorPtr mProjector;
		bool mBiased;
		int mBSMatrix;
	};

	PX2_REGISTER_STREAM(ProjectorMatrixConstant);
	typedef Pointer0<ProjectorMatrixConstant> ProjectorMatrixConstantPtr;

}

#endif
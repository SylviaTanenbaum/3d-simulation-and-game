/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Projector.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2PROJECTOR_HPP
#define PX2PROJECTOR_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Camera.hpp"

namespace PX2
{
	
	/// ͶӰ����
	/**
	* ������CameraΨһ�����ǣ�����������ض���������͡�
	*/
	class Projector : public Camera
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(Projector);

	public:
		Projector (DepthType depthType, bool isPerspective = true);
		virtual ~Projector ();

		// The 0-index matrix maps x' = (1+x)/2 and y' = (1-y)/2.  The
		// 1-index matrix maps x' = (1+x)/2 and y' = (1+y)/2.
		static const HMatrix BiasScaleMatrix[2];
	};

	PX2_REGISTER_STREAM(Projector);
	typedef Pointer0<Projector> ProjectorPtr;

}

#endif
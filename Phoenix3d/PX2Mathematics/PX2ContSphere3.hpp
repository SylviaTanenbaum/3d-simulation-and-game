/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2ContSphere3.hpp
*
* �汾		:	1.0 (2011/01/30)
*
* ����		��	more
*
*/

#ifndef PX2CONTSPHERE3_HPP
#define PX2CONTSPHERE3_HPP

#include "PX2MathematicsPre.hpp"
#include "PX2Sphere3.hpp"

namespace PX2
{

	// ���ȼ���������AABB��Χ�У�Ȼ�����AABB�����ΰ�Χ��
	template <typename Real> 
		Sphere3<Real> ContSphereOfAABB (int numPoints, const Vector3<Real>* points);

	// �����������С��Χ��
	template <typename Real> 
		Sphere3<Real> ContSphereAverage (int numPoints, const Vector3<Real>* points);

	// �����Ƿ�������
	template <typename Real> 
		bool InSphere (const Vector3<Real>& point, const Sphere3<Real>& sphere);

	// �������ں�
	template <typename Real> 
		Sphere3<Real> MergeSpheres (const Sphere3<Real>& sphere0,
		const Sphere3<Real>& sphere1);

}

#endif

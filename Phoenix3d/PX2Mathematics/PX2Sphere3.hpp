/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Sphere3.hpp
*
* �汾		:	1.0 (2011/06/05)
*
* ����		��	more
*
*/

#ifndef PX2SPHERE3_HPP
#define PX2SPHERE3_HPP

#include "PX2MathematicsPre.hpp"
#include "PX2Vector3.hpp"

namespace PX2
{

	template <typename Real>
	class Sphere3
	{
	public:
		Sphere3 ();  //< δ��ʼ��
		~Sphere3 ();

		Sphere3 (const Vector3<Real>& center, Real radius);

		Vector3<Real> Center;
		Real Radius;
	};

#include "PX2Sphere3.inl"

	typedef Sphere3<float> Sphere3f;
	typedef Sphere3<double> Sphere3d;

}

#endif
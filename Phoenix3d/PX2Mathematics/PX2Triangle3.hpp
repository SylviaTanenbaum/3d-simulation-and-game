/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Triangle3.hpp
*
* �汾		:	1.0 (2011/06/05)
*
* ����		��	more
*
*/

#ifndef PX2TRIANGLE3_HPP
#define PX2TRIANGLE3_HPP

#include "PX2MathematicsPre.hpp"
#include "PX2Vector3.hpp"

namespace PX2
{

	/// ��άģ����������
	/** 
	* ��������һ�������������V0,V1,V2��
	*/
	template <typename Real>
	class Triangle3
	{
	public:
		Triangle3 ();  //< δ��ʼ��
		~Triangle3 ();

		Triangle3 (const Vector3<Real>& v0, const Vector3<Real>& v1,
			const Vector3<Real>& v2);

		Triangle3 (const Vector3<Real> vertex[3]);

		/// ��Q�������εľ���
		Real DistanceTo (const Vector3<Real>& q) const;

		Vector3<Real> V[3];
	};

#include "PX2Triangle3.inl"

	typedef Triangle3<float> Triangle3f;
	typedef Triangle3<double> Triangle3d;

}

#endif
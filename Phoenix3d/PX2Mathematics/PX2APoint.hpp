/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2APoint.hpp
*
* �汾		:	1.0 (2011/01/30)
*
* ����		��	more
*
*/

#ifndef PX2APOINT_HPP
#define PX2APOINT_HPP

#include "PX2MathematicsPre.hpp"
#include "PX2AVector.hpp"

namespace PX2
{

	/// ������ࣨaffine point��
	class APoint : public HPoint
	{
	public:
		APoint ();  //< default (0,0,0,1)
		APoint (const APoint& pnt);
		APoint (float x, float y, float z);
		APoint (const Float3& tuple);
		APoint (const Vector3f& pnt);
		~APoint ();

		// ��ʽת��
		inline operator const Float3& () const;
		inline operator Float3& ();
		inline operator const Vector3f& () const;
		inline operator Vector3f& ();

		// ��ֵ
		APoint& operator= (const APoint& pnt);

		// Arithmetic operations supported by affine algebra.

		// ���ȥһ���㣬�õ�һ��������
		AVector operator- (const APoint& pnt) const;

		// �����һ�������õ�����һ����
		APoint operator+ (const AVector& vec) const;
		APoint operator- (const AVector& vec) const;
		APoint& operator+= (const AVector& vec);
		APoint& operator-= (const AVector& vec);

		// �ڷ�����ѧ�У����㡱�ǲ����Ա��������Ӽ�����ġ�Ȼ��Ϊ�˼�����Ҫ��
		// �����֧�֡�

		APoint operator+ (const APoint& pnt) const;
		APoint operator* (float scalar) const;
		APoint operator/ (float scalar) const;
		friend APoint operator* (float scalar, const APoint& pnt);
		APoint& operator+= (const APoint& pnt);
		APoint& operator-= (const APoint& pnt);
		APoint& operator*= (float scalar);
		APoint& operator/= (float scalar);
		APoint operator- () const;

		/// ����������
		/**
		* �ڷ�����ѧ�У��������������ǲ�����ġ�Ȼ���ڴ�����ƽ���������ʱ��
		* �ǳ�����ġ�ƽ�����ʽΪDot(N,X-P) = 0��N�Ƿ���������P��ƽ����һ�㣬
		* X��ƽ���ϵ�����㣬X-P��һ��������ƽ�����ʽ����ת��Ϊ
		* Dot(N,X) = Dot(N,P)����������Ϸ�����ѧ����ʽ������������Ҫ����
		* Dot(N,P)���ں����У�w�����ԣ�APoint������һ����������
		*/
		float Dot (const AVector& vec) const;

		// �ض�ֵ
		static const APoint ORIGIN;  // (0,0,0,1)
	};

#include "PX2APoint.inl"

}

#endif

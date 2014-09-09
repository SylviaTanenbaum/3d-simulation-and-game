/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2BitHacks.hpp
*
* �汾		:	1.0 (2011/01/31)
*
* ����		��	more
*
*/

#ifndef PX2BITHACKS_HPP
#define PX2BITHACKS_HPP

#include "PX2MathematicsPre.hpp"

namespace PX2
{

	bool IsPowerOfTwo (unsigned int value);
	bool IsPowerOfTwo (int value);

	unsigned int Log2OfPowerOfTwo (unsigned int powerOfTwo);
	int Log2OfPowerOfTwo (int powerOfTwo);

	/// ���ٽ�������[0,1]��Χ�ڵ�32bit�ĸ�����F��ת����������[0,2^P-1]��32bit��
	// ����I��value��ʾF��power��ʾP������ֵ��ʾI��
	inline int ScaledFloatToInt (float value, int power);

#include "PX2BitHacks.inl"

}

#endif

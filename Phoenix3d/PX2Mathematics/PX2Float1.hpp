/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Float1.hpp
*
* �汾		:	1.0 (2011/01/30)
*
* ����		��	more
*
*/

#ifndef PX2FLOAT1_HPP
#define PX2FLOAT1_HPP

#include "PX2MathematicsPre.hpp"
#include "PX2Tuple.hpp"

namespace PX2
{

	class Float1 : public Tuple<1,float>
	{
	public:
		Float1 ();   //< δ��ʼ��
		~Float1 ();  // hides ~Tuple<1,float>
		Float1 (float f0);
		Float1 (const Float1& tuple);

		// ��ֵ
		Float1& operator= (const Float1& tuple);
	};

}

#endif

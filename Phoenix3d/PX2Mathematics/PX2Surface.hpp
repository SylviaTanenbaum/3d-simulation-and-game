/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Surface.hpp
*
* �汾		:	1.0 (2011/09/19)
*
* ����		��	more
*
*/

#ifndef PX2SURFACE_HPP
#define PX2SURFACE_HPP

#include "PX2MathematicsPre.hpp"

namespace PX2
{

	template <typename Real>
	class Surface
	{
	public:
		virtual ~Surface ();

	protected:
		Surface ();
	};

	typedef Surface<float> Surfacef;
	typedef Surface<double> Surfaced;

}

#endif
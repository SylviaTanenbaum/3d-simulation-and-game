/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2FloatArray.hpp
*
* �汾		:	1.0 (2011/02/02)
*
* ����		��	more
*
*/

#ifndef PX2FLOATARRAY_HPP
#define PX2FLOATARRAY_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Object.hpp"

namespace PX2
{

	class FloatArray : public Object
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(FloatArray);

	public:
		FloatArray (int numElements = 0, float* elements = 0);
		virtual ~FloatArray ();

		// ��Ա����
		inline int GetNumElements () const;
		inline float* GetData () const;
		inline operator const float* () const;
		inline operator float* ();
		inline const float& operator[] (int i) const;
		inline float& operator[] (int i);

	protected:
		int mNumElements;
		float* mElements;
	};

	PX2_REGISTER_STREAM(FloatArray);
	typedef Pointer0<FloatArray> FloatArrayPtr;
#include "PX2FloatArray.inl"

}

#endif
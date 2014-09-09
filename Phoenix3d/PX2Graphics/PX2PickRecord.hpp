/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2PickRecord.hpp
*
* �汾		:	1.0 (2011/06/05)
*
* ����		��	more
*
*/

#ifndef PX2PICKRECORD_HPP
#define PX2PICKRECORD_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Movable.hpp"

namespace PX2
{

	/// �ü������¼��
	class PickRecord
	{
	public:
		PickRecord ();
		~PickRecord ();

		// ����ѡ��֧��
		inline bool operator== (const PickRecord& record) const;
		inline bool operator!= (const PickRecord& record) const;
		inline bool operator<  (const PickRecord& record) const;
		inline bool operator<= (const PickRecord& record) const;
		inline bool operator>  (const PickRecord& record) const;
		inline bool operator>= (const PickRecord& record) const;

		// �ཻ������
		MovablePtr Intersected;

		// ����P + t*D�е�����Ԫ������T������t�ı�ʾ��
		float T;

		// �������ཻ��������
		int Triangle;

		// ��������ϵ��ѡ���������궼������[0,1]�ڣ�
		// ����Bary[0] + Bary[1] + Bary[2] = 1��
		float Bary[3];
	};

#include "PX2PickRecord.inl"

}

#endif

/*
* Phoenix 3D ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Mutex.hpp
*
* �汾		:	1.0 (2011/01/30)
*
* ����		��	more
*
*/

#ifndef PX2MUTEX_HPP
#define PX2MUTEX_HPP

#include "PX2CorePre.hpp"
#include "PX2MutexType.hpp"

namespace PX2
{
	
	/// �߳�����
	class Mutex
	{
	public:
		Mutex (bool isRecursive=true);
		~Mutex ();

		void Enter ();
		void Leave ();

	private:
		bool mIsRecursive;
		MutexType mMutex;
	};

}
#endif
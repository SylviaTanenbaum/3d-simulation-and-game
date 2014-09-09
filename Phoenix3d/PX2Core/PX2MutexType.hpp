/*
* Phoenix 3D ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2MutexType.hpp
*
* �汾		:	1.0 (2011/01/29)
*
* ����		��	more
*
*/

#ifndef PX2MUTEXTYPE_HPP
#define PX2MUTEXTYPE_HPP

#include "PX2CorePre.hpp"

#if (defined(_WIN32) || defined(WIN32)) && !defined(PX2_USE_PTHREAD)
//----------------------------------------------------------------------------
// ��Windows�У�Mutex��һ��HANDLE����Ҫ����<windows.h>�������ᱩ¶����
// Windows�ӿڡ�����������void*����HANDLE��
//----------------------------------------------------------------------------
namespace PX2
{
	typedef void* MutexType;
}
//----------------------------------------------------------------------------
#elif defined(PX2_USE_PTHREAD)
//----------------------------------------------------------------------------
// ��Linux/Apple�У�pthread.h���������ԭʼ�������ݣ�����pthread.h���ᱩ¶
// ����Ľӿڡ�
//----------------------------------------------------------------------------
#include <pthread.h>
namespace PX2
{
	typedef struct
	{
		pthread_mutexattr_t Attribute;
		pthread_mutex_t Mutex;
	}
	MutexType;
}
#else
//----------------------------------------------------------------------------
// ����ƽ̨���߳�û��֧��
//----------------------------------------------------------------------------
#error Other platforms not yet implemented.
#endif

#endif

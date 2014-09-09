/*
*
* �ļ�����	��	PX2CorePre.hpp
*
*/

#ifndef PX2COREPRE_HPP
#define PX2COREPRE_HPP

//----------------------------------------------------------------------------
// ƽ̨��Ϣ.����ĺ��ƽ̨���п���.
// _WIN32 or WIN32  :  Microsoft Windows
// __APPLE__        :  Macintosh OS X
// __LINUX__        :  Linux
// __ANDROID__		:  Android
// __IOS__          :  IOS
// __MARMALADE__    :  Marmalade
//----------------------------------------------------------------------------
// Microsoft Windows
//----------------------------------------------------------------------------
#if defined(_WIN32) || defined(WIN32)

#ifndef _WIN32
#define _WIN32
#endif

#ifndef WIN32
#define WIN32
#endif

#define PX2_LITTLE_ENDIAN

#if defined(_MSC_VER)

// MSVC6�汾Ϊ12.00��MSVC7.0Ϊ13.00�� MSVC7.1Ϊ13.10��MSVC8.0Ϊ14.00��MSVC9.0
// Ϊ15.00��MSVC10.0Ϊ16.00��ǰ֧��MSVC8.0������ڰ汾.
#if _MSC_VER < 1400
#error ��Ҫʹ��MSVC 8.0���ߺ��ڰ汾
#elif _MSC_VER == 1500
#define PX2_USING_VC80
#elif _MSC_VER == 1600
#define PX2_USING_VC90
#else
#define PX2_USING_VC100
#endif

#pragma warning(disable : 4996)
#pragma warning(disable : 4311)

#include <climits>
#include <stdint.h>

#endif

#endif
//----------------------------------------------------------------------------
// Macintosh OS X
//----------------------------------------------------------------------------
#if defined(__APPLE__)

#if defined(__BIG_ENDIAN__)
#define PX2_BIG_ENDIAN
#else
#define PX2_LITTLE_ENDIAN
#endif

#define PX2_USE_PTHREAD
#endif
//----------------------------------------------------------------------------
// Linux
//----------------------------------------------------------------------------
#if defined(__LINUX__)

#include <inttypes.h>

#define PX2_LITTLE_ENDIAN
#define PX2_USE_PTHREAD
#endif
//----------------------------------------------------------------------------
// Android
//----------------------------------------------------------------------------
#if defined(__ANDROID__)

#include <inttypes.h>

#define PX2_LITTLE_ENDIAN
#define PX2_USE_PTHREAD
#endif
//----------------------------------------------------------------------------
// Marmalade
//----------------------------------------------------------------------------
#if defined(__MARMALADE__)

#define PX2_LITTLE_ENDIAN
#define PX2_USE_PTHREAD

#endif
//----------------------------------------------------------------------------
// IOS
//----------------------------------------------------------------------------
#if defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) || defined(__IPHONE_OS_VERSION_MIN_REQUIRED)

#ifndef __IOS__
#define __IOS__
#endif

#endif
//----------------------------------------------------------------------------



// ���ñ�׼ͷ�ļ�
#include <cassert>
#include <cctype>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#ifdef PX2_USE_PTHREAD
#include <pthread.h>
#endif

// STL
#include <algorithm>
#include <deque>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <bitset>

// int64
#define PX2_HAVE_INT64 1

// �û��Զ���ؼ���
#define public_internal public
#define protected_internal protected
#define private_internal private

// ��ֹδʹ�ñ��������ľ���.��Debug�»�������棬��Ҫ��������������棻
// ��Release�²����������.
#define PX2_UNUSED(variable) (void)variable

// ��Щ������������ֶ���ϵͳ.
// ע�⣺��ǰֻ��Microsoft Visual Studio������֧��.
#ifdef _DEBUG
	#if defined(WIN32) && defined(_MSC_VER)
		#define PX2_USE_ASSERT
		#ifdef PX2_USE_ASSERT
			#define PX2_USE_ASSERT_WRITE_TO_OUTPUT_WINDOW	// ������д����Դ���
			#define PX2_USE_ASSERT_WRITE_TO_MESSAGE_BOX		// ������д��MessageBox	
		#endif
	#endif
	#define PX2_USE_ASSERT_LOG_TO_FILE
#endif

// ���������ڴ����ĺ�
#ifdef _DEBUG
#ifndef __MARMALADE__
	#define PX2_USE_MEMORY // ʹ��Phoenix���ڴ�������
#endif
	#ifdef PX2_USE_MEMORY
		// ����main����֮ǰ�����ڴ������main�˳�֮���ͷ��ڴ棬������
		#define PX2_USE_MEMORY_ASSERT_ON_PREMAIN_POSTMAIN_OPERATIONS

		// ���ָ��ָ����ڴ治����Phoenix�ڴ������Ʒ���ģ��ڴ������
		// delete0��delete1��delete2����delete3�ĵ��û��������ԡ����ʹ�ô˺꣬
		// ��ʹ��c++��׼'delete'����'delete[]'�ͷ���'new','new[]'������ڴ档
		#define PX2_USE_MEMORY_ALLOW_DELETE_ON_FAILED_MAP_LOOKUP
	#endif
#endif

// FileIO��BufferIO
#ifdef _DEBUG
#define PX2_FILEIO_VALIDATE_OPERATION		// ����ļ���������ȷ��
#define PX2_BUFFERIO_VALIDATE_OPERATION		// ����ڴ��������ȷ��
#endif

#define SMART_POINTER_USEMUTEX

#endif
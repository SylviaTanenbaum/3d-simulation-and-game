/*
*
* �ļ�����	��	PX2Core.hpp
*
*/

#ifndef PX2CORE_HPP
#define PX2CORE_HPP

// Assert
#include "PX2Assert.hpp"

// Base
#include "PX2Ascii.hpp"

// DataTypes
#include "PX2Any.hpp"
#include "PX2Table.hpp"
#include "PX2Tuple.hpp"
#include "PX2DoubleChainList.hpp"
#include "PX2FString.hpp"
#include "PX2HashTable.hpp"
#include "PX2MsgQueue.hpp"
#include "PX2PriorityQueue.hpp"
#include "PX2MinHeap.hpp"

// Design
#include "PX2Noncopyable.hpp"
#include "PX2Visitor.hpp"
#include "PX2DesignUntity.hpp"

#if defined(_WIN32) || defined(WIN32)
#pragma warning(push) 
#pragma warning(disable : 4312)
#endif

#include "PX2Singleton.hpp"
#include "PX2Singleton1.hpp"

#if defined(_WIN32) || defined(WIN32)
#pragma warning(pop)
#endif

// Exception
#include "PX2Exception.hpp"

// Help
#include "PX2Environment.hpp"
#include "PX2Helps.hpp"
#include "PX2StringHelp.hpp"
#include "PX2Smoother.hpp"

// IO
#include "PX2BufferIO.hpp"
#include "PX2Endian.hpp"
#include "PX2Environment.hpp"
#include "PX2FileIO.hpp"

// Log
#include "PX2Log.hpp"
#include "PX2LogFileHandler.hpp"
#include "PX2LogOutputWindowHandler.hpp"

// Memory
#include "PX2FixMemoryPool.hpp"
#include "PX2Memory.hpp"
#include "PX2SmartPointer.hpp"
#include "PX2WeakPointer.hpp"
#include "PX2NotFreeObjectPool.hpp"
#include "PX2ObjectCopyPool.hpp"

// Props
#include "PX2PropModify.hpp"

// Os
#include "PX2System.hpp"

// Msg

// Base
#include "PX2Ascii.hpp"

// Notifications
#include "PX2Notification.hpp"
#include "PX2TimedNotificationQueue.hpp"

// ObjectSystems
#include "PX2InitTerm.hpp"
#include "PX2InStream.hpp"
#include "PX2Names.hpp"
#include "PX2Object.hpp"
#include "PX2Property.hpp"
#include "PX2OutStream.hpp"
#include "PX2Rtti.hpp"
#include "PX2Stream.hpp"

// Thread
#include "PX2Condition1.hpp"
#include "PX2ConditionType.hpp"
#include "PX2Eventt.hpp"
#include "PX2Mutex.hpp"
#include "PX2MutexType.hpp"
#include "PX2Runnable.hpp"
#include "PX2ScopedCS.hpp"
#include "PX2ScopedCSUN.hpp"
#include "PX2Semaphore.hpp"
#include "PX2Thread.hpp"
#include "PX2ThreadType.hpp"
#include "PX2ThreadServer.hpp"

// Time
#include "PX2DateTime.hpp"
#include "PX2Time.hpp"
#include "PX2Timespan.hpp"
#include "PX2Timestamp.hpp"
#include "PX2Timer.hpp"
#include "PX2TimerManager.hpp"

// Timer
#include "PX2Timer.hpp"
#include "PX2TimerManager.hpp"


#endif
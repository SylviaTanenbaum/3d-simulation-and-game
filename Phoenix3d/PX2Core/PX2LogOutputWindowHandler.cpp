/*
*
* �ļ�����	��	PX2LogFileHandler.cpp
*
*/

#include "PX2LogOutputWindowHandler.hpp"
#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#elif defined __ANDROID__
#include <android/log.h>
#elif defined __MARMALADE__
#include "s3e.h"
#endif
using namespace PX2;

//----------------------------------------------------------------------------
OutputWindowHandler::OutputWindowHandler (unsigned int levels)
	:
LogHandler(levels)
{
}
//----------------------------------------------------------------------------
OutputWindowHandler::~OutputWindowHandler ()
{
}
//----------------------------------------------------------------------------
void OutputWindowHandler::Handle (const LogBuffer *logBuffer,
	const char *timeStamp)
{
#if defined(_WIN32) || defined(WIN32)
	OutputDebugString(timeStamp);
	OutputDebugString((char*)logBuffer->Buffer);
#elif defined __ANDROID__
	__android_log_print(ANDROID_LOG_INFO, "phoenix3d.px2", timeStamp);
	__android_log_print(ANDROID_LOG_INFO, "phoenix3d.px2",
		(char*)logBuffer->Buffer);
#elif defined __MARMALADE__
	s3eDebugOutputString(timeStamp);
	s3eDebugOutputString(logBuffer->Buffer);
#endif
}
//----------------------------------------------------------------------------
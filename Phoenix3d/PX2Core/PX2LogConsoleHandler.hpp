/*
*
* �ļ�����	��	PX2LogConsoleHandler.hpp
*
*/

#ifndef PX2LOGCONSOLEHANDLER_HPP
#define PX2LOGCONSOLEHANDLER_HPP

#include "PX2Log.hpp"

namespace PX2
{

	class ConcoseLogHandler : public LogHandler
	{
	public:
		ConcoseLogHandler (unsigned int levels);
		virtual ~ConcoseLogHandler ();

		virtual void Handle (const LogBuffer *logBuffer,
			const char *timeStamp);
	};

}

#endif
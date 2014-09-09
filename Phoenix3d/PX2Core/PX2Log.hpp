/*
* Phoenix 3D ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Log.hpp
*
* �汾		:	1.0 (2011/01/30)
*
* ����		��	more
*
*/

#ifndef PX2LOG_HPP
#define PX2LOG_HPP

#include "PX2CorePre.hpp"
#include "PX2Singleton.hpp"
#include "PX2ThreadServer.hpp"
#include "PX2FixMemoryObject.hpp"
#include "PX2MsgQueue.hpp"

namespace PX2
{

	/// ��־����
	enum LogType
	{
		LT_INFO = 1,
		LT_ERROR = 2,
		LT_USER = 4,
		LT_SERVER_INFO = 8,
		LT_SERVER_ERROR = 16,
		LT_SERVER_USER = 32
	};

	class LogBuffer : public FixMemoryObject<LogBuffer>
	{
	public:
		LogBuffer (int isWChar=0);
		virtual ~LogBuffer ();

		static const int MaxLogLength = 512;
		int Level;
		int IsWChar;
		char Buffer[2*MaxLogLength];
	};

	class LogHandler
	{
	public:
		LogHandler (unsigned int levels);
		virtual ~LogHandler ();

		virtual void Handle (const LogBuffer *logBuffer,
			const char *timeStamp) = 0;

		unsigned int GetLevels ();

	protected:
		unsigned int mLevelFlags;
	};

	class Logger : public ThreadServer, public Singleton<Logger>
	{
	public:
		Logger ();
		virtual ~Logger ();

		void SetBlock (bool isBlock);
		bool IsBlock ();

		// LogHandler ��Ҫ��new0 ���䣬��CloseLogger������е�handler�����ͷ�
		bool AddHandler (LogHandler *handler);
		void RemoveHandler (LogHandler *handler);
		bool AddFileHandler (const char *filename, unsigned int levels);
		bool AddConsoleHandler (unsigned int levels);
		bool AddOutputWindowHandler (unsigned int levels);

		void StartLogger ();
		void CloseLogger();

		void LogMessage (int level, long line, const char* fileName, const char* format, ...);

		// for script
		void LogInfo (const std::string &tag, const std::string &info);
		void LogError (const std::string &tag, const std::string &info);
		void LogUser (const std::string &tag, const std::string &info);

		virtual void Run ();

	private:
		void CalcTimeStamp ();
		std::string _GetFileName (const std::string &path);
		std::wstring _GetFileName (const std::wstring &path);

		bool mIsBlock;
		
		bool mDoQuit;
		char mTimeBuff[64];

		std::vector<LogHandler*> mHandlers;
		MsgQueue<LogBuffer> mLogQueue;
	};

#define PX2_LOG_INFO(...)			Logger::GetSingleton().LogMessage(PX2::LT_INFO, __LINE__, __FILE__, ##__VA_ARGS__)
#define PX2_LOG_ERROR(...)			Logger::GetSingleton().LogMessage(PX2::LT_ERROR, __LINE__, __FILE__, ##__VA_ARGS__)
#define PX2_LOG_USER(...)			Logger::GetSingleton().LogMessage(PX2::LT_USER, __LINE__, __FILE__, ##__VA_ARGS__)
#define PX2_LOG_SERVER_INFO(...)	Logger::GetSingleton().LogMessage(PX2::LT_SERVER_INFO, __LINE__, __FILE__, ##__VA_ARGS__)
#define PX2_LOG_SERVER_ERROR(...)	Logger::GetSingleton().LogMessage(PX2::LT_SERVER_ERROR, __LINE__, __FILE__, ##__VA_ARGS__)
#define PX2_LOG_SERVER_USER(...)	Logger::GetSingleton().LogMessage(PX2::LT_SERVER_USER, __LINE__, __FILE__, ##__VA_ARGS__)

}

#endif

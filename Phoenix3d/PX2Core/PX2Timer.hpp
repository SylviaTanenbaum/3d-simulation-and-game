/*
*
* �ļ�����	��	PX2Timer.hpp
*
*/

#ifndef PX2TIMER_HPP
#define PX2TIMER_HPP

#include "PX2CorePre.hpp"
#include "PX2SmartPointer.hpp"
#include "PX2Timestamp.hpp"

namespace PX2
{
	
	class Object;

	class Timer
	{
	public:
		Timer ();
		virtual ~Timer ();

		// time_t ������ʱ��
		virtual bool OnTimer (double appTime) = 0;

public_internal:
		int mTimerID;
		float StartTime;
		double mInterval; // ��
		void *Action;
		void *UserData;
	};
	typedef Pointer0<Timer> TimerPtr;

}

#endif
/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2EventChannel.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2EVENTDATA_HPP
#define PX2EVENTDATA_HPP

#include "PX2EventSystemPre.hpp"

namespace PX2
{

	typedef Any EventData;

	template <class T>
	class EventDataTemplate
	{
	public:
		static EventData Set (const T& in)
		{
			return EventData(in);
		}

		static T Get (const EventData& data)
		{
			const T *val = Any_Cast<T>(&data);
			return *val;
		}
	};

	template <class T>
	void EventDataSet (EventData& data, const T& in)
	{
		data = EventDataTemplate<T>::Set(in);
	}

}

#endif
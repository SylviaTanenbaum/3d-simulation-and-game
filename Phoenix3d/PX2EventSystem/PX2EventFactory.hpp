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

#ifndef PX2EVENTFACTORY_HPP
#define PX2EVENTFACTORY_HPP

#include "PX2EventFactoryImplement.hpp"

namespace PX2
{
	
	/// �¼�����
	/**
	*
	*/
	class EventFactory
	{
	public:
		// ����
		static EventFactory &GetInstance ();
		static EventFactory* GetInstancePtr ();

		// �¼�
		Event* CreateEventX ();
		void DestoryEvent (Event* event);

		// �¼��ռ�
		void RegisterEventSpace (EventSpace* eventSpace);
		void UnRegisterEventSpace (const std::string &name);
		EventSpace* GetEventSpace (const std::string &name) const;
		EventSpace* FindEventSpace (Event* event) const;

	private:
		EventFactory ();
		~EventFactory ();

		EventFactoryImplement* mEventImplement;
	};

}

#endif
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

#ifndef PX2EVENTSPACE_HPP
#define PX2EVENTSPACE_HPP

#include "PX2Event.hpp"

namespace PX2
{

	/// �¼��ռ�
	class EventSpace
	{
	public:
		// �ռ�
		const std::string& GetName () const;
		int GetEventQuantity ();
		bool IsIn (Event* event) const;

		/// ��������
		Event* CreateEventX (Event::EventType eventType);
		Event::EventType UnCover (Event::EventType eventType);
		Event::EventType Cover (Event* event) const;

		/// event�ڱ������ռ��eventType�������Ƿ���ͬ
		bool IsEqual (Event* event, Event::EventType eventType) const;

	protected:
		EventSpace (const std::string &name, int iEventQuantity);
		virtual ~EventSpace ();

	private:
		friend class EventFactoryImplement;
		void SetSpace (int shift);

		class Space
		{
		public:
			Space ();
			~Space ();

			void Reset (int begin, int end); 

			Event::EventType Cover (Event* event) const;
			Event::EventType UnCover (Event::EventType eventType) const;

			bool IsIn (Event* event) const;
			bool IsEqual (Event* event, Event::EventType eventType) const; //< �¼��ڵ�ǰ�ռ�Cover���Ƿ��eventType���

		private:
			int mBegin;
			int mEnd;
		};

		Space mSpace;
		std::string mName;
		int mEventQuantity;
	};

#include "PX2EventSpace.inl"

}

#endif
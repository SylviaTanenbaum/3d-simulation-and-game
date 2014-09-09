/*
*
* �ļ�����	��	PX2Netable.hpp
*
*/

#ifndef PX2NETABLE_HPP
#define PX2NETABLE_HPP

#include "PX2GamePre.hpp"
#include "PX2Controlledable.hpp"
#include "PX2EventHandler.hpp"

namespace PX2
{
	class Netable;

	/**
	* ����ΪNetable�ĸ����࣬��ΪNetable�ĳ�Ա������֧�������������Ϣ���ܡ�ͨ
	* ����Ҫ��ʹ�ø��ࡣ
	*
	* DoEnter��DoExecute��DoLeave�ڲ�����Netable����Ӧ������
	* ���಻����Netable�ڴ�Ĺ���
	*/
	class NetableEventHandler : public EventHandler
	{
	public:
		NetableEventHandler (Netable *netable);
		virtual ~NetableEventHandler ();

		virtual void DoEnter ();
		virtual void DoExecute (Event *event);
		virtual void DoLeave ();

	protected:
		NetableEventHandler ();

		Netable *mNetable;
	};
	
	typedef Pointer0<NetableEventHandler> NetableEventHandlerPtr;

	/**
	* �����ڴ���Ķ��󣬾߱���Ϣ�Ĺ��ܡ�
	*/
	class Netable : public Controlledable
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(Netable);

	public:
		Netable ();
		virtual ~Netable ();

		EventHandler *GetEventHandler ();

		void ComeInToEventWorld ();
		void GoOutFromEventWorld ();
		bool IsInEventWorld ();

		// event
		virtual void DoEnter ();
		virtual void DoExecute (Event *event);
		virtual void DoLeave ();

	protected:
		NetableEventHandlerPtr mNetableEventHandler;
	};

	PX2_REGISTER_STREAM(Netable);
	typedef Pointer0<Netable> NetablePtr;
#include "PX2Netable.inl"

}

#endif
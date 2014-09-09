/*
*
* �ļ�����	��	PX2Controlledable.hpp
*
*/

#ifndef PX2CONTROLLEDOBJECT_HPP
#define PX2CONTROLLEDOBJECT_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Controller.hpp"

namespace PX2
{
	
	/// ����������
	/**
	* �Ӵ�������������а󶨿������Ĺ��ܡ�
	*/
	class Controlledable : public Object
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_PROPERTY;
		PX2_DECLARE_STREAM(Controlledable);

	protected:
		Controlledable ();
	public:
		virtual ~Controlledable ();

		void ResetPlay ();
		virtual void Play ();
		virtual bool IsPlaying () const;
		virtual void Stop ();
		virtual void Reset ();
		void SetSelfCtrled (bool selfCtrled);
		bool IsSelfCtrled () const;

		// ���ʿ��ƶ���Ŀ�����
		int GetNumControllers () const;
		Controller* GetController (int i) const;
		Controller *GetController (const std::string &name) const;
		bool HasController (Controller* controller);
		void AttachController (Controller* controller);
		void DetachController (Controller* controller);
		void DetachAllControllers ();
		void SortControls (); // �������ȼ��Ӵ�С����
		bool UpdateControllers (double applicationTime);

	private:
		bool mIsSelfCtrled;
		std::vector<ControllerPtr> mControllers;

		double mControlUpdateTimeLast;
		double mControlUpdateTimeMin;
	};

	PX2_REGISTER_STREAM(Controlledable);
	typedef Pointer0<Controlledable> ControlledablePtr;
#include "PX2Controlledable.inl"

}

#endif
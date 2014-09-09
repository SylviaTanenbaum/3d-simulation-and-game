/*
*
* �ļ�����	��	PX2Controller.hpp
*
*/

#ifndef PX2CONTROLLER_HPP
#define PX2CONTROLLER_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Object.hpp"

namespace PX2
{

	class Controller;
	typedef void (*CtrlPlayedCallback) (Controller *ctrl);

	class Controlledable;

	class Controller : public Object
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_PROPERTY;
		PX2_DECLARE_STREAM(Controller);

	protected:
		Controller ();
	public:
		virtual ~Controller ();

		// ���ȼ�Խ�ߣ�Խ��ǰ����
		void SetPriority (int priority);
		int GetPriority () const;

		// ����ϵͳ
		virtual void ResetPlay ();
		virtual void Play ();
		virtual bool IsPlaying () const;
		virtual void Stop ();
		virtual void Reset ();

		// ����ʱ��
		void SetMaxPlayTime (float time); // -1.0f forever
		float GetMaxPlayTime () const;
		void SetDelayPlayTime (float time);
		float GetDelayPlayTime () const;
		float GetPlayedTime () const;
		float GetPlayedTimeMinusDelay () const; // GetPlayedTime()-GetDelayPlayTime()

		// ���ſ���
		void SetPlayedDoDetach(bool doDetach);
		bool IsPlayedDoDetach () const;
		void SetPlayedCallback (CtrlPlayedCallback callback);
		CtrlPlayedCallback GetPlayedCallback ();

		// ��Ա����
		Controlledable* GetControlledable () const;
		double GetApplicationTime () const;

		// �������£�applicationTime���Ժ��������㵥λ��
		virtual bool Update (double applicationTime);
		bool IsTimeInited ();
		float GetElapsedTime () const; //< ���֡����ʱ�䣬��Update���ú����
		float GetRunTime () const;

		/// ������������
		enum RepeatType
		{
			RT_NONE,
			RT_CLAMP,
			RT_WRAP,
			RT_CYCLE
		};
		
		// ��Ա����
		RepeatType Repeat;  //< default = RT_NONE
		double MinTime;     //< default = 0
		double MaxTime;     //< default = 0
		double Phase;       //< default = 0
		double Frequency;   //< default = 1
		bool Active;        //< default = true

		virtual void OnAttach ();
		virtual void OnDetach ();

public_internal:
		/// ���ñ����ƵĶ���
		virtual void SetControlledable (Controlledable* object);
		static bool LessThan (const Controller *ctrl0, const Controller *ctrl1);

	protected:
		/// ��Ӧ�ó����ʱ��ת�����������ĵ�ǰʱ�䡣�������ڸ����Լ���ʱ���
		/// �õ��˺�����
		double GetControlTimeByRangeTime (double rangeTime);
		virtual void _Update (double applicationTime);

		/// ʹ��һ������ָ��ָ�򱻿��ƵĶ�����������controller��mObject֮��
		/// smartָ���ѭ������
		Controlledable* mObject;

		int mPriority;
		float mDelayPlayTime;
		float mMaxPlayTime;
		bool mIsPlayedDoDetach;
		bool mIsPlaying; // ����Ҫ����
		float mPlayedTime; // ����Ҫ����

		CtrlPlayedCallback mPlayedCallback;

		/// �Ժ�������λ��Ӧ�ó����¼�
		double mApplicationTime;
		double mLastApplicationTime;
		bool mIsTimeInited;
		double mInitedApplicationIime;
	};

	PX2_REGISTER_STREAM(Controller);
	typedef Pointer0<Controller> ControllerPtr;
#include "PX2Controller.inl"

}

#endif
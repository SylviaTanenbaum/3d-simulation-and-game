/*
*
* �ļ�����	��	PX2SkillCDTimeBuf.hpp
*
*/

#ifndef PX2SKILLCDTIMEBUF_HPP
#define PX2SKILLCDTIMEBUF_HPP

#include "PX2Buf.hpp"

namespace PX2
{

	class SkillCDTimeBuf : public Buf
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(SkillCDTimeBuf);

	public:
		SkillCDTimeBuf ();
		virtual ~SkillCDTimeBuf ();

		static SkillCDTimeBuf *Create ();

		virtual void Update (double appSeconds, double elapsedSeconds);

		enum Mode
		{
			M_IMMEDIATE,
			M_LASTING,
			M_MAX_MODE
		};
		void SetMode (Mode mode);
		Mode GetMode () const;

		// Ϊ�� ����CDʱ��ٷֱȣ�Ϊ������CDʱ��ٷֱ�
		void SetValue (float percent);
		float GetValue () const;

		// ģʽΪM_LASTING�����ʱ��,Ϊ<0ʱ����Ч��
		void SetLastingMaxTime (float lastingMaxTime);
		float GetLastingMaxTime () const;

		void SetSkillName (const std::string &skillName);
		const std::string &GetSkillName () const;

		virtual void OnAdded ();
		virtual void OnRemoved ();

	protected:
		Mode mMode;
		std::string mSkillName;
		float mValue;
		float mLastingMaxTime;
		float mMValue;

		float mLastingTimeUpdate;
	};

#include "PX2SkillCDTimeBuf.inl"
	PX2_REGISTER_STREAM(SkillCDTimeBuf);
	typedef Pointer0<SkillCDTimeBuf> SkillCDTimeBufPtr;

}

#endif
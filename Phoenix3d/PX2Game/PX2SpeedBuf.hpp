/*
*
* �ļ�����	��	PX2SpeedBuf.hpp
*
*/

#ifndef PX2SPEEDBUF_HPP
#define PX2SPEEDBUF_HPP

#include "PX2Buf.hpp"

namespace PX2
{

	class SpeedBuf : public Buf
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(SpeedBuf);

	public:
		SpeedBuf ();
		virtual ~SpeedBuf ();

		static SpeedBuf *Create ();

		virtual void Update (double appSeconds, double elapsedSeconds);

		enum Mode
		{
			M_IMMEDIATE,
			M_LASTING,
			M_DOSTOP,
			M_MAX_MODE
		};
		void SetMode (Mode mode);
		Mode GetMode () const;

		// Ϊ�����٣�Ϊ������
		void SetValue (float val);
		float GetValue () const;

		// ģʽΪM_LASTING�����ʱ��,Ϊ<0ʱ����Ч��
		void SetLastingMaxTime (float lastingMaxTime);
		float GetLastingMaxTime () const;

		virtual void OnAdded ();
		virtual void OnRemoved ();

	protected:
		Mode mMode;
		float mValue;
		float mLastingMaxTime;
		float mMValue;

		float mLastingTimeUpdate;
	};

#include "PX2SpeedBuf.inl"
	PX2_REGISTER_STREAM(SpeedBuf);
	typedef Pointer0<SpeedBuf> SpeedBufPtr;

}

#endif
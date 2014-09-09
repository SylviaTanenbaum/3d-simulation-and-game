/*
*
* �ļ�����	��	PX2InputPushTransformController.hpp
*
*/

#ifndef PX2INPUTPUSHTRANSFORMCONTROLLER_HPP
#define PX2INPUTPUSHTRANSFORMCONTROLLER_HPP

#include "PX2PushTransformController.hpp"
#include "PX2InputEventHandler.hpp"

namespace PX2
{

	typedef void (*TouchConvertCallback) (APoint &touchPos, int xPos, int yPos);
	
	class InputPushTransformController : public PushTransformController, public InputEventHandler
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(InputPushTransformController);

	public:
		InputPushTransformController ();
		virtual ~InputPushTransformController ();

		// ���������LockDir,�ᰴ��LockDir�ƶ�,Ĭ��ΪAVector::ZERO
		void SetLockDir (const AVector &dir);
		const AVector &GetLockDir () const;

		// ÿ�뻬����������룬����Push
		void SetPushTriggerSpeed (float speed);
		float GetPusTriggerSpeed () const;

		virtual void SetReleaseVelocity (const AVector &velocity);
		virtual void SetVelocity(const AVector &velocity);

		virtual void SetTransScope (const AVector &min,const AVector &max);		
		virtual void SetTransScopeSmall (const AVector &min, const AVector &max);
		virtual bool TransScope (APoint &pos);
		bool IsSmallTransScope ();
		AVector GetSmallTransDir ();

		virtual bool Update (double applicationTime);
		virtual void OnMoving (const AVector &dis);

		// ���Ӵ��ĵ�ת��ΪmPressedPos,mReleasedPos�ĺ���
		void SetTouchConvertCallback (TouchConvertCallback callback);
		TouchConvertCallback GetTouchConvertCallback () const;

		virtual bool TouchMoved (const InputEventData &data);
		virtual bool TouchPressed (const InputEventData &data);
		virtual bool TouchReleased (const InputEventData &data);
		virtual bool TouchCancelled (const InputEventData &data);

	protected:
		AVector mLockDir;
		float mPushTriggerSpeed;

		float mPressedTime;
		APoint mPressedPos;
		float mReleasedTime;
		APoint mReleasedPos;
		APoint mCurTouchPos;
		APoint mLastTouchPos;
		AVector mReleasedVec;

		AVector mMinPos; // TransScope
		AVector mMaxPos;
		AVector mMinPosSmall;
		AVector mMaxPosSmall;
		float mSideMoveLength;

		bool mIsPressedValid;

		TouchConvertCallback mConvertCallback;
	};

#include "PX2InputPushTransformController.inl"

	PX2_REGISTER_STREAM(InputPushTransformController);
	typedef Pointer0<InputPushTransformController> InputPushTransformControllerPtr;

}

#endif
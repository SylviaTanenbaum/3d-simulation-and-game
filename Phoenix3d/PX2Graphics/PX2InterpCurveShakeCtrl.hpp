/*
*
* �ļ�����	��	PX2InterpCurveShakeCtrl.hpp
*
*/

#ifndef PX2INTERPCURVESHAKECTRL_HPP
#define PX2INTERPCURVESHAKECTRL_HPP

#include "PX2Controller.hpp"
#include "PX2InterpCurveFloatController.hpp"

namespace PX2
{

	// һ���򵥵��𶯿ؼ�,��ʱ��¼�����巽λ,�Ӵ���ʱ��ԭ�����巽λ
	// ͨ���������ߵĵ�һ�������һ����Ĵ�С��Ϊ0
	class InterpCurveShakeController : public InterpCurveFloatController
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(InterpCurveShakeController);

	public:
		InterpCurveShakeController ();
		virtual ~InterpCurveShakeController ();

		enum ShakeRangeType
		{
			SRT_X,
			SRT_Y,
			SRT_Z,
			SRT_XY,
			SRT_YZ,
			SRT_XZ,
			SRT_XYZ,
			SRT_MAX_TYPE
		};
		void SetShakeRangeType (ShakeRangeType type);
		ShakeRangeType GetShakeRangeType ();

		virtual void OnAttach ();
		virtual void OnDetach ();

		virtual bool Update (double applicationTime);

	protected:
		virtual void _Update (double applicationTime);
		void ReCalcCurve ();

		ShakeRangeType mShakeRangeType;
		APoint mInitPos;
		InterpCurveFloat3 mPoses;
	};

#include "PX2InterpCurveShakeCtrl.inl"

	PX2_REGISTER_STREAM(InterpCurveShakeController);
	typedef Pointer0<InterpCurveShakeController> InterpCurveShakeControllerPtr;

}

#endif
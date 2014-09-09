/*
*
* �ļ�����	��	PX2InterpCurveFloatController.hpp
*
*/

#ifndef PX2INTERPCURVEFLOATCONTROLLER_HPP
#define PX2INTERPCURVEFLOATCONTROLLER_HPP

#include "PX2Controller.hpp"
#include "PX2InterpCurveController.hpp"

namespace PX2
{

	class InterpCurveFloatController : public InterpCurveController
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_PROPERTY;
		PX2_DECLARE_STREAM(InterpCurveFloatController);

	public:
		InterpCurveFloatController (float initValue=0.0f);
		virtual ~InterpCurveFloatController ();

		void SetInitValue (float val);
		const float &GetInitValue () const;

		const float &GetCurValueRaw () const;
		const float &GetCurValueRelatived () const;

	public:
		InterpCurveFloat mValues;

	protected:
		virtual void _Update (double applicationTime);

		float mInitValue;
		float mCurValueRaw; // ������Relative��ϵ��ֵ
		float mCurValueRelatived; // Update���µõ��ĵ�ǰֵ,����Ҫ����
	};

#include "PX2InterpCurveFloatController.inl"

	PX2_REGISTER_STREAM(InterpCurveFloatController);
	typedef Pointer0<InterpCurveFloatController> InterpCurveFloatControllerPtr;

}

#endif
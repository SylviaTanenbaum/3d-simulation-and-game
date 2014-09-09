/*
*
* �ļ�����	��	PX2InterpCurveTransCtrl.hpp
*
*/

#ifndef PX2INTERPCURVETRANSLATECTRL_HPP
#define PX2INTERPCURVETRANSLATECTRL_HPP

#include "PX2Controller.hpp"
#include "PX2InterpCurveFloat3Controller.hpp"

namespace PX2
{

	class InterpCurveTranslateController : public InterpCurveFloat3Controller
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(InterpCurveTranslateController);

	public:
		InterpCurveTranslateController ();
		virtual ~InterpCurveTranslateController ();

		virtual void Reset ();

		virtual void OnAttach ();
		virtual void OnDetach ();

	protected:
		virtual void _Update (double applicationTime);
	};

	PX2_REGISTER_STREAM(InterpCurveTranslateController);
	typedef Pointer0<InterpCurveTranslateController> InterpCurveTranslateControllerPtr;

}

#endif
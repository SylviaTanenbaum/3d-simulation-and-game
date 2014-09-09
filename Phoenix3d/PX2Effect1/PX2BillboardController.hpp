/*
*
* �ļ�����	��	PX2BillboardControl.hpp
*
*/

#ifndef PX2BILLBOARDCONTROL_HPP
#define PX2BILLBOARDCONTROL_HPP

#include "PX2EffectPre.hpp"
#include "PX2EffectableController.hpp"
#include "PX2EffectObject.hpp"

namespace PX2
{

	class BillboardController : public EffectableController
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(BillboardController);

	public:
		BillboardController ();
		~BillboardController ();

		virtual void Reset ();

		const EffectObject *GetBillboardObject () const;
		EffectObject *GetBillboardObject ();

		virtual bool Update (double applicationTime);

	protected:
		EffectObjectPtr mBillboardObject;
	};

#include "PX2BillboardController.inl"
	PX2_REGISTER_STREAM(BillboardController);
	typedef Pointer0<BillboardController> BillboardControllerPtr;

}

#endif
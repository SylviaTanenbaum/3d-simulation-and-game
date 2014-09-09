/*
*
* �ļ�����	��	PX2EffectModelController.hpp
*
*/

#ifndef PX2EFFECTMODELCONTROLLER_HPP
#define PX2EFFECTMODELCONTROLLER_HPP

#include "PX2EffectPre.hpp"
#include "PX2EffectableController.hpp"
#include "PX2EffectObject.hpp"

namespace PX2
{

	class EffectModelController : public EffectableController
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(EffectModelController);

	public:
		EffectModelController ();
		virtual ~EffectModelController ();

		virtual void Reset ();

		const EffectObject *GetEffectModelObject () const;

		virtual bool Update (double applicationTime);

	protected:
		EffectObjectPtr mEffectModelObject;
	};

#include "PX2EffectModelController.inl"
	PX2_REGISTER_STREAM(EffectModelController);
	typedef Pointer0<EffectModelController> EffectModelControllerPtr;

}

#endif
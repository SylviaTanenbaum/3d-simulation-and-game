/*
*
* �ļ�����	��	PX2InterpCurveTransCtrl.cpp
*
*/

#include "PX2InterpCurveTranslateCtrl.hpp"
#include "PX2Movable.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, InterpCurveFloat3Controller, InterpCurveTranslateController);
PX2_IMPLEMENT_STREAM(InterpCurveTranslateController);
PX2_IMPLEMENT_FACTORY(InterpCurveTranslateController);
PX2_IMPLEMENT_DEFAULT_NAMES(InterpCurveFloat3Controller, InterpCurveTranslateController);

//----------------------------------------------------------------------------
InterpCurveTranslateController::InterpCurveTranslateController ()
	:
InterpCurveFloat3Controller(Float3::ZERO)
{
	SetPriority(11);
}
//----------------------------------------------------------------------------
InterpCurveTranslateController::~InterpCurveTranslateController ()
{
}
//----------------------------------------------------------------------------
void InterpCurveTranslateController::Reset ()
{
	InterpCurveFloat3Controller::Reset();

	Movable* movable = StaticCast<Movable>(mObject);
	if (movable)
	{
		movable->LocalTransform.SetTranslate(mInitValue);
	}
}
//----------------------------------------------------------------------------
void InterpCurveTranslateController::_Update (double applicationTime)
{
	InterpCurveFloat3Controller::_Update(applicationTime);

	const Float3 &curValue = GetCurValueRelatived();
	
	Movable* movable = StaticCast<Movable>(mObject);
	if (movable)
	{
		movable->LocalTransform.SetTranslate(curValue);
	}
}
//----------------------------------------------------------------------------
void InterpCurveTranslateController::OnAttach ()
{
	if (IsAttachUpdateInit())
	{
		Movable* movable = StaticCast<Movable>(mObject);
		if (movable)
		{
			mInitValue = movable->LocalTransform.GetTranslate();
		}
	}
}
//----------------------------------------------------------------------------
void InterpCurveTranslateController::OnDetach ()
{
	if (IsDetachResetInit())
	{
		Movable* movable = StaticCast<Movable>(mObject);
		if (movable)
		{
			movable->LocalTransform.SetTranslate(mInitValue);
		}
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// �־û�
//----------------------------------------------------------------------------
InterpCurveTranslateController::InterpCurveTranslateController (LoadConstructor value)
	:
InterpCurveFloat3Controller(value)
{
}
//----------------------------------------------------------------------------
void InterpCurveTranslateController::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	InterpCurveFloat3Controller::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(InterpCurveTranslateController, source);
}
//----------------------------------------------------------------------------
void InterpCurveTranslateController::Link (InStream& source)
{
	InterpCurveFloat3Controller::Link(source);
}
//----------------------------------------------------------------------------
void InterpCurveTranslateController::PostLink ()
{
	InterpCurveFloat3Controller::PostLink();
}
//----------------------------------------------------------------------------
bool InterpCurveTranslateController::Register (OutStream& target) const
{
	return InterpCurveFloat3Controller::Register(target);
}
//----------------------------------------------------------------------------
void InterpCurveTranslateController::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	InterpCurveFloat3Controller::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(InterpCurveTranslateController, target);
}
//----------------------------------------------------------------------------
int InterpCurveTranslateController::GetStreamingSize (Stream &stream) const
{
	int size = InterpCurveFloat3Controller::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);
	return size;
}
//----------------------------------------------------------------------------
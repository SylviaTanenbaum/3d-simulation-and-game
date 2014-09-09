/*
*
* �ļ�����	��	PX2InterpCurveRotateCtrl.cpp
*
*/

#include "PX2InterpCurveRotateCtrl.hpp"
#include "PX2Movable.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, InterpCurveFloat3Controller, InterpCurveRotateController);
PX2_IMPLEMENT_STREAM(InterpCurveRotateController);
PX2_IMPLEMENT_FACTORY(InterpCurveRotateController);
PX2_IMPLEMENT_DEFAULT_NAMES(InterpCurveFloat3Controller, InterpCurveRotateController);

//----------------------------------------------------------------------------
InterpCurveRotateController::InterpCurveRotateController ()
	:
InterpCurveFloat3Controller(Float3::ZERO)
{
	SetPriority(12);
}
//----------------------------------------------------------------------------
InterpCurveRotateController::~InterpCurveRotateController ()
{
}
//----------------------------------------------------------------------------
void InterpCurveRotateController::_Update (double applicationTime)
{
	InterpCurveFloat3Controller::_Update(applicationTime);

	const Float3 &curValue = GetCurValueRelatived();

	Movable* movable = StaticCast<Movable>(mObject);
	if (movable)
	{
		movable->LocalTransform.SetRotate(Matrix3f().MakeEulerXYZ(curValue[0],
			curValue[1], curValue[2]));
	}
}
//----------------------------------------------------------------------------
void InterpCurveRotateController::OnAttach ()
{
	if (IsAttachUpdateInit())
	{
		Movable* movable = StaticCast<Movable>(mObject);
		if (movable)
		{
			Matrix3f mat = movable->LocalTransform.GetRotate();
			mat.ExtractEulerXYZ(mInitValue[0], mInitValue[1], mInitValue[2]);
		}
	}
}
//----------------------------------------------------------------------------
void InterpCurveRotateController::OnDetach ()
{
	if (IsDetachResetInit())
	{
		Movable* movable = StaticCast<Movable>(mObject);
		if (movable)
		{
			movable->LocalTransform.SetRotate(Matrix3f().MakeEulerXYZ(
				mInitValue[0],	mInitValue[1], mInitValue[2]));
		}
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// �־û�
//----------------------------------------------------------------------------
InterpCurveRotateController::InterpCurveRotateController (LoadConstructor value)
	:
InterpCurveFloat3Controller(value)
{
}
//----------------------------------------------------------------------------
void InterpCurveRotateController::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	InterpCurveFloat3Controller::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(InterpCurveRotateController, source);
}
//----------------------------------------------------------------------------
void InterpCurveRotateController::Link (InStream& source)
{
	InterpCurveFloat3Controller::Link(source);
}
//----------------------------------------------------------------------------
void InterpCurveRotateController::PostLink ()
{
	InterpCurveFloat3Controller::PostLink();
}
//----------------------------------------------------------------------------
bool InterpCurveRotateController::Register (OutStream& target) const
{
	return InterpCurveFloat3Controller::Register(target);
}
//----------------------------------------------------------------------------
void InterpCurveRotateController::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	InterpCurveFloat3Controller::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(InterpCurveRotateController, target);
}
//----------------------------------------------------------------------------
int InterpCurveRotateController::GetStreamingSize (Stream &stream) const
{
	int size = InterpCurveFloat3Controller::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);
	return size;
}
//----------------------------------------------------------------------------
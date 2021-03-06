/*
*
* 文件名称	：	PX2CameraShakeController.cpp
*
*/

#include "PX2EffectModelNodeController.hpp"
#include "PX2EffectModelNode.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, EffectableController, EffectModelNodeController);
PX2_IMPLEMENT_STREAM(EffectModelNodeController);
PX2_IMPLEMENT_FACTORY(EffectModelNodeController);
PX2_IMPLEMENT_DEFAULT_NAMES(EffectableController, EffectModelNodeController);

//----------------------------------------------------------------------------
EffectModelNodeController::EffectModelNodeController ()
{
}
//----------------------------------------------------------------------------
EffectModelNodeController::~EffectModelNodeController ()
{
}
//----------------------------------------------------------------------------
bool EffectModelNodeController::Update (double applicationTime)
{
	if (0.0f == applicationTime)
		return true;

	if (!EffectableController::Update(applicationTime))
	{
		return false;
	}

	EffectModelNode *emn = (EffectModelNode*)GetControlledable();
	float elapsedTime = GetElapsedTime();

	emn->UpdateModelNode((float)applicationTime, elapsedTime);

	return true;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化
//----------------------------------------------------------------------------
EffectModelNodeController::EffectModelNodeController (LoadConstructor value)
	:
EffectableController(value)
{
}
//----------------------------------------------------------------------------
void EffectModelNodeController::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	EffectableController::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(EffectModelNodeController, source);
}
//----------------------------------------------------------------------------
void EffectModelNodeController::Link (InStream& source)
{
	EffectableController::Link(source);
}
//----------------------------------------------------------------------------
void EffectModelNodeController::PostLink ()
{
	EffectableController::PostLink();
}
//----------------------------------------------------------------------------
bool EffectModelNodeController::Register (OutStream& target) const
{
	if (EffectableController::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EffectModelNodeController::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	EffectableController::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(EffectModelNodeController, target);
}
//----------------------------------------------------------------------------
int EffectModelNodeController::GetStreamingSize (Stream &stream) const
{
	int size = EffectableController::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	return size;
}
//----------------------------------------------------------------------------

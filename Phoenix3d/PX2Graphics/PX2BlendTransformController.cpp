/*
*
* �ļ�����	��	PX2BlendTransformController.cpp
*
*/

#include "PX2BlendTransformController.hpp"
#include "PX2HQuaternion.hpp"
#include "PX2Movable.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, TransformController, BlendTransformController);
PX2_IMPLEMENT_STREAM(BlendTransformController);
PX2_IMPLEMENT_FACTORY(BlendTransformController);

//----------------------------------------------------------------------------
BlendTransformController::BlendTransformController (
	TransformController* controller0, TransformController* controller1,
	bool rsMatrices, bool geometricRotation, bool geometricScale)
	:
TransformController(Transform::IDENTITY),
	mController0(controller0),
	mController1(controller1),
	mWeight(0.0f),
	mRSMatrices(rsMatrices),
	mGeometricRotation(geometricRotation),
	mGeometricScale(geometricScale)
{
}
//----------------------------------------------------------------------------
BlendTransformController::~BlendTransformController ()
{
}
//----------------------------------------------------------------------------
bool BlendTransformController::Update (double applicationTime)
{
	if (!Controller::Update(applicationTime))
	{
		return false;
	}

	if (mController0)
		mController0->Update(applicationTime);

	if (mController1)
		mController1->Update(applicationTime);

	if (mController0 && mController1)
	{
		const Transform& xfrm0 = mController0->GetTransform();
		const Transform& xfrm1 = mController1->GetTransform();
		float oneMinusWeight = 1.0f - mWeight;

		// Arithmetic blend of translations.
		const APoint& trn0 = xfrm0.GetTranslate();
		const APoint& trn1 = xfrm1.GetTranslate();
		APoint blendTrn = oneMinusWeight*trn0 + mWeight*trn1;
		mTransform.SetTranslate(blendTrn);

		if (mRSMatrices)
		{
			const HMatrix& rot0 = xfrm0.GetRotate();
			const HMatrix& rot1 = xfrm1.GetRotate();

			HQuaternion quat0(rot0), quat1(rot1);
			if (quat0.Dot(quat1) < 0.0f)
			{
				quat1 = -quat1;
			}

			APoint sca0 = xfrm0.GetScale();
			APoint sca1 = xfrm1.GetScale();
			HMatrix blendRot;
			HQuaternion blendQuat;
			APoint blendSca;

			if (mGeometricRotation)
			{
				blendQuat.Slerp(mWeight, quat0, quat1);
			}
			else
			{
				blendQuat = oneMinusWeight*quat0 + mWeight*quat1;
				blendQuat.Normalize();
			}
			blendQuat.ToRotationMatrix(blendRot);
			mTransform.SetRotate(blendRot);

			if (mGeometricScale)
			{
				for (int i = 0; i < 3; ++i)
				{
					float s0 = sca0[i];
					float s1 = sca1[i];
					if (s0 != 0.0f && s1 != 0.0f)
					{
						float sign0 = Mathf::Sign(s0);
						float sign1 = Mathf::Sign(s1);
						s0 = Mathf::FAbs(s0);
						s1 = Mathf::FAbs(s1);
						float pow0 = Mathf::Pow(s0, oneMinusWeight);
						float pow1 = Mathf::Pow(s1, mWeight);
						blendSca[i] = sign0*sign1*pow0*pow1;
					}
					else
					{
						blendSca[i] = 0.0f;
					}
				}
			}
			else
			{
				blendSca = oneMinusWeight*sca0 + mWeight*sca1;
			}
			mTransform.SetScale(blendSca);
		}
		else
		{
			// Arithemtic blend of matrices.
			const HMatrix& mat0 = xfrm0.GetMatrix();
			const HMatrix& mat1 = xfrm1.GetMatrix();
			HMatrix blendMat = oneMinusWeight*mat0 + mWeight*mat1;
			mTransform.SetMatrix(blendMat);
		}
	}

	Movable* mov = StaticCast<Movable>(mObject);
	mov->LocalTransform = mTransform;
	return true;
}
//----------------------------------------------------------------------------
void BlendTransformController::SetControlledable (Controlledable* object)
{
	TransformController::SetControlledable(object);

	mController0->SetControlledable(object);
	mController1->SetControlledable(object);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Name support.
//----------------------------------------------------------------------------
Object* BlendTransformController::GetObjectByName (const std::string& name)
{
	Object* found = TransformController::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	PX2_GET_OBJECT_BY_NAME(mController0, name, found);
	PX2_GET_OBJECT_BY_NAME(mController1, name, found);
	return 0;
}
//----------------------------------------------------------------------------
void BlendTransformController::GetAllObjectsByName (const std::string& name,
	std::vector<Object*>& objects)
{
	TransformController::GetAllObjectsByName(name, objects);

	PX2_GET_ALL_OBJECTS_BY_NAME(mController0, name, objects);
	PX2_GET_ALL_OBJECTS_BY_NAME(mController1, name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Streaming support.
//----------------------------------------------------------------------------
BlendTransformController::BlendTransformController (LoadConstructor value)
	:
TransformController(value),
	mWeight(0.0f),
	mRSMatrices(false),
	mGeometricRotation(false),
	mGeometricScale(false)
{
}
//----------------------------------------------------------------------------
void BlendTransformController::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	TransformController::Load(source);

	source.ReadPointer(mController0);
	source.ReadPointer(mController1);
	source.Read(mWeight);
	source.ReadBool(mRSMatrices);
	source.ReadBool(mGeometricRotation);
	source.ReadBool(mGeometricScale);

	PX2_END_DEBUG_STREAM_LOAD(BlendTransformController, source);
}
//----------------------------------------------------------------------------
void BlendTransformController::Link (InStream& source)
{
	TransformController::Link(source);

	source.ResolveLink(mController0);
	source.ResolveLink(mController1);
}
//----------------------------------------------------------------------------
void BlendTransformController::PostLink ()
{
	TransformController::PostLink();
}
//----------------------------------------------------------------------------
bool BlendTransformController::Register (OutStream& target) const
{
	if (TransformController::Register(target))
	{
		target.Register(mController0);
		target.Register(mController1);
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void BlendTransformController::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	TransformController::Save(target);

	target.WritePointer(mController0);
	target.WritePointer(mController1);
	target.Write(mWeight);
	target.WriteBool(mRSMatrices);
	target.WriteBool(mGeometricRotation);
	target.WriteBool(mGeometricScale);

	PX2_END_DEBUG_STREAM_SAVE(BlendTransformController, target);
}
//----------------------------------------------------------------------------
int BlendTransformController::GetStreamingSize (Stream &stream) const
{
	int size = TransformController::GetStreamingSize(stream);
	size += PX2_POINTERSIZE(mController0);
	size += PX2_POINTERSIZE(mController1);
	size += sizeof(mWeight);
	size += PX2_BOOLSIZE(mRSMatrices);
	size += PX2_BOOLSIZE(mGeometricRotation);
	size += PX2_BOOLSIZE(mGeometricScale);
	return size;
}
//----------------------------------------------------------------------------

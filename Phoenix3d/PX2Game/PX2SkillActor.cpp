/*
*
* �ļ�����	��	PX2SkillActor.cpp
*
*/

#include "PX2SkillActor.hpp"
#include "PX2EffectNode.hpp"
#include "PX2ResourceManager.hpp"
#include "PX2Scene.hpp"
#include "PX2DeletingManager.hpp"
#include "PX2Character.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, EffectActor, SkillActor);
PX2_IMPLEMENT_STREAM(SkillActor);
PX2_IMPLEMENT_FACTORY(SkillActor);
PX2_IMPLEMENT_DEFAULT_NAMES(EffectActor, SkillActor);

//----------------------------------------------------------------------------
SkillActor::SkillActor ()
	:
mTargetType(TT_ACTOR),
mTrackSpeed(10),
mCharacterGroup(0),
mSkillTypeID(0),
mTargetID(0),
mDegree(0.0f),
mSideDegree(0.0f),
mIsAlignTrace(false),
mFlyToNeedTime(0.0f),
mCurRunTime(0.0f),
mRangeRadius(1.0f),
mIsDoDamageOnTrack(false),
mIsOver(false)
{
	mCurve.AddPoint(0.0f, Float3::ZERO, Float3::ZERO, Float3::ZERO, ICM_CURVE_AUTO);
	mCurve.AddPoint(1.0f, Float3::ZERO, Float3::ZERO, Float3::ZERO, ICM_CURVE_AUTO);
}
//----------------------------------------------------------------------------
SkillActor::~SkillActor ()
{
}
//----------------------------------------------------------------------------
void SkillActor::Update (double appSeconds, double elapsedSeconds)
{
	EffectActor::Update(appSeconds, elapsedSeconds);

	mCurRunTime += (float)elapsedSeconds;

	if (mCurRunTime > mFlyToNeedTime)
	{
		SetOver(true);
	}

	if (!mIsOver)
	{
		APoint curPos;
		AVector dir;

		if (TT_ACTOR == mTargetType)
		{
			Scene *scene = GetScene();

			Actor *actor =  scene->GetActorByID(mTargetID);
			if (actor)
			{
				APoint targetPos = actor->GetPosition();
				targetPos.Z() += 1.5f;
				mCurve.Points[1].OutVal = targetPos;
			}
		}
	}

	APoint curPos;
	if (mCurRunTime <= mFlyToNeedTime)
	{
		curPos = mCurve.Eval(mCurRunTime, Float3::ZERO);
	}
	else
	{
		curPos = mCurve.Points[1].OutVal;
	}
	SetPosition(curPos);

	if (mIsAlignTrace && mLastPos!=APoint::ORIGIN)
	{
		AVector dir = curPos - mLastPos;
		dir.Normalize();

		if (dir != AVector::ZERO)
		{
			AVector headheading = dir;
			headheading.Normalize();

			AVector y = AVector::UNIT_Y;
			float dotVal = y.Dot(headheading);
			float radZ = Mathf::ACos(dotVal);

			if (dir.X() < 0.0f)
			{
				radZ = Mathf::TWO_PI - radZ;
			}

			AVector z = AVector::UNIT_Z;
			float dotValZ = z.Dot(headheading);
			float radX = Mathf::ASin(dotValZ);

			Matrix3f mat;
			mat.MakeEulerXYZ(radX, 0.0f, -radZ);

			if (mMovable)
				mMovable->LocalTransform.SetRotate(mat);
		}
	}
	
	mLastPos = curPos;
}
//----------------------------------------------------------------------------
void SkillActor::SetTargetType (TargetType type)
{
	mTargetType = type;
}
//----------------------------------------------------------------------------
void SkillActor::SetBeginPos (const APoint &pos)
{
	mBeginPos = pos;

	mCurve.Points[0].OutVal = pos;
}
//----------------------------------------------------------------------------
void SkillActor::SetTargetID (int ID)
{
	mTargetID = ID;
}
//----------------------------------------------------------------------------
void SkillActor::SetTargetPos (const APoint &pos)
{
	mTargetPos = pos;

	mCurve.Points[1].OutVal = pos;
}
//----------------------------------------------------------------------------
void SkillActor::SetDegree (float degree)
{
	mDegree = degree;
}
//----------------------------------------------------------------------------
void SkillActor::Start ()
{
	SetOver(false);

	AVector dir;
	APoint targetPos;
	if (TT_ACTOR == mTargetType)
	{
		Actor *targetActor = mScene->GetActorByID(mTargetID);
		if (targetActor)
		{
			targetPos = targetActor->GetPosition();
			dir = targetPos - mBeginPos;
		}
	}
	else
	{
		targetPos = mTargetPos;
		dir = targetPos - mBeginPos;
	}

	float length = dir.Normalize();
	mFlyToNeedTime = length/mTrackSpeed;

	AVector newDir = dir;
	AVector newDir1 = dir;
	if (0.0f != mSideDegree)
	{
		AVector left = AVector::UNIT_Z.Cross(dir);
		left.Normalize();
		left *= Mathf::Tan(mSideDegree*Mathf::DEG_TO_RAD);

		if (left.X() > 0.0f)
			left.X() = -left.X();

		newDir = dir + left;
		newDir1 = dir - left;
	}

	if (0.0f != mDegree)
	{
		newDir.Z() = Mathf::Sqrt(newDir.X()*newDir.X() + newDir.Y()*newDir.Y())*Mathf::Tan(
			mDegree*Mathf::DEG_TO_RAD);
		newDir.Normalize();

		newDir1.Z() = Mathf::Sqrt(newDir1.X()*newDir1.X() + newDir1.Y()*newDir1.Y())*Mathf::Tan(
			mDegree*Mathf::DEG_TO_RAD);
	}

	newDir *= mTrackSpeed;
	newDir1 *= mTrackSpeed;

	mCurve.Points[0].InVal = 0.0f;
	mCurve.Points[0].OutVal = mBeginPos;
	mCurve.Points[0].ArriveTangent = newDir;
	mCurve.Points[0].LeaveTangent = newDir;
	if (0.0f == mDegree)
	{
		mCurve.Points[0].InterpMode = ICM_LINEAR;
	}

	AVector targetDir = newDir1;
	targetDir.Z() = -targetDir.Z();

	mCurve.Points[1].InVal = mFlyToNeedTime;
	mCurve.Points[1].OutVal = targetPos;
	mCurve.Points[1].ArriveTangent = targetDir;
	mCurve.Points[1].LeaveTangent = targetDir;
	if (0.0f == mDegree)
	{
		mCurve.Points[1].InterpMode = ICM_LINEAR;
	}

	mCurRunTime = 0.0f;

	OnStart();
}
//----------------------------------------------------------------------------
void SkillActor::OnStart ()
{
	if (mMovable)
		mMovable->ResetPlay();
}
//----------------------------------------------------------------------------
void SkillActor::SetOver (bool over)
{
	if (over == mIsOver)
		return;

	mIsOver = over;

	if (mIsOver)
	{
		if (mMovable)
			mMovable->Stop();

		PX2_DM.AddDeletingObj(this, 0.0f, 3.0f);
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// �־û�֧��
//----------------------------------------------------------------------------
SkillActor::SkillActor (LoadConstructor value)
	:
EffectActor(value),
	mTargetType(TT_ACTOR),
	mTrackSpeed(10),
	mCharacterGroup(0),
	mSkillTypeID(0),
	mTargetID(0),
	mSideDegree(0.0f),
	mDegree(30.0f),
	mIsAlignTrace(false),
	mFlyToNeedTime(0.0f),
	mCurRunTime(0.0f),
	mRangeRadius(1.0f),
	mIsDoDamageOnTrack(false),
	mIsOver(false)
{
	mCurve.AddPoint(0.0f, Float3::ZERO, Float3::ZERO, Float3::ZERO, ICM_CURVE_AUTO);
	mCurve.AddPoint(0.0f, Float3::ZERO, Float3::ZERO, Float3::ZERO, ICM_CURVE_AUTO);
}
//----------------------------------------------------------------------------
void SkillActor::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	EffectActor::Load(source);
	PX2_VERSION_LOAD(source);

	source.ReadEnum(mTargetType);
	source.Read(mTrackSpeed);
	source.Read(mTargetID);
	source.Read(mSideDegree);
	source.Read(mDegree);
	source.ReadBool(mIsAlignTrace);
	source.Read(mRangeRadius);
	source.ReadBool(mIsDoDamageOnTrack);

	PX2_END_DEBUG_STREAM_LOAD(SkillActor, source);
}
//----------------------------------------------------------------------------
void SkillActor::Link (InStream& source)
{
	EffectActor::Link(source);
}
//----------------------------------------------------------------------------
void SkillActor::PostLink ()
{
	EffectActor::PostLink();
}
//----------------------------------------------------------------------------
bool SkillActor::Register (OutStream& target) const
{
	if (EffectActor::Register(target))
	{
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void SkillActor::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	EffectActor::Save(target);
	PX2_VERSION_SAVE(target);

	target.WriteEnum(mTargetType);
	target.Write(mTrackSpeed);
	target.Write(mTargetID);
	target.Write(mSideDegree);
	target.Write(mDegree);
	target.WriteBool(mIsAlignTrace);
	target.Write(mRangeRadius);
	target.WriteBool(mIsDoDamageOnTrack);

	PX2_END_DEBUG_STREAM_SAVE(SkillActor, target);
}
//----------------------------------------------------------------------------
int SkillActor::GetStreamingSize (Stream &stream) const
{
	int size = EffectActor::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	size += PX2_ENUMSIZE(mTargetType);
	size += sizeof(mTrackSpeed);
	size += sizeof(mTargetID);
	size += sizeof(mSideDegree);
	size += sizeof(mDegree);
	size += PX2_BOOLSIZE(mIsAlignTrace);
	size += sizeof(mRangeRadius);
	size += PX2_BOOLSIZE(mIsDoDamageOnTrack);

	return size;
}
//----------------------------------------------------------------------------
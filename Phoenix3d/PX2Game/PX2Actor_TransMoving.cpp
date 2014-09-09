/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Actor_TransMoving.cpp
*
*/

#include "PX2Actor.hpp"
#include "PX2Scene.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
void Actor::SetScale (const APoint &scale)
{
	if (scale == mScale)
		return;

	mScale = scale;

	if (0.0f==mScale.X() || 0.0f==mScale.Y() || 0.0f==mScale.Z())
	{
		mScale.X() = 0.0001f;
	}

	if (mMovable)
	{
		mMovable->LocalTransform.SetScale(scale);
	}

	if (mHelpMovable)
	{
		mHelpMovable->LocalTransform.SetScale(scale);
	}
}
//----------------------------------------------------------------------------
void Actor::SetRotation (const APoint &rolate)
{
	if (rolate == mRotation)
		return;

	mRotation = rolate;

	if (mMovable)
	{
		mMovable->LocalTransform.SetRotate(Matrix3f().MakeEulerXYZ(
			rolate.X(), rolate.Y(), rolate.Z()));
	}

	if (mHelpMovable)
	{
		mHelpMovable->LocalTransform.SetRotate(Matrix3f().MakeEulerXYZ(
			rolate.X(), rolate.Y(), rolate.Z()));
	}
}
//----------------------------------------------------------------------------
void Actor::SetPosition (const APoint &position)
{
	if (position == mPosition)
		return;

	APoint beforePosition = mPosition;
	mPosition = position;

	if (mMovable)
	{
		mMovable->LocalTransform.SetTranslate(position);
	}

	if (mHelpMovable)
	{
		mHelpMovable->LocalTransform.SetTranslate(position);
	}

	if (mScene)
	{
		mScene->OnActorPositionChanged(this, beforePosition);
	}
}
//----------------------------------------------------------------------------
void Actor::SetMaxSpeed (float val) 
{ 
	mMaxSpeed = val; 

	CalMMaxSpeed (); 
} 
//----------------------------------------------------------------------------
float Actor::GetMaxSpeed () const 
{ 
	return mMaxSpeed; 
} 
//----------------------------------------------------------------------------
void Actor::AddMMaxSpeed (const std::string &factorName, float val) 
{ 
	mMMapMaxSpeed[factorName] = val; 

	CalMMaxSpeed (); 
} 
//----------------------------------------------------------------------------
float Actor::GetMMaxSpeed (const std::string &factorName) 
{ 
	std::map<std::string, float>::iterator it = mMMapMaxSpeed.find(factorName); 
	if (mMMapMaxSpeed.end() != it) 
	{ 
		return it->second; 
	}
	else
	{
		assertion(false, "%s does not exist.\n", factorName.c_str());
		PX2_LOG_ERROR("%s does not exist.", factorName.c_str());
	}

	return 0.0f;
}
//----------------------------------------------------------------------------
void Actor::RemoveMMaxSpeed (const std::string &factorName)
{
	std::map<std::string, float>::iterator it = mMMapMaxSpeed.find(factorName);
	if (it != mMMapMaxSpeed.end())
	{
		mMMapMaxSpeed.erase(it);
	}

	CalMMaxSpeed ();
}
//----------------------------------------------------------------------------
std::map<std::string, float> &Actor::GetMMapMaxSpeed () 
{
	return mMMapMaxSpeed;
}
//----------------------------------------------------------------------------
void Actor::CalMMaxSpeed ()
{
	mMMaxSpeed = GetMaxSpeed ();

	std::map<std::string, float>::iterator it = mMMapMaxSpeed.begin();
	for (; it!=mMMapMaxSpeed.end(); it++)
	{
		mMMaxSpeed += it->second;
	}

	OnMaxSpeedModified();
}
//----------------------------------------------------------------------------
void Actor::OnMaxSpeedModified ()
{
}
//----------------------------------------------------------------------------
float Actor::GetPercentSpeedOverModified ()
{
	if (0.0f == mMMaxSpeed)
		return 0.0f;

	return mMaxSpeed/mMMaxSpeed;
}
//----------------------------------------------------------------------------
float Actor::GetMMaxSpeed () const
{
	return mMMaxSpeed;
}
//----------------------------------------------------------------------------
void Actor::StopSpeed (bool stop)
{
	mIsStopSpeed = stop;

	if (mIsStopSpeed)
	{
		if (mGridMoveBehavior)
			mGridMoveBehavior->SetSpeed(0.0f);

		SetVelocity(AVector::ZERO);
	}
}
//----------------------------------------------------------------------------
void Actor::SetVelocity (const AVector &vec)
{
	mVelocity = vec;
}
//----------------------------------------------------------------------------
void Actor::SetHeading (const AVector &heading)
{
	mHeading = heading;
}
//----------------------------------------------------------------------------
void Actor::OnUpdateGoToPosition (const APoint &toPos)
{
	SetPosition(toPos);
}
//----------------------------------------------------------------------------
void Actor::SetSmoothHeading (const AVector &soomthHeading)
{
	mSmoothHeading = soomthHeading;
}
//----------------------------------------------------------------------------
/*
*
* ÎÄ¼þÃû³Æ	£º	PX2AmbientRegionActor.inl
*
*/

//----------------------------------------------------------------------------
inline const Float3 &AmbientRegionActor::GetAmbientColor () const
{
	return mAmbientColor;
}
//----------------------------------------------------------------------------
inline const Float3 &AmbientRegionActor::GetLightDiffColor () const
{
	return mDirLightDiffColor;
}
//----------------------------------------------------------------------------
inline const Float3 &AmbientRegionActor::GetLightSpecColor () const
{
	return mLightSpecColor;
}
//----------------------------------------------------------------------------
inline float AmbientRegionActor::GetLightIntensity () const
{
	return mLightIntensity;
}
//----------------------------------------------------------------------------
inline float AmbientRegionActor::GetHorAngle () const
{
	return mHorAngle;
}
//----------------------------------------------------------------------------
inline float AmbientRegionActor::GetVerAngle () const
{
	return mVerAngle;
}
//----------------------------------------------------------------------------
inline const Light *AmbientRegionActor::GetLight () const
{
	return mLight;
}
//----------------------------------------------------------------------------
inline Light *AmbientRegionActor::GetLight ()
{
	return mLight;
}
//----------------------------------------------------------------------------
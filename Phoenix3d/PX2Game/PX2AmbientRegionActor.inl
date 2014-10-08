/*
*
* ÎÄ¼þÃû³Æ	£º	PX2AmbientRegionActor.inl
*
*/

//----------------------------------------------------------------------------
inline void AmbientRegionActor::SetGISkyLightColor (const Float3 &color)
{
	mBakeSkyLightColor = color;
}
//----------------------------------------------------------------------------
inline const Float3 &AmbientRegionActor::GetGISkyLightColor () const
{
	return mBakeSkyLightColor;
}
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
inline void AmbientRegionActor::SetAmbientScale (float scale)
{
	mAmbientScale = scale;
}
//----------------------------------------------------------------------------
inline void AmbientRegionActor::SetDiffuseScale (float scale)
{
	mDiffuseScale = scale;
}
//----------------------------------------------------------------------------
inline void AmbientRegionActor::SetSpecularScale (float scale)
{
	mSpecularScale = scale;
}
//----------------------------------------------------------------------------
inline float AmbientRegionActor::GetAmbientScale () const
{
	return mAmbientScale;
}
//----------------------------------------------------------------------------
inline float AmbientRegionActor::GetDiffuseScale () const
{
	return mDiffuseScale;
}
//----------------------------------------------------------------------------
inline float AmbientRegionActor::GetSpecularScale () const
{
	return mSpecularScale;
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
inline void AmbientRegionActor::SetBakeShadowAngle (float shadowAnge)
{
	mBakeShadowAngle = shadowAnge;
}
//----------------------------------------------------------------------------
inline float AmbientRegionActor::GetBakeShadowAngle () const
{
	return mBakeShadowAngle;
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
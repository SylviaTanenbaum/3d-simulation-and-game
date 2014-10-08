/*
*
* 文件名称	：	PX2AmbientRegionActor.cpp
*
*/

#include "PX2AmbientRegionActor.hpp"
#include "PX2GraphicsRoot.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI_V(PX2, TriggerActor, AmbientRegionActor, 5);
PX2_IMPLEMENT_STREAM(AmbientRegionActor);
PX2_IMPLEMENT_FACTORY(AmbientRegionActor);

//----------------------------------------------------------------------------
AmbientRegionActor::AmbientRegionActor ()
{
	mHorAngle = 30.0f;
	mVerAngle = 15.0f;
	mLightIntensity = 1.0f;

	mAmbientColor = Float3(0.4f, 0.4f, 0.4f);
	mDirLightDiffColor = Float3(1.0f, 1.0f, 1.0f);
	mLightSpecColor = Float3(0.5f, 0.5f, 0.5f);

	mLight = new0 Light(Light::LT_DIRECTIONAL);
	mLight->SetDirection(AVector(-1.0f, -1.0f, -1.0f));
	mLight->Ambient = Float4(0.2f, 0.2f, 0.2f, 1.0f);
	mLight->Diffuse = Float4(1.0f, 1.0f, 1.0f, 1.0f);
	mLight->Specular = Float4(0.5f, 0.5f, 0.5f, 1.0f);

	mFogParam = Float2(60.0f, 240.0f);
	mFogColor = Float3::WHITE;

	mBakeShadowAngle = 0.0f; 

	mBakeSkyLightColor = Float3::WHITE;

	mAmbientScale = 1.0f;
	mDiffuseScale = 1.0f;
	mSpecularScale = 1.0f;

	mShineParam = Float2(1.0f, 1.0f);
}
//----------------------------------------------------------------------------
AmbientRegionActor::~AmbientRegionActor ()
{
}
//----------------------------------------------------------------------------
void AmbientRegionActor::SetAmbientColor (const Float3 &color)
{
	mAmbientColor = color;

	if (mLight)
	{
		mLight->Ambient = Float4(color[0], color[1], color[2], 1.0f);
	}
}
//----------------------------------------------------------------------------
void AmbientRegionActor::SetLightDiffColor (const Float3 &color)
{
	mDirLightDiffColor = color;

	if (mLight)
	{
		mLight->Diffuse = Float4(color[0], color[1], color[2], 1.0f);
	}
}
//----------------------------------------------------------------------------
void AmbientRegionActor::SetLightSpecColor (const Float3 &color)
{
	mLightSpecColor = color;

	if (mLight)
	{
		mLight->Specular = Float4(color[0], color[1], color[2], 1.0f);
	}
}
//----------------------------------------------------------------------------
void AmbientRegionActor::SetLightIntensity (float intensity)
{
	mLightIntensity = intensity;

	if (mLight)
	{
		mLight->Intensity = intensity;
	}
}
//----------------------------------------------------------------------------
static AVector AnglesToDirection(float angle0, float angle1)
{
	return AVector(Mathf::Cos(angle1)*Mathf::Cos(angle0), 
		-Mathf::Cos(angle1)*Mathf::Sin(angle0), -Mathf::Sin(angle1));
}
//----------------------------------------------------------------------------
void AmbientRegionActor::SetHorAngle (float angle)
{
	mHorAngle = angle;

	if (mLight)
	{
		AVector dir = AnglesToDirection(Mathf::DEG_TO_RAD*mHorAngle, 
			Mathf::DEG_TO_RAD*mVerAngle);
		mLight->SetDirection(dir);
	}
}
//----------------------------------------------------------------------------
void AmbientRegionActor::SetVerAngle (float angle)
{
	mVerAngle = angle;

	if (mLight)
	{
		AVector dir = AnglesToDirection(Mathf::DEG_TO_RAD*mHorAngle, 
			Mathf::DEG_TO_RAD*mVerAngle);
		mLight->SetDirection(dir);
	}
}
//----------------------------------------------------------------------------
void AmbientRegionActor::CalLights ()
{
	if (mLight)
	{
		GraphicsRoot::GetSingleton().RemoveLight(mLight);
	}
}
//----------------------------------------------------------------------------
void AmbientRegionActor::DoEnter ()
{
}
//----------------------------------------------------------------------------
void AmbientRegionActor::DoExecute (Event *event)
{
	PX2_UNUSED(event);
}
//----------------------------------------------------------------------------
void AmbientRegionActor::DoLeave ()
{
}
//----------------------------------------------------------------------------
void AmbientRegionActor::SetScene (Scene *scene)
{
	if (scene)
	{
		if (mLight)
		{
			GraphicsRoot::GetSingleton().AddLight(mLight);
		}
	}
	else
	{
		if (mLight)
		{
			GraphicsRoot::GetSingleton().RemoveLight(mLight);
		}
	}

	TriggerActor::SetScene(scene);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Property
//----------------------------------------------------------------------------
void AmbientRegionActor::RegistProperties ()
{
	TriggerActor::RegistProperties();

	AddPropertyClass("AmbientRegionActor");

	AddProperty("GI_SkyLightColor_Bake", Object::PT_COLOR3FLOAT3, mBakeSkyLightColor);

	AddProperty("AmbientColor_Bake", Object::PT_COLOR3FLOAT3, mAmbientColor);
	AddProperty("AmbientColor_BakeScale", Object::PT_FLOAT, mAmbientScale);

	AddProperty("LightDiffColor_Bake", Object::PT_COLOR3FLOAT3, mDirLightDiffColor);
	AddProperty("LightDiffColor_BakeScale", Object::PT_FLOAT, mDiffuseScale);

	AddProperty("LightSpecColor_Bake", Object::PT_COLOR3FLOAT3, mLightSpecColor);
	AddProperty("LightSpecColor_BakeScale", Object::PT_FLOAT, mSpecularScale);
	
	//AddProperty("LightIntensity", Object::PT_FLOAT, mLightIntensity);
	AddProperty("ShadowAngle_Bake", Object::PT_FLOAT, mBakeShadowAngle);
	AddProperty("HorAngle", Object::PT_FLOAT, mHorAngle);
	AddProperty("VerAngle", Object::PT_FLOAT, mVerAngle);
	
	AddProperty("FogParam", Object::PT_FLOAT2, mFogParam);
	AddProperty("FogColor", Object::PT_COLOR3FLOAT3, mFogColor);

	AddProperty("ShineParam", Object::PT_FLOAT2, mShineParam);
}
//----------------------------------------------------------------------------
void AmbientRegionActor::OnPropertyChanged (const PropertyObject &obj) 
{ 
	TriggerActor::OnPropertyChanged(obj);

	if ("GI_SkyLightColor_Bake" == obj.Name)
	{
		SetGISkyLightColor(PX2_ANY_AS(obj.Data, Float3));
	}
	if ("AmbientColor_Bake" == obj.Name)
	{
		SetAmbientColor(PX2_ANY_AS(obj.Data, Float3));
	}
	else if ("AmbientColor_BakeScale" == obj.Name)
	{
		SetAmbientScale(PX2_ANY_AS(obj.Data, float));
	}
	else if ("LightDiffColor_Bake" == obj.Name)
	{
		SetLightDiffColor(PX2_ANY_AS(obj.Data, Float3));
	}
	else if ("LightDiffColor_BakeScale" == obj.Name)
	{
		SetDiffuseScale(PX2_ANY_AS(obj.Data, float));
	}
	else if ("AmbientColor_BakeScale" == obj.Name)
	{
		SetAmbientScale(PX2_ANY_AS(obj.Data, float));
	}
	else if ("LightSpecColor_BakeScale" == obj.Name)
	{
		SetSpecularScale(PX2_ANY_AS(obj.Data, float));
	}
	else if ("LightDiffColor_BakeScale" == obj.Name)
	{
		SetDiffuseScale(PX2_ANY_AS(obj.Data, float));
	}
	else if ("LightSpecColor_BakeScale" == obj.Name)
	{
		SetSpecularScale(PX2_ANY_AS(obj.Data, float));
	}
	else if ("ShadowAngle_Bake" == obj.Name)
	{
		SetBakeShadowAngle(PX2_ANY_AS(obj.Data, float));
	}
	else if ("LightSpecColor_Bake" == obj.Name)
	{
		SetLightSpecColor(PX2_ANY_AS(obj.Data, Float3));
	}
	else if ("LightIntensity" == obj.Name)
	{
		SetLightIntensity(PX2_ANY_AS(obj.Data, float));
	}
	else if ("HorAngle" == obj.Name)
	{
		SetHorAngle(PX2_ANY_AS(obj.Data, float));
	}
	else if ("VerAngle" == obj.Name)
	{
		SetVerAngle(PX2_ANY_AS(obj.Data, float));
	}
	else if ("FogParam" == obj.Name)
	{
		mFogParam = PX2_ANY_AS(obj.Data, Float2);
		Float4 lastParam = Float4(mFogParam[0],mFogParam[1], mShineParam[0], mShineParam[1]);
		PX2_GR.SetFogParam(lastParam);
	}
	else if ("FogColor" == obj.Name)
	{
		mFogColor = PX2_ANY_AS(obj.Data, Float3);
		Float4 lastColor = Float4(mFogColor[0], mFogColor[1], mFogColor[2], 1.0f);
		PX2_GR.SetFogColor(lastColor);
	}
	else if ("ShineParam" == obj.Name)
	{
		mShineParam = PX2_ANY_AS(obj.Data, Float2);
		Float4 lastParam = Float4(mFogParam[0],mFogParam[1], mShineParam[0], mShineParam[1]);
		PX2_GR.SetFogParam(lastParam);
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称支持
//----------------------------------------------------------------------------
Object* AmbientRegionActor::GetObjectByName (const std::string& name)
{
	Object* found = TriggerActor::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	return 0;
}
//----------------------------------------------------------------------------
void AmbientRegionActor::GetAllObjectsByName (const std::string& name,
	std::vector<Object*>& objects)
{
	TriggerActor::GetAllObjectsByName(name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
AmbientRegionActor::AmbientRegionActor (LoadConstructor value)
	:
TriggerActor(value)
{
	mHorAngle = 30.0f;
	mVerAngle = 15.0f;
	mLightIntensity = 1.0f;

	mAmbientColor = Float3(0.4f, 0.4f, 0.4f);
	mDirLightDiffColor = Float3(1.0f, 1.0f, 1.0f);
	mLightSpecColor = Float3(0.5f, 0.5f, 0.5f);

	mBakeShadowAngle = 0.0f; 

	mFogParam = Float2(60.0f, 240.0f);
	mFogColor = Float3::WHITE;

	mBakeSkyLightColor = Float3::WHITE;

	mAmbientScale = 1.0f;
	mDiffuseScale = 1.0f;
	mSpecularScale = 1.0f;

	mShineParam = Float2(1.0f, 1.0f);
}
//----------------------------------------------------------------------------
void AmbientRegionActor::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	TriggerActor::Load(source);
	PX2_VERSION_LOAD(source);

	source.ReadAggregate<Float3>(mAmbientColor);
	source.ReadAggregate<Float3>(mDirLightDiffColor);
	source.ReadAggregate<Float3>(mLightSpecColor);
	source.Read(mLightIntensity);
	source.Read(mHorAngle);
	source.Read(mVerAngle);
	source.ReadPointer(mLight);

	int readedVersion = GetReadedVersion();
	if (1 <= readedVersion)
	{
		source.Read(mBakeShadowAngle);
	}
	if (2 <= readedVersion)
	{
		source.ReadAggregate(mFogParam);
		source.ReadAggregate(mFogColor);
	}
	if (3 <= readedVersion)
	{
		source.ReadAggregate(mBakeSkyLightColor);
	}
	if (4 <= readedVersion)
	{
		source.Read(mAmbientScale);
		source.Read(mDiffuseScale);
		source.Read(mSpecularScale);
	}
	if (5 <= readedVersion)
	{
		source.Read(mShineParam);
	}

	PX2_END_DEBUG_STREAM_LOAD(AmbientRegionActor, source);
}
//----------------------------------------------------------------------------
void AmbientRegionActor::Link (InStream& source)
{
	TriggerActor::Link(source);

	if (mLight)
		source.ResolveLink(mLight);
}
//----------------------------------------------------------------------------
void AmbientRegionActor::PostLink ()
{
	TriggerActor::PostLink();

	PX2_GR.SetFogParam(Float4(mFogParam[0],mFogParam[1], mShineParam[0], mShineParam[1]));
	PX2_GR.SetFogColor(Float4(mFogColor[0], mFogColor[1], mFogColor[2], 1.0f));
}
//----------------------------------------------------------------------------
bool AmbientRegionActor::Register (OutStream& target) const
{
	if (TriggerActor::Register(target))
	{
		if (mLight)
			target.Register(mLight);

		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void AmbientRegionActor::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	TriggerActor::Save(target);
	PX2_VERSION_SAVE(target);

	target.WriteAggregate<Float3>(mAmbientColor);
	target.WriteAggregate<Float3>(mDirLightDiffColor);
	target.WriteAggregate<Float3>(mLightSpecColor);
	target.Write(mLightIntensity);
	target.Write(mHorAngle);
	target.Write(mVerAngle);
	target.WritePointer(mLight);
	
	target.Write(mBakeShadowAngle);

	target.WriteAggregate(mFogParam);
	target.WriteAggregate(mFogColor);

	target.WriteAggregate(mBakeSkyLightColor);

	target.Write(mAmbientScale);
	target.Write(mDiffuseScale);
	target.Write(mSpecularScale);

	target.WriteAggregate(mShineParam);

	PX2_END_DEBUG_STREAM_SAVE(AmbientRegionActor, target);
}
//----------------------------------------------------------------------------
int AmbientRegionActor::GetStreamingSize (Stream &stream) const
{
	int size = TriggerActor::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);
	size += sizeof(mAmbientColor);
	size += sizeof(mDirLightDiffColor);
	size += sizeof(mLightSpecColor);
	size += sizeof(mLightIntensity);
	size += sizeof(mHorAngle);
	size += sizeof(mVerAngle);
	size += PX2_POINTERSIZE(mLight);

	if (stream.IsIn())
	{
		int readedVersion = GetReadedVersion();
		if (1 <= readedVersion)
		{
			size += sizeof(mBakeShadowAngle);
		}
		if (2 <= readedVersion)
		{
			size += sizeof(mFogParam);
			size += sizeof(mFogColor);
		}
		if (3 <= readedVersion)
		{
			size += sizeof(mBakeSkyLightColor);
		}
		if (4 <= readedVersion)
		{
			size += sizeof(mAmbientScale);
			size += sizeof(mDiffuseScale);
			size += sizeof(mSpecularScale);
		}
		if (5 <= readedVersion)
		{
			size += sizeof(mShineParam);
		}
	}
	else
	{
		size += sizeof(mBakeShadowAngle);

		size += sizeof(mFogParam);
		size += sizeof(mFogColor);

		size += sizeof(mBakeSkyLightColor);

		size += sizeof(mAmbientScale);
		size += sizeof(mDiffuseScale);
		size += sizeof(mSpecularScale);

		size += sizeof(mShineParam);
	}

	return size;
}
//----------------------------------------------------------------------------
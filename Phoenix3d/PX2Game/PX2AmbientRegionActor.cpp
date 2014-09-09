/*
*
* 文件名称	：	PX2AmbientRegionActor.cpp
*
*/

#include "PX2AmbientRegionActor.hpp"
#include "PX2GraphicsRoot.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, TriggerActor, AmbientRegionActor);
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

	AddProperty("AmbientColor", Object::PT_COLOR3FLOAT3, mAmbientColor);
	AddProperty("LightDiffColor_Bake", Object::PT_COLOR3FLOAT3, mDirLightDiffColor);
	//AddProperty("LightSpecColor", Object::PT_COLOR3FLOAT3, mLightSpecColor);
	//AddProperty("LightIntensity", Object::PT_FLOAT, mLightIntensity);
	AddProperty("HorAngle", Object::PT_FLOAT, mHorAngle);
	AddProperty("VerAngle", Object::PT_FLOAT, mVerAngle);
}
//----------------------------------------------------------------------------
void AmbientRegionActor::OnPropertyChanged (const PropertyObject &obj) 
{ 
	TriggerActor::OnPropertyChanged(obj);

	if ("AmbientColor" == obj.Name)
	{
		SetAmbientColor(PX2_ANY_AS(obj.Data, Float3));
	}
	else if ("LightDiffColor_Bake" == obj.Name)
	{
		SetLightDiffColor(PX2_ANY_AS(obj.Data, Float3));
	}
	else if ("LightSpecColor" == obj.Name)
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

	return size;
}
//----------------------------------------------------------------------------
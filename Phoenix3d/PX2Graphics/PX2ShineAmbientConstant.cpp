/*
*
* �ļ�����	��	PX2ShineAmbientConstant.cpp
*
*/

#include "PX2ShineAmbientConstant.hpp"
#include "PX2Camera.hpp"
#include "PX2Renderable.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, ShaderFloat, ShineAmbientConstant);
PX2_IMPLEMENT_STREAM(ShineAmbientConstant);
PX2_IMPLEMENT_FACTORY(ShineAmbientConstant);

//----------------------------------------------------------------------------
ShineAmbientConstant::ShineAmbientConstant (Shine* shine)
:
ShaderFloat(1),
mShine(shine)
{
	EnableUpdater();
}
//----------------------------------------------------------------------------
ShineAmbientConstant::~ShineAmbientConstant ()
{
}
//----------------------------------------------------------------------------
Shine* ShineAmbientConstant::GetShine ()
{
	return mShine;
}
//----------------------------------------------------------------------------
void ShineAmbientConstant::Update (const Renderable*, const Camera*)
{
	const float* source = (const float*)mShine->Ambient;
	float* target = mData;
	for (int i = 0; i < 4; ++i)
	{
		*target++ = *source++;
	}
}
//----------------------------------------------------------------------------
void ShineAmbientConstant::Float_OnRegistProperties (Object *parObj)
{
	parObj->AddProperty("S_Ambinet_Emissive", Object::PT_COLOR3FLOAT3, Float3(mShine->Emissive[0], mShine->Emissive[1], mShine->Emissive[2]));
	parObj->AddProperty("S_Ambinet_Ambient", Object::PT_COLOR3FLOAT3, Float3(mShine->Ambient[0], mShine->Ambient[1], mShine->Ambient[2]));
	parObj->AddProperty("S_Ambinet_Diffuse", Object::PT_COLOR3FLOAT3, Float3(mShine->Diffuse[0], mShine->Diffuse[1], mShine->Diffuse[2]));
	parObj->AddProperty("S_Ambinet_Specular", Object::PT_COLOR3FLOAT3, Float3(mShine->Specular[0], mShine->Specular[1], mShine->Specular[2]));
}
//----------------------------------------------------------------------------
void ShineAmbientConstant::Float_OnPropertyChanged (Object *parObj, 
	const PropertyObject &obj)
{
	if (obj.Name == "S_Ambinet_Emissive")
	{
		Float3 color = PX2_ANY_AS(obj.Data, Float3);
		mShine->Emissive = Float4(color[0], color[1], color[2], 1.0f);
	}
	else if (obj.Name == "S_Ambinet_Ambient")
	{
		Float3 color = PX2_ANY_AS(obj.Data, Float3);
		mShine->Ambient = Float4(color[0], color[1], color[2], 1.0f);
	}
	else if (obj.Name == "S_Ambinet_Diffuse")
	{
		Float3 color = PX2_ANY_AS(obj.Data, Float3);
		mShine->Diffuse = Float4(color[0], color[1], color[2], 1.0f);
	}
	else if (obj.Name == "S_Ambinet_Specular")
	{
		Float3 color = PX2_ANY_AS(obj.Data, Float3);
		mShine->Specular = Float4(color[0], color[1], color[2], 1.0f);
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ����֧��
//----------------------------------------------------------------------------
Object* ShineAmbientConstant::GetObjectByName (const std::string& name)
{
	Object* found = ShaderFloat::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	PX2_GET_OBJECT_BY_NAME(mShine, name, found);
	return 0;
}
//----------------------------------------------------------------------------
void ShineAmbientConstant::GetAllObjectsByName (const std::string& name,
												   std::vector<Object*>& objects)
{
	ShaderFloat::GetAllObjectsByName(name, objects);

	PX2_GET_ALL_OBJECTS_BY_NAME(mShine, name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// �־û�
//----------------------------------------------------------------------------
ShineAmbientConstant::ShineAmbientConstant (LoadConstructor value)
:
ShaderFloat(value)
{
}
//----------------------------------------------------------------------------
void ShineAmbientConstant::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	ShaderFloat::Load(source);
	PX2_VERSION_LOAD(source);

	source.ReadPointer(mShine);

	PX2_END_DEBUG_STREAM_LOAD(ShineAmbientConstant, source);
}
//----------------------------------------------------------------------------
void ShineAmbientConstant::Link (InStream& source)
{
	ShaderFloat::Link(source);

	source.ResolveLink(mShine);
}
//----------------------------------------------------------------------------
void ShineAmbientConstant::PostLink ()
{
	ShaderFloat::PostLink();
}
//----------------------------------------------------------------------------
bool ShineAmbientConstant::Register (OutStream& target) const
{
	if (ShaderFloat::Register(target))
	{
		target.Register(mShine);
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void ShineAmbientConstant::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	ShaderFloat::Save(target);
	PX2_VERSION_SAVE(target);

	target.WritePointer(mShine);

	PX2_END_DEBUG_STREAM_SAVE(ShineAmbientConstant, target);
}
//----------------------------------------------------------------------------
int ShineAmbientConstant::GetStreamingSize (Stream &stream) const
{
	int size = ShaderFloat::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);
	size += PX2_POINTERSIZE(mShine);
	return size;
}
//----------------------------------------------------------------------------

/*
*
* �ļ�����	��	PX2LightAmbientConstant.cpp
*
*/

#include "PX2LightAmbientConstant.hpp"
#include "PX2Camera.hpp"
#include "PX2Renderable.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, ShaderFloat, LightAmbientConstant);
PX2_IMPLEMENT_STREAM(LightAmbientConstant);
PX2_IMPLEMENT_FACTORY(LightAmbientConstant);

//----------------------------------------------------------------------------
LightAmbientConstant::LightAmbientConstant (Light* light)
    :
    ShaderFloat(1),
    mLight(light)
{
    EnableUpdater();
}
//----------------------------------------------------------------------------
LightAmbientConstant::~LightAmbientConstant ()
{
}
//----------------------------------------------------------------------------
void LightAmbientConstant::SetLight (Light *light)
{
	mLight = light;
}
//----------------------------------------------------------------------------
Light* LightAmbientConstant::GetLight ()
{
    return mLight;
}
//----------------------------------------------------------------------------
void LightAmbientConstant::Update (const Renderable*, const Camera*)
{
    const float* source = (const float*)mLight->Ambient;
    float* target = mData;
    for (int i = 0; i < 4; ++i)
    {
        *target++ = *source++;
    }
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ����֧��
//----------------------------------------------------------------------------
Object* LightAmbientConstant::GetObjectByName (const std::string& name)
{
    Object* found = ShaderFloat::GetObjectByName(name);
    if (found)
    {
        return found;
    }

    PX2_GET_OBJECT_BY_NAME(mLight, name, found);
    return 0;
}
//----------------------------------------------------------------------------
void LightAmbientConstant::GetAllObjectsByName (const std::string& name,
    std::vector<Object*>& objects)
{
    ShaderFloat::GetAllObjectsByName(name, objects);

    PX2_GET_ALL_OBJECTS_BY_NAME(mLight, name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// �־û�֧��
//----------------------------------------------------------------------------
LightAmbientConstant::LightAmbientConstant (LoadConstructor value)
    :
    ShaderFloat(value)
{
}
//----------------------------------------------------------------------------
void LightAmbientConstant::Load (InStream& source)
{
    PX2_BEGIN_DEBUG_STREAM_LOAD(source);

    ShaderFloat::Load(source);
	PX2_VERSION_LOAD(source);

    source.ReadPointer(mLight);

    PX2_END_DEBUG_STREAM_LOAD(LightAmbientConstant, source);
}
//----------------------------------------------------------------------------
void LightAmbientConstant::Link (InStream& source)
{
    ShaderFloat::Link(source);

    source.ResolveLink(mLight);
}
//----------------------------------------------------------------------------
void LightAmbientConstant::PostLink ()
{
    ShaderFloat::PostLink();
}
//----------------------------------------------------------------------------
bool LightAmbientConstant::Register (OutStream& target) const
{
    if (ShaderFloat::Register(target))
    {
        target.Register(mLight);
        return true;
    }
    return false;
}
//----------------------------------------------------------------------------
void LightAmbientConstant::Save (OutStream& target) const
{
    PX2_BEGIN_DEBUG_STREAM_SAVE(target);

    ShaderFloat::Save(target);
	PX2_VERSION_SAVE(target);

    target.WritePointer(mLight);

    PX2_END_DEBUG_STREAM_SAVE(LightAmbientConstant, target);
}
//----------------------------------------------------------------------------
int LightAmbientConstant::GetStreamingSize (Stream &stream) const
{
    int size = ShaderFloat::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);
    size += PX2_POINTERSIZE(mLight);
    return size;
}
//----------------------------------------------------------------------------

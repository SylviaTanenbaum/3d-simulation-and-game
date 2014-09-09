/*
*
* �ļ�����	��	PX2DepthProperty.cpp
*
*/

#include "PX2DepthProperty.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Object, DepthProperty);
PX2_IMPLEMENT_STREAM(DepthProperty);
PX2_IMPLEMENT_FACTORY(DepthProperty);
PX2_IMPLEMENT_DEFAULT_NAMES(Object, DepthProperty);

//----------------------------------------------------------------------------
DepthProperty::DepthProperty ()
:
Enabled(true),
Writable(true),
Compare(CM_LEQUAL)
{
}
//----------------------------------------------------------------------------
DepthProperty::~DepthProperty ()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// �־û�
//----------------------------------------------------------------------------
DepthProperty::DepthProperty (LoadConstructor value)
:
Object(value),
Enabled(false),
Writable(false),
Compare(CM_NEVER)
{
}
//----------------------------------------------------------------------------
void DepthProperty::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Object::Load(source);
	PX2_VERSION_LOAD(source);

	source.ReadBool(Enabled);
	source.ReadBool(Writable);
	source.ReadEnum(Compare);

	PX2_END_DEBUG_STREAM_LOAD(DepthProperty, source);
}
//----------------------------------------------------------------------------
void DepthProperty::Link (InStream& source)
{
	Object::Link(source);
}
//----------------------------------------------------------------------------
void DepthProperty::PostLink ()
{
	Object::PostLink();
}
//----------------------------------------------------------------------------
bool DepthProperty::Register (OutStream& target) const
{
	return Object::Register(target);
}
//----------------------------------------------------------------------------
void DepthProperty::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Object::Save(target);
	PX2_VERSION_SAVE(target);

	target.WriteBool(Enabled);
	target.WriteBool(Writable);
	target.WriteEnum(Compare);

	PX2_END_DEBUG_STREAM_SAVE(DepthProperty, target);
}
//----------------------------------------------------------------------------
int DepthProperty::GetStreamingSize (Stream &stream) const
{
	int size = Object::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);
	size += PX2_BOOLSIZE(Enabled);
	size += PX2_BOOLSIZE(Writable);
	size += PX2_ENUMSIZE(Compare);
	return size;
}
//----------------------------------------------------------------------------
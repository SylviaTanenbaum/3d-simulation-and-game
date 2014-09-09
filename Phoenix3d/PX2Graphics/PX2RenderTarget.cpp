/*
*
* �ļ�����	��	PX2RenderTarget.cpp
*
*/

#include "PX2RenderTarget.hpp"
#include "PX2Renderer.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Object, RenderTarget);
PX2_IMPLEMENT_STREAM(RenderTarget);
PX2_IMPLEMENT_FACTORY(RenderTarget);

//----------------------------------------------------------------------------
RenderTarget::RenderTarget (int numTargets, Texture::Format tformat,
							int width, int height, bool hasMipmaps, bool hasDepthStencil)
							:
mNumTargets(numTargets),
mHasMipmaps(hasMipmaps),
PdrPointer(0)
{
	assertion(mNumTargets > 0, "Number of targets must be at least one.\n");

	mColorTextures = new1<Texture2DPtr>(mNumTargets);
	int i;
	for (i = 0; i < mNumTargets; ++i)
	{
		mColorTextures[i] = new0 Texture2D(tformat, width, height,
			(hasMipmaps ? 0 : 1), Buffer::BU_RENDERTARGET);
	}

	if (hasDepthStencil)
	{
		mDepthStencilTexture = new0 Texture2D(Texture::TF_D24S8,
			width, height, 1, Buffer::BU_DEPTHSTENCIL);
	}
}
//----------------------------------------------------------------------------
RenderTarget::~RenderTarget ()
{
	Renderer::UnbindAll(this);

	delete1(mColorTextures);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ����֧��
//----------------------------------------------------------------------------
Object* RenderTarget::GetObjectByName (const std::string& name)
{
	Object* found = Object::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	for (int i = 0; i < mNumTargets; ++i)
	{
		PX2_GET_OBJECT_BY_NAME(mColorTextures[i], name, found);
	}
	PX2_GET_OBJECT_BY_NAME(mDepthStencilTexture, name, found);

	return 0;
}
//----------------------------------------------------------------------------
void RenderTarget::GetAllObjectsByName (const std::string& name,
										std::vector<Object*>& objects)
{
	Object::GetAllObjectsByName(name, objects);

	for (int i = 0; i < mNumTargets; ++i)
	{
		PX2_GET_ALL_OBJECTS_BY_NAME(mColorTextures[i], name, objects);
	}
	PX2_GET_ALL_OBJECTS_BY_NAME(mDepthStencilTexture, name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// �־û�֧��
//----------------------------------------------------------------------------
RenderTarget::RenderTarget (LoadConstructor value)
:
Object(value),
mNumTargets(0),
mColorTextures(0),
mHasMipmaps(false),
PdrPointer(0)
{
}
//----------------------------------------------------------------------------
void RenderTarget::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Object::Load(source);
	PX2_VERSION_LOAD(source);

	source.ReadPointerRR(mNumTargets, mColorTextures);
	source.ReadPointer(mDepthStencilTexture);
	source.ReadBool(mHasMipmaps);

	PX2_END_DEBUG_STREAM_LOAD(RenderTarget, source);
}
//----------------------------------------------------------------------------
void RenderTarget::Link (InStream& source)
{
	Object::Link(source);

	for (int i = 0; i < mNumTargets; ++i)
	{
		source.ResolveLink(mColorTextures[i]);
	}
	source.ResolveLink(mDepthStencilTexture);
}
//----------------------------------------------------------------------------
void RenderTarget::PostLink ()
{
	Object::PostLink();
}
//----------------------------------------------------------------------------
bool RenderTarget::Register (OutStream& target) const
{
	if (Object::Register(target))
	{
		for (int i = 0; i < mNumTargets; ++i)
		{
			target.Register(mColorTextures[i]);
		}
		target.Register(mDepthStencilTexture);
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void RenderTarget::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Object::Save(target);
	PX2_VERSION_SAVE(target);

	target.WritePointerW(mNumTargets, mColorTextures);
	target.WritePointer(mDepthStencilTexture);
	target.WriteBool(mHasMipmaps);

	PX2_END_DEBUG_STREAM_SAVE(RenderTarget, target);
}
//----------------------------------------------------------------------------
int RenderTarget::GetStreamingSize (Stream &stream) const
{
	int size = Object::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);
	size += mNumTargets*PX2_POINTERSIZE(mColorTextures[0]);
	size += PX2_POINTERSIZE(mDepthStencilTexture);
	size += PX2_BOOLSIZE(mHasMipmaps);
	return size;
}
//----------------------------------------------------------------------------
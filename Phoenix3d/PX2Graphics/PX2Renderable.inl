/*
*
* �ļ�����	��	PX2Renderable.inl
*
*/

//----------------------------------------------------------------------------
inline Renderable::PrimitiveType Renderable::GetPrimitiveType () const
{
    return mType;
}
//----------------------------------------------------------------------------
inline void Renderable::SetVertexFormat (VertexFormat* vformat)
{
    mVFormat = vformat;
}
//----------------------------------------------------------------------------
inline const VertexFormat* Renderable::GetVertexFormat () const
{
    return mVFormat;
}
//----------------------------------------------------------------------------
inline VertexFormat* Renderable::GetVertexFormat ()
{
    return mVFormat;
}
//----------------------------------------------------------------------------
inline void Renderable::SetVertexBuffer (VertexBuffer* vbuffer)
{
    mVBuffer = vbuffer;
}
//----------------------------------------------------------------------------
inline const VertexBuffer* Renderable::GetVertexBuffer () const
{
    return mVBuffer;
}
//----------------------------------------------------------------------------
inline VertexBuffer* Renderable::GetVertexBuffer ()
{
    return mVBuffer;
}
//----------------------------------------------------------------------------
inline void Renderable::SetIndexBuffer (IndexBuffer* ibuffer)
{
    mIBuffer = ibuffer;
}
//----------------------------------------------------------------------------
inline const IndexBuffer* Renderable::GetIndexBuffer () const
{
    return mIBuffer;
}
//----------------------------------------------------------------------------
inline IndexBuffer* Renderable::GetIndexBuffer ()
{
    return mIBuffer;
}
//----------------------------------------------------------------------------
inline void Renderable::SetShareDBObject_V (DBObject_V *obj)
{
	mDBObject_V = obj;
}
//----------------------------------------------------------------------------
inline const DBObject_V *Renderable::GetShareDBObject_V () const
{
	return mDBObject_V;
}
//----------------------------------------------------------------------------
inline DBObject_V *Renderable::GetShareDBObject_V ()
{
	return mDBObject_V;
}
//----------------------------------------------------------------------------
inline void Renderable::SetShareDBObject_I (DBObject_I *obj)
{
	mDBObject_I = obj;
}
//----------------------------------------------------------------------------
inline const DBObject_I *Renderable::GetShareDBObject_I () const
{
	return mDBObject_I;
}
//----------------------------------------------------------------------------
inline DBObject_I *Renderable::GetShareDBObject_I ()
{
	return mDBObject_I;
}
//----------------------------------------------------------------------------
inline void Renderable::SetIBOffset (int offset)
{
	mIBOffset = offset;
}
//----------------------------------------------------------------------------
inline int Renderable::GetIBOffset () const
{
	return mIBOffset;
}
//----------------------------------------------------------------------------
inline void Renderable::SetIBNumElements (int num)
{
	mIBNumElements = num;
}
//----------------------------------------------------------------------------
inline int Renderable::GetIBNumElements () const
{
	return mIBNumElements;
}
//----------------------------------------------------------------------------
inline void Renderable::SetUseShareBuffers (bool use)
{
	mIsUseShareBuffers = use;
}
//----------------------------------------------------------------------------
inline bool Renderable::IsUseShareBuffers () const
{
	return mIsUseShareBuffers;
}
//----------------------------------------------------------------------------
inline const Bound& Renderable::GetModelBound () const
{
    return mModelBound;
}
//----------------------------------------------------------------------------
inline Bound& Renderable::GetModelBound ()
{
    return mModelBound;
}
//----------------------------------------------------------------------------
inline void Renderable::AddRenderUsage (RenderUsage usage)
{
	mRenderUsageBits |= 1<<usage;
}
//----------------------------------------------------------------------------
inline void Renderable::RemoveRenderUsage (RenderUsage usage)
{
	mRenderUsageBits &= ~(1<<usage);
}
//----------------------------------------------------------------------------
inline unsigned int Renderable::GetRenderUsage ()
{
	return mRenderUsageBits;
}
//----------------------------------------------------------------------------
inline void Renderable::SetTransparent (bool transparent)
{
	mSortIndex = (mSortIndex&0xffff0000)|(transparent?1:0);
}
//----------------------------------------------------------------------------
inline bool Renderable::IsTransparent () const
{
	return (mSortIndex&1); 
}
//----------------------------------------------------------------------------
inline Renderable::RenderLayer Renderable::GetRenderLayer () const
{
	return mLayer;
}
//----------------------------------------------------------------------------
inline int Renderable::GetSubLayer () const
{
	return mSubLayer;
}
//----------------------------------------------------------------------------
inline unsigned int Renderable::GetSortIndex () const
{
	return mSortIndex;
}
//----------------------------------------------------------------------------
inline void Renderable::SetMaterialInstance (MaterialInstance* material)
{
    mMaterial = material;
}
//----------------------------------------------------------------------------
inline MaterialInstance* Renderable::GetMaterialInstance () const
{
    return mMaterial;
}
//----------------------------------------------------------------------------
inline Shine *Renderable::GetDefaultShine ()
{
	return mDefaultShine;
}
//----------------------------------------------------------------------------
inline void Renderable::SetBakeObject (bool bakeObject)
{
	mIsBackObject = bakeObject;
}
//----------------------------------------------------------------------------
inline bool Renderable::IsBakeObject () const
{
	return mIsBackObject;
}
//----------------------------------------------------------------------------
inline void Renderable::SetBakeTarget (bool bakeTarget)
{
	mIsBackTarget = bakeTarget;
}
//----------------------------------------------------------------------------
inline bool Renderable::IsBakeTarget () const
{
	return mIsBackTarget;
}
//----------------------------------------------------------------------------
inline const Shine *Renderable::GetDefaultShine () const
{
	return mDefaultShine;
}
//----------------------------------------------------------------------------
inline void Renderable::SetBakeSizeType (BakeSizeType type)
{
	mBakeSizeType = type;
}
//----------------------------------------------------------------------------
inline Renderable::BakeSizeType Renderable::GetBakeSizeType () const
{
	return mBakeSizeType;
}
//----------------------------------------------------------------------------
inline const std::string &Renderable::GetLightTexture () const
{
	return mLightTexPath;
}
//----------------------------------------------------------------------------
inline const std::string &Renderable::GetNormalTexture () const
{
	return mNormalTexPath;
}
//----------------------------------------------------------------------------
inline bool Renderable::IsUseLightTexture () const
{
	return mIsUseLightTexture;
}
//----------------------------------------------------------------------------
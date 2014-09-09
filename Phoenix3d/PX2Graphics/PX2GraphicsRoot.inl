/*
*
* ÎÄ¼þÃû³Æ	£º	PX2GraphicsRoot.inl
*
*/

//----------------------------------------------------------------------------
inline void GraphicsRoot::SetRect (const Rectf &rect)
{
	mRect = rect;
}
//----------------------------------------------------------------------------
inline const Rectf &GraphicsRoot::GetRect () const
{
	return mRect;
}
//----------------------------------------------------------------------------
inline void GraphicsRoot::SetSize (const Sizef &size)
{
	mSize = size;
}
//----------------------------------------------------------------------------
inline const Sizef &GraphicsRoot::GetSize () const
{
	return mSize;
}
//----------------------------------------------------------------------------
inline void GraphicsRoot::SetCamera (Camera *camera)
{
	mCamera = camera;
}
//----------------------------------------------------------------------------
inline PX2::Camera *GraphicsRoot::GetCamera()
{
	return mCamera;
}
//----------------------------------------------------------------------------
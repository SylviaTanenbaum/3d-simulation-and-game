/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Animation3DSkeleton.inl
*
*/

//----------------------------------------------------------------------------
inline void Animation3DSkeleton::SetTagName (const std::string &tagName)
{
	mTagName = tagName;
}
//----------------------------------------------------------------------------
inline const std::string &Animation3DSkeleton::GetTagName () const
{
	return mTagName;
}
//----------------------------------------------------------------------------
inline Node *Animation3DSkeleton::GetAnimObject ()
{
	return mAnimObject;
}
//----------------------------------------------------------------------------
inline Node *Animation3DSkeleton::GetAnimNode ()
{
	return mAnimNode;
}
//----------------------------------------------------------------------------
inline std::map<SkinController*, std::vector<Node*> > &Animation3DSkeleton
	::GetAnimUpdateNodes ()
{
	return mAnimUpdateNodes;
}
//----------------------------------------------------------------------------
inline std::list<KeyframeControllerPtr> &Animation3DSkeleton
	::GetNodeKeyframes ()
{
	return mKeyframeCtrls;
}
//----------------------------------------------------------------------------
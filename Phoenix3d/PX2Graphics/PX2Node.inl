/*
*
* �ļ�����	��	PX2Node.inl
*
*/

//----------------------------------------------------------------------------
inline void Node::SetDoPickPriority (bool doPickPriority)
{
	mIsDoPickPriority = doPickPriority;
}
//----------------------------------------------------------------------------
inline bool Node::IsDoPickPriority () const
{
	return mIsDoPickPriority;
}
//----------------------------------------------------------------------------
inline int Node::GetNumChildren () const
{
	return (int)mChild.size();
}
//----------------------------------------------------------------------------
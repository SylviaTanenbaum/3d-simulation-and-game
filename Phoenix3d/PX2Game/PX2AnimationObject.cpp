/*
*
* �ļ�����	��	PX2AnimationObject.cpp
*
*/

#include "PX2AnimationObject.hpp"
#include "PX2Character.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
AnimationObject::AnimationObject ()
	:
BlendTime(0.0f),
BlendWeight(0.0f),
TheCharacter(0)
{
}
//----------------------------------------------------------------------------
AnimationObject::~AnimationObject()
{
}
//----------------------------------------------------------------------------
void AnimationObject::Update (double appTime, double elapsedTime)
{
	BlendTime += (float)elapsedTime;
}
//----------------------------------------------------------------------------
void AnimationObject::BeforeRemove ()
{
	Movable *charMov = TheCharacter->GetMovable();
	Node *charNode = DynamicCast<Node>(charMov);

	if (charNode)
	{
		charNode->DetachChild(AnimNode);
	}

	TheCharacter = 0;
}
//----------------------------------------------------------------------------
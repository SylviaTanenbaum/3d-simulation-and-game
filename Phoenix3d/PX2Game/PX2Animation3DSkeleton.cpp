/*
*
* 文件名称	：	PX2Animation3DSkeleton.cpp
*
*/

#include "PX2Animation3DSkeleton.hpp"
#include "PX2Character.hpp"
#include "PX2ResourceManager.hpp"
#include "PX2Movable.hpp"
#include "PX2TriMesh.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Animation, Animation3DSkeleton);
PX2_IMPLEMENT_STREAM(Animation3DSkeleton);
PX2_IMPLEMENT_FACTORY(Animation3DSkeleton);
PX2_IMPLEMENT_DEFAULT_NAMES(Animation, Animation3DSkeleton);

//----------------------------------------------------------------------------
Animation3DSkeleton::Animation3DSkeleton (const std::string &name,
	const std::string &animTagName)
	:
Animation(Animation::AT_3DSKELETON),
mNumAnimUpdateNodes(0)
{
	SetName(name);
	SetTagName(animTagName);
}
//----------------------------------------------------------------------------
Animation3DSkeleton::~Animation3DSkeleton ()
{
}
//----------------------------------------------------------------------------
void Animation3DSkeleton::Stop ()
{
	Animation::Stop();
}
//----------------------------------------------------------------------------
bool Animation3DSkeleton::IsPlaying () const
{
	return Animation::IsPlaying();
}
//----------------------------------------------------------------------------
void Animation3DSkeleton::SetTime (float time)
{
	Animation::SetTime(time);
}
//----------------------------------------------------------------------------
void Animation3DSkeleton::SetFrequency (float frequency)
{
	Animation::SetFrequency(frequency);

	std::list<KeyframeControllerPtr>::iterator it = mKeyframeCtrls.begin();
	for (; it!=mKeyframeCtrls.end(); it++)
	{
		(*it)->Frequency = frequency;
	}
}
//----------------------------------------------------------------------------
void Animation3DSkeleton::SetFilename (const std::string &filename)
{
	if (filename.empty())
		return;

	Animation::SetFilename(filename);

	mAnimObject = DynamicCast<Node>(PX2_RM.BlockLoadCopy(filename));
	if (!mAnimObject)
		return;

	for (int i=0; i<mAnimObject->GetNumChildren(); i++)
	{
		Movable *mov = mAnimObject->GetChild(i);
		Node *node = DynamicCast<Node>(mov);
		Renderable *renderable = DynamicCast<Renderable>(mov);
		if (node && !renderable && !Character::IsNodeHasMesh(node) && node->GetNumValidChildren()>0)
		{
			mAnimNode = node;
		}
	}
	mAnimObject->DetachChild(mAnimNode);

	if (mCharacter && mCharacter->GetCurPlayingAnim()==this)
	{
		LetCharacterPlay();
	}
}
//----------------------------------------------------------------------------
void Animation3DSkeleton::SetPlayOnce (bool once)
{
	Animation::SetPlayOnce(once);

	std::list<KeyframeControllerPtr>::iterator it = mKeyframeCtrls.begin();
	for (; it!=mKeyframeCtrls.end(); it++)
	{
		(*it)->Repeat = once ? Controller::RT_CLAMP:Controller::RT_WRAP;
	}
}
//----------------------------------------------------------------------------
void Animation3DSkeleton::OnPlay (Character *character)
{
	if (0==mNumAnimUpdateNodes || mKeyframeCtrls.empty())
	{
		SetCharacter(mCharacter);
	}

	if (0==mNumAnimUpdateNodes || mKeyframeCtrls.empty())
	{
		return;
	}

	Animation::OnPlay(character);

	Movable *charMov = character->GetMovable();
	Node *charNode = DynamicCast<Node>(charMov);

	if (mAnimNode)
	{
		charNode->AttachChild(mAnimNode);

		mAnimNode->ResetPlay();

		SetFrequency(GetFrequency());
		SetPlayOnce(IsPlayOnce());

		charMov->Update(GetTimeInSeconds());
	}
}
//----------------------------------------------------------------------------
void Animation3DSkeleton::SetCharacter (Character *character)
{
	Animation::SetCharacter(character);

	if (!character)
		return;

	Movable *charMov = character->GetMovable();
	const std::string &modelTagName = character->GetModelTagName();
	Node *charNode = DynamicCast<Node>(charMov);
	std::list<SkinControllerPtr> &skinCtrls = character->GetSkinCtrls();

	if (mAnimNode)
	{
		mKeyframeCtrls.clear();
		CalNodeKeyframeControllers(mAnimNode, mKeyframeCtrls);

		std::list<SkinControllerPtr>::iterator it = skinCtrls.begin();
		for (; it!=skinCtrls.end(); it++)
		{
			CalAnimUpdateNodes(*it, mTagName, modelTagName);
		}
	}
}
//----------------------------------------------------------------------------
void Animation3DSkeleton::OnRemove (Character *character)
{
	Animation::OnRemove(character);
}
//----------------------------------------------------------------------------
void Animation3DSkeleton::CalAnimUpdateNodes (SkinController *skinCtrl,
	const std::string &animNodeTagName, const std::string &modelTagName)
{
	mNumAnimUpdateNodes = 0;

	if (mAnimNode)
	{
		int numBones = skinCtrl->GetNumBones();
		mAnimUpdateNodes[skinCtrl].resize(numBones);

		for (int i=0; i<numBones; i++)
		{
			std::string boneName = skinCtrl->GetBoneNames()[i];

			if (!modelTagName.empty())
				boneName = boneName.substr(modelTagName.length(), boneName.length()-modelTagName.length());
			boneName = animNodeTagName + boneName;

			std::vector<Object *> objs;
			mAnimNode->GetAllObjectsByName(boneName, objs);
			if (1 == objs.size())
			{
				Node *node = DynamicCast<Node>(objs[0]);
				if (node)
				{
					mAnimUpdateNodes[skinCtrl][i] = node;
					mNumAnimUpdateNodes++;
				}
				else
				{
					assertion(false, "%s must be a bone.\n", boneName.c_str());
				}
			}
			else if (objs.size() >= 2)
			{
				assertion(false, "bones with same name %s .\n", boneName.c_str());
			}
		}
	}
}
//----------------------------------------------------------------------------
void Animation3DSkeleton::CalNodeKeyframeControllers (Movable *movable, 
	std::list<KeyframeControllerPtr> &list)
{
	for (int i=0; i<movable->GetNumControllers(); i++)
	{
		KeyframeController *kfCtrl = DynamicCast<KeyframeController>(movable->GetController(i));
		if (kfCtrl)
		{
			list.push_back(kfCtrl);
		}
	}

	Node *node = DynamicCast<Node>(movable);
	if (node)
	{
		for (int i=0; i<node->GetNumChildren(); i++)
		{
			CalNodeKeyframeControllers(node->GetChild(i), list);
		}
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Property
//----------------------------------------------------------------------------
void Animation3DSkeleton::RegistProperties ()
{
	Animation::RegistProperties();

	AddPropertyClass("Animation3DSkeleton");

	AddProperty("TagName", PT_STRING, GetTagName());
}
//----------------------------------------------------------------------------
void Animation3DSkeleton::OnPropertyChanged (const PropertyObject &obj)
{
	Animation::OnPropertyChanged(obj);

	if ("TagName" == obj.Name)
	{
		SetTagName(PX2_ANY_AS(obj.Data, std::string));
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
Animation3DSkeleton::Animation3DSkeleton (LoadConstructor value)
	:
Animation(value),
mNumAnimUpdateNodes(0)
{
}
//----------------------------------------------------------------------------
void Animation3DSkeleton::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Animation::Load(source);
	PX2_VERSION_LOAD(source);

	source.ReadString(mTagName);

	PX2_END_DEBUG_STREAM_LOAD(Animation3DSkeleton, source);
}
//----------------------------------------------------------------------------
void Animation3DSkeleton::Link (InStream& source)
{
	Animation::Link(source);
}
//----------------------------------------------------------------------------
void Animation3DSkeleton::PostLink ()
{
	Animation::PostLink();
}
//----------------------------------------------------------------------------
bool Animation3DSkeleton::Register (OutStream& target) const
{
	if (Animation::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void Animation3DSkeleton::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Animation::Save(target);
	PX2_VERSION_SAVE(target);

	target.WriteString(mTagName);

	PX2_END_DEBUG_STREAM_SAVE(Animation3DSkeleton, target);
}
//----------------------------------------------------------------------------
int Animation3DSkeleton::GetStreamingSize (Stream &stream) const
{
	int size = Animation::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);
	size += PX2_STRINGSIZE(mTagName);

	return size;
}
//----------------------------------------------------------------------------
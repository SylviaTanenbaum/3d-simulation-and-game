/*
*
* �ļ�����	��	PX2Node.cpp
*
*/

#include "PX2Node.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Movable, Node);
PX2_IMPLEMENT_STREAM(Node);
PX2_IMPLEMENT_FACTORY(Node);

//----------------------------------------------------------------------------
Node::Node ()
	:
mIsDoPickPriority(false),
mIsNeedCalUpdateChild(true)
{
}
//----------------------------------------------------------------------------
Node::~Node ()
{
    std::vector<MovablePtr>::iterator iter = mChild.begin();
    std::vector<MovablePtr>::iterator end = mChild.end();
    for (/**/; iter != end; ++iter)
    {
        if (*iter)
        {
            (*iter)->SetParent(0);
            *iter = 0;
        }
    }
}
//----------------------------------------------------------------------------
void Node::Play ()
{
	Movable::Play();

	for (int i=0; i<GetNumChildren(); i++)
	{
		if (mChild[i] && !mChild[i]->IsSelfCtrled())
		{
			mChild[i]->Play();
		}
	}
}
//----------------------------------------------------------------------------
bool Node::IsPlaying () const
{
	if (Movable::IsPlaying())
		return true;

	for (int i=0; i<GetNumChildren(); i++)
	{
		if (mChild[i] && !mChild[i]->IsSelfCtrled())
		{
			if (mChild[i]->IsPlaying())
				return true;
		}
	}

	return false;
}
//----------------------------------------------------------------------------
void Node::Stop ()
{
	Movable::Stop();

	for (int i=0; i<GetNumChildren(); i++)
	{
		if (mChild[i] && !mChild[i]->IsSelfCtrled())
		{
			mChild[i]->Stop();
		}
	}
}
//----------------------------------------------------------------------------
void Node::Reset ()
{
	Movable::Reset();

	for (int i=0; i<GetNumChildren(); i++)
	{
		if (mChild[i] && !mChild[i]->IsSelfCtrled())
		{
			mChild[i]->Reset();
		}
	}
}
//----------------------------------------------------------------------------
int Node::AttachChild (Movable* child)
{
    if (!child)
    {
        assertion(false, "You cannot attach null children to a node.\n");
        return -1;
    }

    if (child->GetParent())
    {
        assertion(false, "The child already has a parent.\n");
        return -1;
    }

	mIsNeedCalUpdateChild = true;

    child->SetParent(this);
	child->OnAttach();

	// �����Ӳ��뵽��һ������λ��
    std::vector<MovablePtr>::iterator iter = mChild.begin();
    std::vector<MovablePtr>::iterator end = mChild.end();
    for (int i = 0; iter != end; ++iter, ++i)
    {
        if (*iter == 0)
        {
            *iter = child;
            return i;
        }
    }

	// ���п�λ�������ˣ������Ӳ������ĩβ
    const int numChildren = (int)mChild.size();
    mChild.push_back(child);
    return numChildren;
}
//----------------------------------------------------------------------------
int Node::DetachChild (Movable* child)
{
    if (child)
    {
        std::vector<MovablePtr>::iterator iter = mChild.begin();
        std::vector<MovablePtr>::iterator end = mChild.end();
        for (int i = 0; iter != end; ++iter, ++i)
        {
            if (*iter == child)
            {
                (*iter)->SetParent(0);
				(*iter)->OnDetach();
                *iter = 0;

				mIsNeedCalUpdateChild = true;

                return i;
            }
        }
    }
    return -1;
}
//----------------------------------------------------------------------------
bool Node::DetachChildByName (const std::string &name)
{
	for (int i=0; i<(int)mChild.size(); i++)
	{
		MovablePtr child = mChild[i];

		if (child != 0 && child->GetName() == name)
		{
			child->SetParent(0);
			child->OnDetach();
			mChild[i] = 0;

			mIsNeedCalUpdateChild = true;

			return true;
		}

	}

	return false;
}
//----------------------------------------------------------------------------
MovablePtr Node::DetachChildAt (int i)
{
    if (0 <= i && i < (int)mChild.size())
    {
        MovablePtr child = mChild[i];
        if (child)
        {
            child->SetParent(0);
			child->OnDetach();
            mChild[i] = 0;

			mIsNeedCalUpdateChild = true;
        }
        return child;
    }
    return 0;
}
//----------------------------------------------------------------------------
void Node::DetachAllChildren ()
{
	for (int i=0; i<(int)mChild.size(); i++)
	{
		 MovablePtr child = mChild[i];

		 if (child)
		 {
			 child->SetParent(0);
			 child->OnDetach();
			 mChild[i] = 0;
		 }
	}

	mIsNeedCalUpdateChild = true;
}
//----------------------------------------------------------------------------
int Node::GetNumValidChildren () const
{
	int num = 0;

	for (int i=0; i<(int)mChild.size(); i++)
	{
		if (mChild[i])
			num++;
	}

	return num;
}
//----------------------------------------------------------------------------
MovablePtr Node::SetChild (int i, Movable* child)
{
    if (child)
    {
        assertion(!child->GetParent(), "The child already has a parent.\n");
    }

	mIsNeedCalUpdateChild = true;

    const int numChildren = (int)mChild.size();
    if (0 <= i && i < numChildren)
    {
		// ���ɵĺ����Ƴ�
        MovablePtr previousChild = mChild[i];
        if (previousChild)
        {
            previousChild->SetParent(0);
        }

		// �����µĺ��ӵ���λ
        if (child)
        {
            child->SetParent(this);
        }

        mChild[i] = child;
        return previousChild;
    }

	// ���ӳ�����Χ��������뵽���Ӷ���ĩβ
    if (child)
    {
        child->SetParent(this);
    }
    mChild.push_back(child);

    return 0;
}
//----------------------------------------------------------------------------
MovablePtr Node::GetChild (int i)
{
    if (0 <= i && i < (int)mChild.size())
    {
        return mChild[i];
    }
    return 0;
}
//----------------------------------------------------------------------------
MovablePtr Node::GetChildByName (const std::string &name)
{
	for (int i=0; i<(int)mChild.size(); i++)
	{
		MovablePtr child = mChild[i];

		if (child != 0 && child->GetName() == name)
		{
			return child;
		}
	}

	return 0;
}
//----------------------------------------------------------------------------
void Node::SetAlpha (float alpha)
{
	Movable::SetAlpha(alpha);

	for (int i=0; i<GetNumChildren(); i++)
	{
		if (mChild[i] != NULL && !mChild[i]->IsAlphaSelfCtrled())
		{
			mChild[i]->SetAlpha(alpha);
		}
	}
}
//----------------------------------------------------------------------------
void Node::SetColor (const Float3 &color)
{
	Movable::SetColor(color);

	for (int i=0; i<GetNumChildren(); i++)
	{
		if (mChild[i] != NULL && !mChild[i]->IsColorSelfCtrled())
		{
			mChild[i]->SetColor(color);
		}
	}
}
//----------------------------------------------------------------------------
void Node::OnNotPicked (int pickInfo)
{
	for (int i=0; i<(int)mChild.size(); i++)
	{
		if (mChild[i])
		{
			mChild[i]->OnNotPicked(pickInfo);
		}
	}
}
//----------------------------------------------------------------------------
bool MovableUpdateLessThan (const Movable *mov0,
	const Movable *mov1)
{
	int priority0 = mov0->GetUpdatePriority();
	int priority1 = mov1->GetUpdatePriority();

	if (priority0 == priority1)
		return priority0 < priority1;

	return mov0 < mov1;
}
//----------------------------------------------------------------------------
void Node::UpdateWorldData (double applicationTime)
{
    Movable::UpdateWorldData(applicationTime);

	if (mIsNeedCalUpdateChild)
	{
		mUpdateChild.clear();
		for (int i=0; i<mChild.size(); i++)
		{
			if (mChild[i])
				mUpdateChild.push_back(mChild[i]);
		}

		std::sort(mUpdateChild.begin(), mUpdateChild.end(), MovableUpdateLessThan);

		mIsNeedCalUpdateChild = false;
	}

	for (int i=0; i<(int)mUpdateChild.size(); i++)
	{
		mUpdateChild[i]->Update(applicationTime, false);
	}
}
//----------------------------------------------------------------------------
void Node::UpdateWorldBound ()
{
    if (!WorldBoundIsCurrent)
    {
        bool foundFirstBound = false;

		for (int i=0; i<(int)mChild.size(); i++)
		{
			Movable *child = mChild[i];

			if (child)
			{
				if (foundFirstBound)
				{
					// �����к��ӵĽڵ��Χ���ںϵ�һ����Ϊ��ǰ�ڵ�İ�Χ��
					WorldBound.GrowToContain(child->WorldBound);
				}
				else
				{
					// ���Ƚ���һ�����ӵİ�Χ����Ϊ�ڵ�İ�Χ��
					foundFirstBound = true;
					WorldBound = child->WorldBound;
				}
			}
		}

		if (!foundFirstBound)
		{
			WorldBound.SetCenter(APoint::ORIGIN);
			WorldBound.SetRadius(0.0f);
		}
    }
}
//----------------------------------------------------------------------------
void Node::GetVisibleSet (Culler& culler, bool noCull)
{
    std::vector<MovablePtr>::iterator iter = mChild.begin();
    std::vector<MovablePtr>::iterator end = mChild.end();
    for (/**/; iter != end; ++iter)
    {
        Movable* child = *iter;
        if (child)
        {
            child->OnGetVisibleSet(culler, noCull);
        }
    }
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Name support.
//----------------------------------------------------------------------------
Object* Node::GetObjectByName (const std::string& name)
{
    Object* found = Movable::GetObjectByName(name);
    if (found)
    {
        return found;
    }

    const int numChildren = (int)mChild.size();
    for (int i = 0; i < numChildren; ++i)
    {
        PX2_GET_OBJECT_BY_NAME(mChild[i], name, found);
    }

    return 0;
}
//----------------------------------------------------------------------------
void Node::GetAllObjectsByName (const std::string& name,
    std::vector<Object*>& objects)
{
    Movable::GetAllObjectsByName(name, objects);

    const int numChildren = (int)mChild.size();
    for (int i = 0; i < numChildren; ++i)
    {
        PX2_GET_ALL_OBJECTS_BY_NAME(mChild[i], name, objects);
    }
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Property
//----------------------------------------------------------------------------
void Node::RegistProperties ()
{
	Movable::RegistProperties();

	AddPropertyClass("Node");

	AddProperty("NumChildren", Object::PT_INT, Any(GetNumChildren()), 
		false);
}
//----------------------------------------------------------------------------
void Node::OnPropertyChanged (const PropertyObject &obj)
{
	Movable::OnPropertyChanged(obj);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// �־û�֧��
//----------------------------------------------------------------------------
Node::Node (LoadConstructor value)
    :
    Movable(value),
	mIsDoPickPriority(false),
	mIsNeedCalUpdateChild(true)
{
}
//----------------------------------------------------------------------------
void Node::Load (InStream& source)
{
    PX2_BEGIN_DEBUG_STREAM_LOAD(source);

    Movable::Load(source);
	PX2_VERSION_LOAD(source);

    int numChildren;
    source.Read(numChildren);
    if (numChildren > 0)
    {
        mChild.resize(numChildren);
        source.ReadPointerVV(numChildren, &mChild[0]);
    }

    PX2_END_DEBUG_STREAM_LOAD(Node, source);
}
//----------------------------------------------------------------------------
void Node::Link (InStream& source)
{
    Movable::Link(source);

    const int numChildren = (int)mChild.size();
    for (int i = 0; i < numChildren; ++i)
    {
        if (mChild[i])
        {
            source.ResolveLink(mChild[i]);
            SetChild(i, mChild[i]);
        }
    }
}
//----------------------------------------------------------------------------
void Node::PostLink ()
{
    Movable::PostLink();
}
//----------------------------------------------------------------------------
bool Node::Register (OutStream& target) const
{
    if (Movable::Register(target))
    {
        const int numChildren = (int)mChild.size();
        for (int i = 0; i < numChildren; ++i)
        {
            if (mChild[i])
            {
                target.Register(mChild[i]);
            }
        }
        return true;
    }
    return false;
}
//----------------------------------------------------------------------------
void Node::Save (OutStream& target) const
{
    PX2_BEGIN_DEBUG_STREAM_SAVE(target);

    Movable::Save(target);
	PX2_VERSION_SAVE(target);

    const int numChildren = (int)mChild.size();
    target.Write(numChildren);
    for (int i = 0; i < numChildren; ++i)
    {
        if (mChild[i])
        {
            target.WritePointer(mChild[i]);
        }
        else
        {
            target.WritePointer((Movable*)0);
        }
    }


    PX2_END_DEBUG_STREAM_SAVE(Node, target);
}
//----------------------------------------------------------------------------
int Node::GetStreamingSize (Stream &stream) const
{
    int size = Movable::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);
    int numChildren = (int)mChild.size();
    size += sizeof(numChildren);
    size += numChildren*PX2_POINTERSIZE(mChild[0]);
    return size;
}
//----------------------------------------------------------------------------

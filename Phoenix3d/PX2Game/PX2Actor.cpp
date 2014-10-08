/*
*
* �ļ�����	��	PX2Actor.cpp
*
*/

#include "PX2Actor.hpp"
#include "PX2Scene.hpp"
#include "PX2VertexColor4Material.hpp"
#include "PX2VertexBufferAccessor.hpp"
#include "PX2Renderer.hpp"
#include "PX2ScriptManager.hpp"
#include "PX2Project.hpp"
#include "PX2ResourceManager.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI_V(PX2, Gameable, Actor, 2);
PX2_IMPLEMENT_STREAM(Actor);
PX2_IMPLEMENT_FACTORY(Actor);

//----------------------------------------------------------------------------
Actor::Actor ()
	:
mID(0),
mTypeID(0),
mGroup(0),
mScene(0),
mSceneContainer(0),
mSceneContainerIndex(-1),
mIsStaticType(false),
mIsBuilding(false),
mIsVisible(true),
mActorTransparent(1.0f),
mIsShareVIM(false),
mMoveableResHandle(0),
mMovable(0),
mHelpMovable(0),
mIsShowHelpMovable(false),
mIsStopSpeed(false),
mArriveRange(1.0f),
mSelfRadius(1.0f),
mHeight(1.0f),
mMass(1.0f),
mIsSmoothOn(true),
mHeadingSmoother(0),
mIsBakeObject(true),
mIsBakeTarget(true)
{
	PX2_INIT_PM_F(MaxSpeed);

	mScale = APoint(1.0f, 1.0f, 1.0f);
	mHeading = AVector::UNIT_Y;

	mIsGridMoveOn = false;
	mGridMoveBehavior = new0 GridMoveBehavior(this);
	mHeadingSmoother = new0 Smoother<AVector>(24, AVector::ZERO);

	SetName("NoName");

	SetID(Scene::GetNextID());
}
//----------------------------------------------------------------------------
Actor::~Actor ()
{
	delete0(mHeadingSmoother);
}
//----------------------------------------------------------------------------
void Actor::Update (double appSeconds, double elapsedSeconds)
{
	if(IsGridMoveOn())
	{
		if ((int)mStopSpeedTags.size() > 0)
		{
			StopSpeed(true);
		}
		else
		{
			StopSpeed(false);
		}

		if (mIsStopSpeed)
		{
			mGridMoveBehavior->SetSpeed(0.0f);
			SetVelocity(AVector::ZERO);
		}
		else
		{
			mGridMoveBehavior->SetSpeed(GetMMaxSpeed());		

			APoint toPos;
			AVector direction;
			if (mGridMoveBehavior->Update((float)elapsedSeconds, toPos, direction))
			{
				OnUpdateGoToPosition(toPos);

				float modifiedMaxSpeed = GetMMaxSpeed();
				AVector vec =  direction * modifiedMaxSpeed;
				SetVelocity(vec);

				if (mVelocity != AVector::ZERO)
				{
					direction.Normalize();
					SetHeading(direction);
				}
			}
		}

		if (mIsSmoothOn)
		{
			AVector smoothHeading = mHeadingSmoother->Update(mHeading);
			SetSmoothHeading(smoothHeading);
		}
	}
}
//----------------------------------------------------------------------------
void Actor::SetBakeObject (bool bakeObject)
{
	mIsBakeObject = bakeObject;

	if (mMovable)
	{
		_SetBakeObject(mMovable, bakeObject);
	}
}
//----------------------------------------------------------------------------
void Actor::SetBakeTarget (bool bakeTarget)
{
	mIsBakeTarget = bakeTarget;

	if (mMovable)
	{
		_SetBakeTarget(mMovable, bakeTarget);
	}
}
//----------------------------------------------------------------------------
void Actor::_SetBakeObject (Movable *mov, bool bakeObject)
{
	Renderable *renderable = DynamicCast<Renderable>(mov);
	Node *node = DynamicCast<Node>(mov);

	if (renderable)
	{
		renderable->SetBakeObject(bakeObject);
	}
	else if (node)
	{
		for (int i=0; i<node->GetNumChildren(); i++)
		{
			Movable *mov = node->GetChild(i);
			if (mov)
			{
				_SetBakeObject(mov, bakeObject);
			}
		}
	}
}
//----------------------------------------------------------------------------
void Actor::ClearBakeTextures ()
{
	mBakeTextures.clear();
}
//----------------------------------------------------------------------------
void Actor::AddBakeTxture (const std::string &name, const std::string &bakeTexture)
{
	mBakeTextures[name] = bakeTexture;
}
//----------------------------------------------------------------------------
void Actor::SetUseLightTexture (bool use)
{
	if (IsBakeTarget())
	{
		std::map<std::string, std::string>::iterator it = mBakeTextures.begin();
		for (; it!=mBakeTextures.end(); it++)
		{
			const std::string &filename = it->first;
			const std::string &texFilename = it->second;

			TriMesh *mesh = DynamicCast<TriMesh>(mMovable->GetObjectByName(filename));
			Texture2D *tex2D = DynamicCast<Texture2D>(PX2_RM.BlockLoad(texFilename));
			if (mesh && tex2D)
			{
				mesh->SetLightTexture(tex2D);
				mesh->SetUseLightTexture(use, tex2D);
			}
		}
	}
}
//----------------------------------------------------------------------------
void Actor::_SetBakeTarget (Movable *mov, bool bakeTarget)
{
	Renderable *renderable = DynamicCast<Renderable>(mov);
	Node *node = DynamicCast<Node>(mov);

	if (renderable)
	{
		renderable->SetBakeTarget(bakeTarget);
	}
	else if (node)
	{
		for (int i=0; i<node->GetNumChildren(); i++)
		{
			Movable *mov = node->GetChild(i);
			if (mov)
			{
				_SetBakeTarget(mov, bakeTarget);
			}
		}
	}
}
//----------------------------------------------------------------------------
void Actor::SaveToXMLNode (XMLNode nodeParent)
{
	XMLNode nodeClass = nodeParent.NewChild("Class");
	nodeClass.SetAttributeString("Type", "Actor");

	Gameable::SaveToXMLNode(nodeClass);

	XMLNode nodeProperty = nodeClass.NewChild("Property");
	nodeProperty.SetAttributeInt("ID", GetID());
	nodeProperty.SetAttributeInt("TypeID", GetTypeID());
	nodeProperty.SetAttributeFloat("SelfRadius", GetSelfRadius());
	nodeProperty.SetAttributeFloat("Height", GetHeight());
	nodeProperty.SetAttributeFloat("BaseMaxSpeed", GetMaxSpeed());
}
//----------------------------------------------------------------------------
void Actor::LoadFromXMLNode (XMLNode node)
{
	XMLNode nodeBaseClass = node.GetChild("Class");
	if (!nodeBaseClass.IsNull())
	{
		Gameable::LoadFromXMLNode(nodeBaseClass);
	}
	else
	{
		assertion(false, "");
	}

	XMLNode nodeProperty = node.GetChild("Property");
	if (!nodeProperty.IsNull())
	{
		if (nodeProperty.HasAttribute("SelfRadius"))
		{
			SetSelfRadius(nodeProperty.AttributeToFloat("SelfRadius"));
		}

		if (nodeProperty.HasAttribute("Height"))
		{
			SetHeight(nodeProperty.AttributeToFloat("Height"));
		}

		if (nodeProperty.HasAttribute("BaseMaxSpeed"))
		{
			SetMaxSpeed(nodeProperty.AttributeToFloat("BaseMaxSpeed"));
			CalMMaxSpeed();
		}
	}
	else
	{
		assertion(false, "");
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ����֧��
//----------------------------------------------------------------------------
Object* Actor::GetObjectByName (const std::string& name)
{
	Object* found = Gameable::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	if (mMovable)
	{
		return mMovable->GetObjectByName(name);
	}

	return 0;
}
//----------------------------------------------------------------------------
void Actor::GetAllObjectsByName (const std::string& name,
	std::vector<Object*>& objects)
{
	Gameable::GetAllObjectsByName(name, objects);

	PX2_GET_ALL_OBJECTS_BY_NAME(mMovable, name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Property
//----------------------------------------------------------------------------
void Actor::RegistProperties ()
{
	Gameable::RegistProperties();

	AddPropertyClass("Actor");

	AddProperty("MovableFilename", Object::PT_STRING, GetMoveableFilename(), false);
	AddProperty("IsShareVIM", Object::PT_BOOL, IsShareVIM(), false);

	AddProperty("Position", Object::PT_APOINT3, Any(mPosition));
	AddProperty("Rotation", Object::PT_APOINT3, Any(mRotation));
	AddProperty("Scale", Object::PT_APOINT3, Any(mScale));

	AddProperty("Heading", Object::PT_AVECTOR3, GetHeading());

	AddProperty("SelfRadius", PT_FLOAT, GetSelfRadius());
	AddProperty("Height", PT_FLOAT, GetHeight());
	AddProperty("BaseMaxSpeed", PT_FLOAT, GetMaxSpeed());
	AddProperty("ModifiedMaxSpeed", PT_FLOAT, GetMMaxSpeed(), false);
	AddProperty("ShowHelpMovable", PT_BOOL, IsHelpMovableShow());

	AddProperty("IsBakeObject", PT_BOOL, IsBakeObject());
	AddProperty("IsBakeTarget", PT_BOOL, IsBakeTarget());
}
//----------------------------------------------------------------------------
void Actor::OnPropertyChanged (const PropertyObject &obj)
{
	Gameable::OnPropertyChanged(obj);

	if ("MovableFilename" == obj.Name)
	{
		//SetMovableFilename(PX2_ANY_AS(obj.Data, std::string), true);
	}
	else if ("Scale" == obj.Name)
	{
		APoint scale = PX2_ANY_AS(obj.Data, APoint);
		if (0.0f == scale.X())
		{
			scale.X() = 0.00001f;
		}
		else if (0.0f == scale.Y())
		{
			scale.Y() = 0.00001f;
		}
		else if (0.0f == scale.Z())
		{
			scale.Z() = 0.00001f;
		}
		SetScale(scale);
	}
	else if ("Rotation" == obj.Name)
	{
		SetRotation(PX2_ANY_AS(obj.Data, APoint));
	}
	else if ("Position" == obj.Name)
	{
		SetPosition(PX2_ANY_AS(obj.Data, APoint));
	}
	else if ("Heading" == obj.Name)
	{
		SetHeading(PX2_ANY_AS(obj.Data, AVector));
	}
	else if ("SelfRadius" == obj.Name)
	{
		SetSelfRadius(PX2_ANY_AS(obj.Data, float));
	}
	else if ("Height" == obj.Name)
	{
		SetHeight(PX2_ANY_AS(obj.Data, float));
	}
	else if ("BaseMaxSpeed" == obj.Name)
	{
		SetMaxSpeed(PX2_ANY_AS(obj.Data, float));
	}
	else if ("ShowHelpMovable" == obj.Name)
	{
		ShowHelpMovable(PX2_ANY_AS(obj.Data, bool));
	}
	else if ("IsBakeObject" == obj.Name)
	{
		SetBakeObject(PX2_ANY_AS(obj.Data, bool));
	}
	else if ("IsBakeTarget" == obj.Name)
	{
		SetBakeTarget(PX2_ANY_AS(obj.Data, bool));
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// �־û�֧��
//----------------------------------------------------------------------------
Actor::Actor (LoadConstructor value)
	:
Gameable(value),
	mID(1),
	mTypeID(0),
	mGroup(0),
	mScene(0),
	mSceneContainer(0),
	mSceneContainerIndex(-1),
	mIsVisible(true),
	mActorTransparent(1.0f),
	mMoveableResHandle(0),
	mIsShareVIM(false),
	mMovable(0),
	mHelpMovable(0),
	mIsShowHelpMovable(false),
	mIsStaticType(false),
	mIsBuilding(false),
	mSelfRadius(1.0f),
	mHeight(1.0f),
	mMaxSpeed(0.0f),
	mMMaxSpeed(0.0f),
	mIsStopSpeed(false),
	mArriveRange(1.0f),
	mMass(1.0f),
	mIsSmoothOn(true),
	mHeadingSmoother(0),
	mIsBakeObject(true),
	mIsBakeTarget(true)
{
	SetID(Scene::GetNextID());

	PX2_INIT_PM_F(MaxSpeed);

	mIsGridMoveOn = false;
	mGridMoveBehavior = new0 GridMoveBehavior(this);
	mHeadingSmoother = new0 Smoother<AVector>(24, AVector::ZERO);

	mScale = APoint(1.0f, 1.0f, 1.0f);
	mHeading = AVector::UNIT_Y;
}
//----------------------------------------------------------------------------
void Actor::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Gameable::Load(source);
	PX2_VERSION_LOAD(source);

	// ��¼һЩ������Ϣ
	
	source.ReadBool(mIsVisible);
	source.Read(mActorTransparent);

	source.ReadBool(mIsShareVIM);
	source.ReadString(mMoveableFilename);
	if (!mMoveableFilename.empty())
	{
		Movable *mov = 0;
		source.ReadPointer(mov);
	}
	else
	{
		source.ReadPointer(mMovable);
	}
	source.ReadPointer(mHelpMovable);
	source.ReadBool(mIsShowHelpMovable);
	// mScene�������棬������Scene::Link�е���Scene::AddChild�����á�

	source.ReadAggregate(mScale);
	source.ReadAggregate(mRotation);
	source.ReadAggregate(mPosition);

	source.Read(mSelfRadius);
	source.Read(mHeight);

	source.Read(mMass);

	int readedVersion = GetReadedVersion();
	if (1 <= readedVersion)
	{
		source.ReadBool(mIsBakeObject);
		source.ReadBool(mIsBakeTarget);
	}

	if (2 <= readedVersion)
	{
		int numLightTex = 0;
		source.Read(numLightTex);
		for (int i=0; i<numLightTex; i++)
		{
			std::string meshName;
			std::string lightTexFilename;
			source.ReadString(meshName);
			source.ReadString(lightTexFilename);

			mBakeTextures[meshName] = lightTexFilename;
		}
	}

	PX2_END_DEBUG_STREAM_LOAD(Actor, source);
}
//----------------------------------------------------------------------------
void Actor::Link (InStream& source)
{
	Gameable::Link(source);

	if (mMoveableFilename.empty())
	{
		source.ResolveLink(mMovable);
	}
	else
	{
		SetMovableFilename(mMoveableFilename, mIsShareVIM);
	}

	source.ResolveLink(mHelpMovable);
}
//----------------------------------------------------------------------------
void Actor::PostLink ()
{
	Gameable::PostLink();
}
//----------------------------------------------------------------------------
bool Actor::Register (OutStream& target) const
{
	if (Gameable::Register(target))
	{
		if (mMoveableFilename.empty())
		{
			target.Register(mMovable);
		}
		target.Register(mHelpMovable);

		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void Actor::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Gameable::Save(target);
	PX2_VERSION_SAVE(target);

	target.WriteBool(mIsVisible);
	target.Write(mActorTransparent);

	target.WriteBool(mIsShareVIM);
	target.WriteString(mMoveableFilename);
	if (!mMoveableFilename.empty())
	{
		Movable *mov = 0;
		target.WritePointer(mov);
	}
	else
	{
		target.WritePointer(mMovable);
	}
	target.WritePointer(mHelpMovable);
	target.WriteBool(mIsShowHelpMovable);

	target.WriteAggregate(mScale);
	target.WriteAggregate(mRotation);
	target.WriteAggregate(mPosition);

	target.Write(mSelfRadius);
	target.Write(mHeight);

	target.Write(mMass);

	target.WriteBool(mIsBakeObject);
	target.WriteBool(mIsBakeTarget);

	int numBakeTexs = (int)mBakeTextures.size();
	target.Write(numBakeTexs);
	std::map<std::string, std::string>::const_iterator it = mBakeTextures.begin();
	for (; it!=mBakeTextures.end(); it++)
	{
		target.WriteString(it->first);
		target.WriteString(it->second);
	}

	PX2_END_DEBUG_STREAM_SAVE(Actor, target);
}
//----------------------------------------------------------------------------
int Actor::GetStreamingSize (Stream &stream) const
{
	int size = Gameable::GetStreamingSize(stream);

	size += PX2_VERSION_SIZE(mVersion);

	size += PX2_BOOLSIZE(mIsVisible);
	size += sizeof(mActorTransparent);

	size += PX2_BOOLSIZE(mIsShareVIM);
	size += PX2_STRINGSIZE(mMoveableFilename);
	size += PX2_POINTERSIZE(mMovable);
	size += PX2_POINTERSIZE(mHelpMovable);
	size += PX2_BOOLSIZE(mIsShowHelpMovable);

	size += sizeof(mScale);
	size += sizeof(mRotation);
	size += sizeof(mPosition);

	size += sizeof(mSelfRadius);
	size += sizeof(mHeight);

	size += sizeof(mMass);

	if (stream.IsIn())
	{
		int readedVersion = GetReadedVersion();

		if (1 <= readedVersion)
		{
			size += PX2_BOOLSIZE(mIsBakeObject);
			size += PX2_BOOLSIZE(mIsBakeTarget);
		}

		if (2 <= readedVersion)
		{
			int numBakeTexs = (int)mBakeTextures.size();
			size += sizeof(numBakeTexs);
			std::map<std::string, std::string>::const_iterator it = mBakeTextures.begin();
			for (; it!=mBakeTextures.end(); it++)
			{
				size += PX2_STRINGSIZE(it->first);
				size += PX2_STRINGSIZE(it->second);
			}
		}
	}
	else
	{
		size += PX2_BOOLSIZE(mIsBakeObject);
		size += PX2_BOOLSIZE(mIsBakeTarget);

		int numBakeTexs = (int)mBakeTextures.size();
		size += sizeof(numBakeTexs);
		std::map<std::string, std::string>::const_iterator it = mBakeTextures.begin();
		for (; it!=mBakeTextures.end(); it++)
		{
			size += PX2_STRINGSIZE(it->first);
			size += PX2_STRINGSIZE(it->second);
		}
	}

	return size;
}
//----------------------------------------------------------------------------
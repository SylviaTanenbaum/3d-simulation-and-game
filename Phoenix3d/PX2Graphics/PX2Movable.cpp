/*
*
* �ļ�����	��	PX2Movable.cpp
*
*/

#include "PX2Movable.hpp"
#include "PX2Culler.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI_V(PX2, Controlledable, Movable, 2);
PX2_IMPLEMENT_STREAM(Movable);
PX2_IMPLEMENT_ABSTRACT_FACTORY(Movable);

//----------------------------------------------------------------------------
Movable::Movable ()
    :
    WorldTransformIsCurrent(false),
    WorldBoundIsCurrent(false),
    Culling(CULL_DYNAMIC),
    mParent(0),
	mIsAlphaSelfCtrled(false),
	mAlpha(1.0f),
	mIsColorSelfCtrled(false),
	mColor(Float3::WHITE),
	mUpdateTime(-1.0f),
	mUpdateTiming(0.0f),
	mUpdateTimingInit(-1.0f),
	mUpdatePriority(0),
	mIsDoPick(true),
	mIsPickIngoreCullingMode(false),
	mIsNotPickedParentChildrenNotPicked(false),
	mIsIngoreParent_Translate(false),
	mIsIngoreParent_Rotate(false),
	mIsIngoreParent_Scale(false)
{
}
//----------------------------------------------------------------------------
Movable::~Movable ()
{
	// mParent����Ҫ���ͷ�
}
//----------------------------------------------------------------------------
void Movable::Show (bool show)
{
	if (show)
	{
		if (CULL_ALWAYS == Culling)
		{
			Culling = CULL_DYNAMIC;
		}
	}
	else
	{
		Culling = CULL_ALWAYS;
	}
}
//----------------------------------------------------------------------------
void Movable::SetDoPick (bool doPick)
{
	mIsDoPick = doPick;
}
//----------------------------------------------------------------------------
bool Movable::IsShow () const
{
	return Culling!=CULL_ALWAYS;
}
//----------------------------------------------------------------------------
void Movable::Update (double applicationTime, bool initiator)
{
	bool doUpdateTrans = true;
	if (mUpdateTime > 0.0f)
	{
		if (-1.0f == mUpdateTimingInit)
		{
			mUpdateTimingInit = (float)applicationTime;
			mUpdateTiming = 0.0f;
		}
		else
		{
			mUpdateTiming = ((float)applicationTime-mUpdateTimingInit);
		}

		if (mUpdateTiming > mUpdateTime)
		{
			doUpdateTrans = false;
		}
	}

	if (doUpdateTrans)
	{
		UpdateWorldData(applicationTime);
		UpdateWorldBound();
		if (initiator)
		{
			PropagateBoundToRoot();
		}
	}
}
//----------------------------------------------------------------------------
void Movable::SetParentTransformIngore (bool trans, bool rotate, bool scale)
{
	mIsIngoreParent_Translate = trans;
	mIsIngoreParent_Rotate = rotate;
	mIsIngoreParent_Scale = scale;
}
//----------------------------------------------------------------------------
void Movable::GetParentTransformIngore (bool &trans, bool &rotate, bool &scale)
{
	trans = mIsIngoreParent_Translate;
	rotate = mIsIngoreParent_Rotate;
	scale = mIsIngoreParent_Scale;
}
//----------------------------------------------------------------------------
void Movable::OnAttach ()
{
}
//----------------------------------------------------------------------------
void Movable::OnDetach ()
{
}
//----------------------------------------------------------------------------
void Movable::OnPicked (int pickInfo)
{
	PX2_UNUSED(pickInfo);
}
//----------------------------------------------------------------------------
void Movable::OnNotPicked (int pickInfo)
{
	PX2_UNUSED(pickInfo);
}
//----------------------------------------------------------------------------
void Movable::UpdateWorldData (double applicationTime)
{
	// ���¿�����
	UpdateControllers(applicationTime);

	if (LocalTransform.IsRSMatrix())
	{
		const APoint &scale = LocalTransform.GetScale();
		if (scale.X()==scale.Y() && scale.Y()==scale.Z())
			LocalTransform.SetUniformScale(scale.X());
	}

	// ����������
	if (!WorldTransformIsCurrent)
	{
		if (mParent)
		{
			if (mIsIngoreParent_Translate || mIsIngoreParent_Rotate ||
				mIsIngoreParent_Scale)
			{
				Transform trans = mParent->WorldTransform;

				if (mIsIngoreParent_Translate)
				{
					trans.SetTranslate(APoint::ORIGIN);
				}
				if (mIsIngoreParent_Rotate)
				{
					trans.SetRotate(HMatrix::IDENTITY);
				}
				if (mIsIngoreParent_Scale)
				{
					trans.SetScale(APoint(1.0f, 1.0f, 1.0f));
				}
				WorldTransform = trans*LocalTransform;
			}
			else
			{
				WorldTransform = mParent->WorldTransform*LocalTransform;
			}
		}
		else
		{
			WorldTransform = LocalTransform;
		}
	}
}
//----------------------------------------------------------------------------
void Movable::PropagateBoundToRoot ()
{
    if (mParent)
    {
        mParent->UpdateWorldBound();
        mParent->PropagateBoundToRoot();
    }
}
//----------------------------------------------------------------------------
void Movable::OnGetVisibleSet (Culler& culler, bool noCull)
{
    if (Culling == CULL_ALWAYS)
    {
        return;
    }

    if (Culling == CULL_NEVER)
    {
        noCull = true;
    }

    unsigned int savePlaneState = culler.GetPlaneState();
    if (noCull || culler.IsVisible(WorldBound))
    {
        GetVisibleSet(culler, noCull);
    }
    culler.SetPlaneState(savePlaneState);
}
//----------------------------------------------------------------------------
void Movable::SetAlpha (float alpha)
{
	mAlpha = alpha;
}
//----------------------------------------------------------------------------
void Movable::SetColor (const Float3 &color)
{
	mColor = color;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ����
//----------------------------------------------------------------------------
Object* Movable::GetObjectByName (const std::string& name)
{
    // mParent���ò��ң����������ѭ��
    return Controlledable::GetObjectByName(name);
}
//----------------------------------------------------------------------------
void Movable::GetAllObjectsByName (const std::string& name,
    std::vector<Object*>& objects)
{
    // mParent���ò��ң����������ѭ��
    Controlledable::GetAllObjectsByName(name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Property
//----------------------------------------------------------------------------
void Movable::RegistProperties ()
{
	Controlledable::RegistProperties();

	AddPropertyClass("Movable");

	PropertyObject objLocalTrans;
	objLocalTrans.Name = "LocalTransform";
	objLocalTrans.Type = Object::PT_TRANSFORM;
	objLocalTrans.Data = LocalTransform;
	objLocalTrans.Data1 = true;
	AddProperty(objLocalTrans);

	PropertyObject objWorldTrans;
	objWorldTrans.Name = "WorldTransform";
	objWorldTrans.Type = Object::PT_TRANSFORM;
	objWorldTrans.Data = WorldTransform;
	objWorldTrans.Data1 = false;
	AddProperty(objWorldTrans);
	AddProperty("WorldTransformIsCurrent", Object::PT_BOOL, Any(WorldTransformIsCurrent));

	AddProperty("WorldBoundCenter", Object::PT_APOINT3, Any(WorldBound.GetCenter()));
	AddProperty("WorldBoundRadius", Object::PT_FLOAT, Any(WorldBound.GetRadius()));
	AddProperty("WorldBoundIsCurrent", Object::PT_BOOL, Any(WorldBoundIsCurrent));

	std::vector<std::string> cullings;
	cullings.push_back("CULL_DYNAMIC");
	cullings.push_back("CULL_ALWAYS");
	cullings.push_back("CULL_NEVER");
	AddPropertyEnum("CullingMode", (int)Culling, cullings);

	AddProperty("Alpha", Object::PT_FLOAT, Any(GetAlpha()));
	AddProperty("AlphaSelfCtrled", Object::PT_BOOL, Any(IsAlphaSelfCtrled()));
	AddProperty("Color", Object::PT_COLOR3FLOAT3, Any(GetColor()));
	AddProperty("ColorSelfCtrled", Object::PT_BOOL, Any(IsColorSelfCtrled()));

	AddProperty("UpdateTime", Object::PT_FLOAT, GetUpdateTime());
}
//----------------------------------------------------------------------------
void Movable::OnPropertyChanged (const PropertyObject &obj)
{
	Controlledable::OnPropertyChanged(obj);

	if ("LocalTransform" == obj.Name)
	{
		LocalTransform = *Any_Cast<Transform>(&obj.Data);
	}
	else if ("WorldTransform" == obj.Name)
	{
		LocalTransform = *Any_Cast<Transform>(&obj.Data);
	}
	else if ("WorldTransformIsCurrent" == obj.Name)
	{
		WorldTransformIsCurrent = *Any_Cast<bool>(&obj.Data);
	}
	else if ("WorldBoundIsCurrent" == obj.Name)
	{
		WorldBoundIsCurrent = PX2_ANY_AS(obj.Data, bool);
	}
	else if ("WorldBoundCenter" == obj.Name)
	{
		WorldBound.SetCenter(*Any_Cast<APoint>(&obj.Data));
	}
	else if ("WorldBoundRadius" == obj.Name)
	{
		WorldBound.SetRadius(*Any_Cast<float>(&obj.Data));
	}
	else if ("CullingMode" == obj.Name)
	{
		Culling = (CullingMode)(*Any_Cast<int>(&obj.Data));
	}
	else if ("Alpha" == obj.Name)
	{
		SetAlpha(*Any_Cast<float>(&obj.Data));
	}
	else if ("AlphaSelfCtrled" == obj.Name)
	{
		SetAlphaSelfCtrled(*Any_Cast<bool>(&obj.Data));
	}
	else if ("Color" == obj.Name)
	{
		SetColor(*Any_Cast<Float3>(&obj.Data));
	}
	else if ("ColorSelfCtrled" == obj.Name)
	{
		SetColorSelfCtrled(*Any_Cast<bool>(&obj.Data));
	}
	else if ("UpdateTime" == obj.Name)
	{
		SetUpdateTime(PX2_ANY_AS(obj.Data, float));
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// �־û�
//----------------------------------------------------------------------------
Movable::Movable (LoadConstructor value)
    :
    Controlledable(value),
    WorldTransformIsCurrent(false),
    WorldBoundIsCurrent(false),
    Culling(CULL_DYNAMIC),
    mParent(0),
	mIsAlphaSelfCtrled(false),
	mAlpha(1.0f),
	mIsColorSelfCtrled(false),
	mColor(Float3::WHITE),
	mUpdateTime(-1.0f),
	mUpdateTiming(0.0f),
	mUpdateTimingInit(-1.0f),
	mUpdatePriority(0),
	mIsDoPick(true),
	mIsPickIngoreCullingMode(false),
	mIsNotPickedParentChildrenNotPicked(false),
	mIsIngoreParent_Translate(false),
	mIsIngoreParent_Rotate(false),
	mIsIngoreParent_Scale(false)
{
}
//----------------------------------------------------------------------------
void Movable::Load (InStream& source)
{
    PX2_BEGIN_DEBUG_STREAM_LOAD(source);

    Controlledable::Load(source);
	PX2_VERSION_LOAD(source);

    source.ReadAggregate(LocalTransform);
    source.ReadAggregate(WorldTransform);
    source.ReadBool(WorldTransformIsCurrent);
    source.ReadAggregate(WorldBound);
    source.ReadBool(WorldBoundIsCurrent);
    source.ReadEnum(Culling);
	source.Read(mAlpha);
	source.ReadAggregate(mColor);

	int readedVersion = GetReadedVersion();
	if (1 <= readedVersion)
	{
		source.Read(mUpdateTime);
	}

	// mParent�������棬������Node::Link�е���Node::SetChild�����á�

	if (2 <= readedVersion)
	{
		source.ReadBool(mIsAlphaSelfCtrled);
		source.ReadBool(mIsColorSelfCtrled);
	}

    PX2_END_DEBUG_STREAM_LOAD(Movable, source);
}
//----------------------------------------------------------------------------
void Movable::Link (InStream& source)
{
	// mParent�������棬������Node::Link�е���Node::SetChild�����á�

    Controlledable::Link(source);
}
//----------------------------------------------------------------------------
void Movable::PostLink ()
{
    Controlledable::PostLink();
}
//----------------------------------------------------------------------------
bool Movable::Register (OutStream& target) const
{
	// mParent����Ҫ��ע��

    return Controlledable::Register(target);
}
//----------------------------------------------------------------------------
void Movable::Save (OutStream& target) const
{
    PX2_BEGIN_DEBUG_STREAM_SAVE(target);

    Controlledable::Save(target);
	PX2_VERSION_SAVE(target);

    target.WriteAggregate(LocalTransform);
    target.WriteAggregate(WorldTransform);
    target.WriteBool(WorldTransformIsCurrent);
    target.WriteAggregate(WorldBound);
    target.WriteBool(WorldBoundIsCurrent);
    target.WriteEnum(Culling);
	target.Write(mAlpha);
	target.WriteAggregate(mColor);
	target.Write(mUpdateTime);

	target.WriteBool(mIsAlphaSelfCtrled);
	target.WriteBool(mIsColorSelfCtrled);

	// mParent�������棬������Node::Link�е���Node::SetChild�����á�

    PX2_END_DEBUG_STREAM_SAVE(Movable, target);
}
//----------------------------------------------------------------------------
int Movable::GetStreamingSize (Stream &stream) const
{
    int size = Controlledable::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);
    size += LocalTransform.GetStreamingSize();;
    size += WorldTransform.GetStreamingSize();
    size += PX2_BOOLSIZE(WorldTransformIsCurrent);
    size += WorldBound.GetStreamingSize();
    size += PX2_BOOLSIZE(WorldBoundIsCurrent);
    size += PX2_ENUMSIZE(Culling);
	size += sizeof(mAlpha);
	size += sizeof(mColor);

	if (stream.IsIn())
	{
		int readedVersion = GetReadedVersion();
		if (1 <= readedVersion)
		{
			size += sizeof(mUpdateTime);
		}
		if (2 <= readedVersion)
		{
			size += PX2_BOOLSIZE(mIsAlphaSelfCtrled);
			size += PX2_BOOLSIZE(mIsColorSelfCtrled);
		}
	}
	else
	{
		size += sizeof(mUpdateTime);
		size += PX2_BOOLSIZE(mIsAlphaSelfCtrled);
		size += PX2_BOOLSIZE(mIsColorSelfCtrled);
	}

    // mParent�����־û�

    return size;
}
//----------------------------------------------------------------------------

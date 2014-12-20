/*
*
* �ļ�����	��	PX2Object.cpp
*
*/

#include "PX2Object.hpp"
#include "PX2StringHelp.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
Object::Object ()
	:
mReadedVersion(0),
mCurStream(NULL),
mIsNameChangeable(true)
{
}
//----------------------------------------------------------------------------
Object::~Object ()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ����ʶ����Ϣ
//----------------------------------------------------------------------------
const Rtti Object::TYPE("PX2.Object", 0, 0);
//----------------------------------------------------------------------------
const Rtti& Object::GetRttiType () const
{
	return TYPE;
}
//----------------------------------------------------------------------------
unsigned short Object::GetRttiVersion () const
{
	return GetRttiType().GetVersion();
}
//----------------------------------------------------------------------------
bool Object::IsExactly (const Rtti& type) const
{
	return GetRttiType().IsExactly(type);
}
//----------------------------------------------------------------------------
bool Object::IsDerived (const Rtti& type) const
{
	return GetRttiType().IsDerived(type);
}
//----------------------------------------------------------------------------
bool Object::IsExactlyTypeOf (const Object* object) const
{
	return object && GetRttiType().IsExactly(object->GetRttiType());
}
//----------------------------------------------------------------------------
bool Object::IsDerivedTypeOf (const Object* object) const
{
	return object && GetRttiType().IsDerived(object->GetRttiType());
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// �û�����
//----------------------------------------------------------------------------
void Object::SetUserDataFloat (const std::string &name, float val)
{
	mUserDataFloats[name] = val;
}
//----------------------------------------------------------------------------
float Object::GetUserDataFloat (const std::string &name, bool *isValied) const
{
	std::map<std::string, float>::const_iterator it = mUserDataFloats.find(name);
	if (it != mUserDataFloats.end())
	{
		if (isValied)
		{
			*isValied = true;
		}
		return it->second;
	}

	isValied = false;
	return 0.0f;
}
//----------------------------------------------------------------------------
void Object::SetUserData (const std::string &name, const Any &any)
{
	mUserDatas[name] = any;
}
//----------------------------------------------------------------------------
Any Object::GetUserDataAny (const std::string &name, bool *isValied) const
{
	std::map<std::string, Any>::const_iterator it = mUserDatas.find(name);
	if (it != mUserDatas.end())
	{
		if (isValied)
		{
			*isValied = true;
		}
		return it->second;
	}

	isValied = false;
	return Any();
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ��Դ·��
//----------------------------------------------------------------------------
void Object::SetResourcePath (const std::string& name)
{
	mResourcePath = name; 
}
//----------------------------------------------------------------------------
const std::string& Object::GetResourcePath () const
{
	return mResourcePath;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ����
//----------------------------------------------------------------------------
void Object::SetName (const std::string& name)
{
	mName = name;
}
//----------------------------------------------------------------------------
const std::string& Object::GetName () const
{
	return mName;
}
//----------------------------------------------------------------------------
Object* Object::GetObjectByName (const std::string& name)
{
	return (name == mName ? this : 0);
}
//----------------------------------------------------------------------------
void Object::GetAllObjectsByName (const std::string& name,
								  std::vector<Object*>& objects)
{
	if (name == mName)
	{
		objects.push_back(this);
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ����
//----------------------------------------------------------------------------
int Object::msNumProperties = 0;
Object::PropertyObject::PropertyObject ()
	:
Enable(true),
Type(Object::PT_MAX_TYPE)
{
}
//----------------------------------------------------------------------------
Object::PropertyObject::~PropertyObject ()
{

}
//----------------------------------------------------------------------------
Object::PropertyObject *Object::PropertyObject::GetPropertyByTag (
	const std::string &tag)
{
	for (int i=0; i<(int)SubObjects.size(); i++)
	{
		if (tag == SubObjects[i].Tag)
			return &SubObjects[i];
	}

	return 0;
}
//----------------------------------------------------------------------------
Object::PropertyObject *Object::PropertyObject::GetPropertyByName (
	const std::string &name)
{
	for (int i=0; i<(int)SubObjects.size(); i++)
	{
		if (name == SubObjects[i].Tag)
			return &SubObjects[i];
	}

	return 0;
}
//----------------------------------------------------------------------------
std::string Object::GenPropertyTag ()
{
	msNumProperties++;
	return "ObjectPropertyTag" + StringHelp::IntToString(msNumProperties);
}
//----------------------------------------------------------------------------
void Object::RegistProperties ()
{
	AddProperty("Object", PT_CLASS, Any());

	const std::string name = GetName();
	AddProperty("Name", PT_STRING, Any(name), mIsNameChangeable);

	const std::string &rttiName = GetRttiType().GetName();
	AddProperty("RttiName", PT_STRING, Any(rttiName), false);
}
//----------------------------------------------------------------------------
void Object::OnPropertyChanged (const PropertyObject &obj)
{
	if ("Name" == obj.Name)
	{
		std::string val = *(Any_Cast<std::string>(&obj.Data));
		SetName(val);
	}
}
//----------------------------------------------------------------------------
void Object::SetNamePropChangeable (bool isNamePropChangeable)
{
	mIsNameChangeable = isNamePropChangeable;
}
//----------------------------------------------------------------------------
bool Object::IsNamePropChangeable () const
{
	return mIsNameChangeable;
}
//----------------------------------------------------------------------------
std::string Object::AddProperty (const std::string &name, PropertyType type, 
	const Any &data, bool enable)
{
	PropertyObject obj;
	obj.Tag = GenPropertyTag();
	obj.Name = name;
	obj.Type = type;
	obj.Enable = enable;
	obj.Data = data;

	mProperties.push_back(obj);

	return obj.Tag;
}
//----------------------------------------------------------------------------
std::string Object::AddPropertyEnum (const std::string &name, int val,
	const std::vector<std::string> &enums, bool enable)
{
	std::string tag = GenPropertyTag();

	PropertyObject obj;
	obj.Tag = tag;
	obj.Name = name;
	obj.Type = PT_ENUM;
	obj.Enable = enable;
	obj.Data = val;
	obj.Data1 = enums;

	mProperties.push_back(obj);

	return obj.Tag;
}
//----------------------------------------------------------------------------
std::string Object::AddPropertyClass (const std::string &name)
{
	return AddProperty(name, Object::PT_CLASS, Any());
}
//----------------------------------------------------------------------------
std::string Object::AddProperty (PropertyObject &obj)
{
	obj.Tag = GenPropertyTag();

	mProperties.push_back(obj);

	return obj.Tag;
}
//----------------------------------------------------------------------------
void Object::RemoveAllProperties ()
{
	mProperties.clear();
}
//----------------------------------------------------------------------------
std::string Object::AddPropertySub (const std::string &parTag,
	const std::string &name, PropertyType type, const Any &data, bool enable)
{
	if (parTag.empty())
	{
		AddProperty(name, type, data, enable);
	}
	else
	{
		Object::PropertyObject *po = GetPropertyByTag(parTag);
		if (po)
		{
			PropertyObject obj;
			obj.Tag = GenPropertyTag();
			obj.Name = name;
			obj.Type = type;
			obj.Enable = enable;
			obj.Data = data;

			po->SubObjects.push_back(obj);

			return obj.Tag;
		}
	}

	return "";
}
//----------------------------------------------------------------------------
std::string Object::AddPropertyEnumSub (const std::string &parTag,
	const std::string &name, int val, const std::vector<std::string> &enums, 
	bool enable)
{
	if (parTag.empty())
	{
		AddPropertyEnum(name, val, enums, enable);
	}
	else
	{
		Object::PropertyObject *po = GetPropertyByTag(parTag);
		if (po)
		{
			std::string tag = GenPropertyTag();

			PropertyObject obj;
			obj.Tag = tag;
			obj.Name = name;
			obj.Type = PT_ENUM;
			obj.Enable = enable;
			obj.Data = val;
			obj.Data1 = enums;

			po->SubObjects.push_back(obj);

			return obj.Tag;
		}
	}

	return "";
}
//----------------------------------------------------------------------------
const std::vector<Object::PropertyObject> &Object::GetProperties () const
{
	return mProperties;
}
//----------------------------------------------------------------------------
std::vector<Object::PropertyObject> &Object::GetProperties ()
{
	return mProperties;
}
//----------------------------------------------------------------------------
Object::PropertyObject *Object::GetPropertyByName (const std::string &name)
{
	for (int i=0; i<(int)mProperties.size(); i++)
	{
		Object::PropertyObject *propObj = mProperties[i].GetPropertyByName(name);
		if (propObj)
			return propObj;

		if (name == mProperties[i].Name)
			return &mProperties[i];
	}

	return 0;
}
//----------------------------------------------------------------------------
Object::PropertyObject *Object::GetPropertyByTag (const std::string &tag)
{
		for (int i=0; i<(int)mProperties.size(); i++)
	{
		Object::PropertyObject *propObj = mProperties[i].GetPropertyByTag(tag);
		if (propObj)
			return propObj;

		if (tag == mProperties[i].Tag)
			return &mProperties[i];
	}

	return 0;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//  ����
//----------------------------------------------------------------------------
std::map<std::string, std::vector<Object::FunObject> > Object::mFunObjectMap;
//----------------------------------------------------------------------------
Object::FunParam::FunParam ()
	:
Type(FPT_INT)
{
}
//----------------------------------------------------------------------------
Object::FunParam::~FunParam ()
{
}
//----------------------------------------------------------------------------
void Object::FunObject::AddInput (const std::string &paramName, 
	Object::FunParamType type, const Any &paramValue)
{
	FunParam funParam;
	funParam.Name = paramName;
	funParam.Type = type;
	funParam.Value = paramValue;
	mInParams.push_back(funParam);
}
//----------------------------------------------------------------------------
void Object::FunObject::AddOutPut (const std::string &paramName, 
	Object::FunParamType type)
{
	FunParam funParam;
	funParam.Name = paramName;
	funParam.Type = type;
	mOutParams.push_back(funParam);
}
//----------------------------------------------------------------------------
const std::vector<Object::FunParam> &Object::FunObject::GetInParams () const
{
	return mInParams;
}
//----------------------------------------------------------------------------
int Object::FunObject::GetNumInParams () const
{
	return (int)mInParams.size();
}
//----------------------------------------------------------------------------
const Object::FunParam &Object::FunObject::GetInParam (int i) const
{
	return mInParams[i];
}
//----------------------------------------------------------------------------
const std::vector<Object::FunParam> &Object::FunObject::GetOutParams () const
{
	return mOutParams;
}
//----------------------------------------------------------------------------
int Object::FunObject::GetNumOutParams () const
{
	return (int)mOutParams.size();
}
//----------------------------------------------------------------------------
const Object::FunParam &Object::FunObject::GetOutParam (int i) const
{
	return mOutParams[i];
}
//----------------------------------------------------------------------------
void Object::RegistFunctions ()
{
	mFunObjectMap.clear();

	FunObject funObjSetName;
	funObjSetName.ClassName = "Object";
	funObjSetName.FunName = "SetName";
	funObjSetName.AddInput("name", FPT_STRING, std::string("NoName"));
	mFunObjectMap[funObjSetName.ClassName].push_back(funObjSetName);

	FunObject funObjGetName;
	funObjGetName.ClassName = "Object";
	funObjGetName.FunName = "GetName";
	funObjGetName.AddOutPut("value", FPT_STRING);
	mFunObjectMap[funObjSetName.ClassName].push_back(funObjGetName);
}
//----------------------------------------------------------------------------
std::map<std::string, std::vector<Object::FunObject> > &Object::
	GetFunctionMap ()
{
	return mFunObjectMap;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// �־û�
//----------------------------------------------------------------------------
Object::FactoryMap* Object::msFactories = 0;
bool Object::msStreamRegistered = false;
bool Object::msIsIOWriting = false;
//----------------------------------------------------------------------------
Object *Object::Create ()
{
	assertion(false, "Object should not create");
	return 0;
}
//----------------------------------------------------------------------------
Object *Object::Create (const std::string &name)
{
	assertion(false, "Object should not create");
	PX2_UNUSED(name);
	return 0;
}
//----------------------------------------------------------------------------
Object* Object::Factory (InStream&)
{
	assertion(false, "Abstract classes have no factory.\n");
	return 0;
}
//----------------------------------------------------------------------------
bool Object::RegisterFactory ()
{
	if (!msStreamRegistered)
	{
		InitTerm::AddInitializer(Object::InitializeFactory);
		InitTerm::AddTerminator(Object::TerminateFactory);
		msStreamRegistered = true;
	}
	return msStreamRegistered;
}
//----------------------------------------------------------------------------
void Object::InitializeFactory ()
{
	if (!msFactories)
	{
		msFactories = new0 Object::FactoryMap();
	}
	//msFactories->insert(std::make_pair(TYPE.GetName(), Factory));
	(*msFactories)[TYPE.GetName()] = Factory;}
//----------------------------------------------------------------------------
void Object::TerminateFactory ()
{
	delete0(msFactories);
	msFactories = 0;
}
//----------------------------------------------------------------------------
Object::FactoryFunction Object::Find (const std::string& name)
{
	assertion(msFactories != 0, "FactoryMap was not yet allocated.\n");
	FactoryMap::iterator iter = msFactories->find(name);
	if (iter != msFactories->end())
	{
		return iter->second;
	}
	return 0;
}
//----------------------------------------------------------------------------
Object::Object (LoadConstructor)
	:
mReadedVersion(0),
mCurStream(NULL)
{
}
//----------------------------------------------------------------------------
void Object::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	// Rtti �����Ѿ�����ȡ��
	
	// Rtti version
	source.Read(mReadedVersion);

	// ��ȡID���ṩ�����������Ϣ
	source.ReadUniqueID(this);

	// ��Դ·��
	source.ReadString(mResourcePath);

	// ��ȡ���������
	source.ReadString(mName);

	PX2_END_DEBUG_STREAM_LOAD(Object, source);
}
//----------------------------------------------------------------------------
void Object::Link (InStream&)
{
	// Objectû����ҪLink�ĳ�Ա
}
//----------------------------------------------------------------------------
void Object::PostLink ()
{
	// Objectû����ҪPostLink�ĳ�Ա
}
//----------------------------------------------------------------------------
bool Object::Register (OutStream& target) const
{
	return target.RegisterRoot(this);
}
//----------------------------------------------------------------------------
void Object::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	// д��Rtti ����
	target.WriteString(GetRttiType().GetName());

	// д��Rtti version
	target.Write(TYPE.GetVersion());

	// д��ID
	target.WriteUniqueID(this);

	// ��Դ·��
	target.WriteString(mResourcePath);

	// д���������
	target.WriteString(mName);

	PX2_END_DEBUG_STREAM_SAVE(Object, target);
}
//----------------------------------------------------------------------------
int Object::GetStreamingSize (Stream &stream) const
{
	PX2_UNUSED(stream);

	// Rtti ����
	int size = PX2_STRINGSIZE(GetRttiType().GetName());

	// Rtti version
	size += sizeof(GetRttiType().GetVersion());

	// ����ID
	size += sizeof(unsigned int);

	// ��Դ·��
	size += PX2_STRINGSIZE(mResourcePath);

	// ���������
	size += PX2_STRINGSIZE(mName);

	return size;
}
//----------------------------------------------------------------------------
unsigned short Object::GetReadedVersion () const
{
	return mReadedVersion;
}
//----------------------------------------------------------------------------
Object* Object::Copy (const std::string& uniqueNameAppend)
{
	// Save the object to a memory buffer.
	OutStream saveStream;
	saveStream.SetObjectCopy(false);

	saveStream.Insert((Object*)this);
	int bufferSize = 0;
	char* buffer = 0;
	saveStream.Save(bufferSize, buffer, BufferIO::BM_DEFAULT_WRITE);

	// Load the object from the memory buffer.
	InStream loadStream;
	loadStream.Load(bufferSize, buffer, BufferIO::BM_DEFAULT_READ);
	delete1(buffer);

	if (uniqueNameAppend != "")
	{
		int numObjects = loadStream.GetNumObjects();
		for (int i=0; i<numObjects; i++)
		{
			PX2::Object *obj = loadStream.GetObjectAt(i);
			std::string name = obj->GetName();
			if (name.length() > 0)
			{
				name += uniqueNameAppend;
				obj->SetName(name);
			}
		}
	}

	return loadStream.GetObjectAt(0);
}
//----------------------------------------------------------------------------
Object* Object::ShareCopy (const std::string& uniqueNameAppend)
{
	// Save the object to a memory buffer.
	OutStream saveStream;
	saveStream.SetObjectCopy(true);

	saveStream.Insert((Object*)this);
	int bufferSize = 0;
	char* buffer = 0;
	saveStream.Save(bufferSize, buffer, BufferIO::BM_DEFAULT_WRITE);

	// Load the object from the memory buffer.
	InStream loadStream;
	loadStream.Load(bufferSize, buffer, BufferIO::BM_DEFAULT_READ);
	delete1(buffer);

	if (uniqueNameAppend != "")
	{
		int numObjects = loadStream.GetNumObjects();
		for (int i=0; i<numObjects; i++)
		{
			PX2::Object *obj = loadStream.GetObjectAt(i);
			std::string name = obj->GetName();
			if (name.length() > 0)
			{
				name += uniqueNameAppend;
				obj->SetName(name);
			}
		}
	}

	return loadStream.GetObjectAt(0);
}
//----------------------------------------------------------------------------
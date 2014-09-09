/*
*
* 文件名称	：	PX2ShaderParameters.cpp
*
*/

#include "PX2ShaderParameters.hpp"
#include "PX2StringHelp.hpp"
#include "PX2Texture2D.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI_V(PX2, Object, ShaderParameters, 2);
PX2_IMPLEMENT_STREAM(ShaderParameters);
PX2_IMPLEMENT_FACTORY(ShaderParameters);

const std::string strEmptyResPath = "EmptyResPath";

//----------------------------------------------------------------------------
ShaderParameters::ShaderParameters (Shader* shader)
:
mShader(shader)
{
	assertion(shader != 0, "Shader must be specified.\n");

	mNumConstants = mShader->GetNumConstants();
	if (mNumConstants > 0)
	{
		mConstants = new1<ShaderFloatPtr>(mNumConstants);
	}
	else
	{
		mConstants = 0;
	}

	mNumTextures = mShader->GetNumSamplers();
	if (mNumTextures > 0)
	{
		mTextureResPath.resize(mNumTextures);
		mTextures = new1<TexturePtr>(mNumTextures);
	}
	else
	{
		mTextures = 0;
	}

	SetName("ShaderParameters");
}
//----------------------------------------------------------------------------
ShaderParameters::~ShaderParameters ()
{
	delete1(mConstants);
	delete1(mTextures);
}
//----------------------------------------------------------------------------
int ShaderParameters::SetConstant (const std::string& name,
								   ShaderFloat* sfloat)
{
	for (int i = 0; i < mNumConstants; ++i)
	{
		if (mShader->GetConstantName(i) == name)
		{
			mConstants[i] = sfloat;
			return i;
		}
	}

	assertion(false, "Cannot find constant:%s\n", name);
	return -1;
}
//----------------------------------------------------------------------------
int ShaderParameters::SetTexture (const std::string& name, Texture* texture)
{
	for (int i = 0; i < mNumTextures; ++i)
	{
		if (mShader->GetSamplerName(i) == name)
		{
			mTextures[i] = texture;
			return i;
		}
	}

	assertion(false, "Cannot find texture:%s\n", name);
	return -1;
}
//----------------------------------------------------------------------------
void ShaderParameters::SetConstant (int handle, ShaderFloat* sfloat)
{
	if (0 <= handle && handle < mNumConstants)
	{
		mConstants[handle] = sfloat;
		return;
	}

	assertion(false, "Invalid constant handle.\n");
}
//----------------------------------------------------------------------------
void ShaderParameters::SetTexture (int handle, Texture* texture)
{
	if (0 <= handle && handle < mNumTextures)
	{
		mTextures[handle] = texture;
		return;
	}

	assertion(false, "Invalid texture handle.\n");
}
//----------------------------------------------------------------------------
ShaderFloat* ShaderParameters::GetConstant (const std::string& name) const
{
	for (int i = 0; i < mNumConstants; ++i)
	{
		if (mShader->GetConstantName(i) == name)
		{
			return mConstants[i];
		}
	}

	assertion(false, "Cannot find constant.\n");
	return 0;
}
//----------------------------------------------------------------------------
Texture* ShaderParameters::GetTexture (const std::string& name) const
{
	for (int i = 0; i < mNumTextures; ++i)
	{
		if (mShader->GetSamplerName(i) == name)
		{
			return mTextures[i];
		}
	}

	assertion(false, "Cannot find texture.\n");
	return 0;
}
//----------------------------------------------------------------------------
ShaderFloat* ShaderParameters::GetConstant (int handle) const
{
	if (0 <= handle && handle < mNumConstants)
	{
		return mConstants[handle];
	}

	assertion(false, "Invalid constant handle.\n");
	return 0;
}
//----------------------------------------------------------------------------
Texture* ShaderParameters::GetTexture (int handle) const
{
	if (0 <= handle && handle < mNumTextures)
	{
		return mTextures[handle];
	}

	assertion(false, "Invalid texture handle.\n");
	return 0;
}
//----------------------------------------------------------------------------
void ShaderParameters::UpdateConstants (const Renderable* renderable,
										const Camera* camera)
{
	ShaderFloatPtr* constants = mConstants;
	for (int i = 0; i < mNumConstants; ++i, ++constants)
	{
		ShaderFloat* constant = *constants;
		if (constant->AllowUpdater())
		{
			constant->Update(renderable, camera);
		}
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Property
//----------------------------------------------------------------------------
void ShaderParameters::RegistProperties ()
{
	Object::RegistProperties();
	AddPropertyClass("ShaderParameters");

	AddProperty("NumConstants", PT_INT, GetNumConstants(), false);
	for (int i=0; i<GetNumConstants(); i++)
	{
		ShaderFloat *sf = GetConstant(i);
		if (sf)
		{
			std::string name = mShader->GetConstantName(i);
			AddProperty("ShaderFloat", Object::PT_STRING, name, false);
			sf->Float_OnRegistProperties(this);
		}
	}

	AddProperty("NumTextures", PT_INT, GetNumTextures(), false);
	for (int i=0; i<GetNumTextures(); i++)
	{
		Texture *tex = GetTexture(i);
		std::string iStr = StringHelp::IntToString(i);
		AddProperty("Texture_Name"+iStr, PT_STRING, tex->GetName(), false);
		AddProperty("Texture_Path"+iStr, PT_STRINGBUTTON, tex->GetResourcePath());
	}
}
//----------------------------------------------------------------------------
void ShaderParameters::OnPropertyChanged (const PropertyObject &obj)
{
	Object::OnPropertyChanged(obj);

	for (int i=0; i<GetNumConstants(); i++)
	{
		ShaderFloat *sf = GetConstant(i);
		if (sf)
		{
			sf->Float_OnPropertyChanged(this, obj);
		}
	}

	if (Object::PT_STRINGBUTTON == obj.Type)
	{
		const std::string name = obj.Name;
		std::string path = PX2_ANY_AS(obj.Data, std::string);

		std::string key = "Texture_Path";
		size_t pos = name.find(key);	
		size_t len = key.length();
		size_t leftLen = name.length() - len;
		if (pos != std::string::npos && msTextureUserLoadFun)
		{
			std::string iStr = name.substr(len, leftLen);
			int i = atoi(iStr.c_str());

			mTextureResPath[i] = path;
			mTextures[i] = msTextureUserLoadFun(path.c_str());
		}
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称支持
//----------------------------------------------------------------------------
Object* ShaderParameters::GetObjectByName (const std::string& name)
{
	Object* found = Object::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	PX2_GET_OBJECT_BY_NAME(mShader, name, found);

	int i;
	for (i = 0; i < mNumConstants; ++i)
	{
		PX2_GET_OBJECT_BY_NAME(mConstants[i], name, found);
	}

	for (i = 0; i < mNumTextures; ++i)
	{
		PX2_GET_OBJECT_BY_NAME(mTextures[i], name, found);
	}

	return 0;
}
//----------------------------------------------------------------------------
void ShaderParameters::GetAllObjectsByName (const std::string& name,
											std::vector<Object*>& objects)
{
	Object::GetAllObjectsByName(name, objects);

	PX2_GET_ALL_OBJECTS_BY_NAME(mShader, name, objects);

	int i;
	for (i = 0; i < mNumConstants; ++i)
	{
		PX2_GET_ALL_OBJECTS_BY_NAME(mConstants[i], name, objects);
	}

	for (i = 0; i < mNumTextures; ++i)
	{
		PX2_GET_ALL_OBJECTS_BY_NAME(mTextures[i], name, objects);
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
ShaderParameters::ShaderParameters (LoadConstructor value)
:
Object(value),
mNumConstants(0),
mConstants(0),
mNumTextures(0),
mTextures(0)
{
}
//----------------------------------------------------------------------------
void ShaderParameters::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Object::Load(source);
	PX2_VERSION_LOAD(source);

	source.ReadPointer(mShader);
	source.ReadPointerRR(mNumConstants, mConstants);

	int readedVersion = GetReadedVersion();

	if (0 == readedVersion)
	{
		source.ReadPointerRR(mNumTextures, mTextures);
	}
	else if (1 == readedVersion)
	{
		source.Read(mNumTextures);

		if (mNumTextures > 0 )
		{
			mTextures = new1<TexturePtr>(mNumTextures);
			mTextureResPath.resize(mNumTextures);

			for (int i=0; i<mNumTextures; i++)
			{
				std::string resPath;
				source.ReadString(resPath);
				mTextureResPath[i] = resPath;
				if (strEmptyResPath == resPath)
				{
					source.ReadPointer(mTextures[i]);
				}
			}
		}
	}
	else if (2 == readedVersion)
	{
		source.Read(mNumTextures);

		if (mNumTextures > 0 )
		{
			mTextures = new1<TexturePtr>(mNumTextures);
			mTextureResPath.resize(mNumTextures);

			for (int i=0; i<mNumTextures; i++)
			{
				std::string resPath;
				source.ReadString(resPath);
				mTextureResPath[i] = resPath;
			}
		}
	}

	PX2_END_DEBUG_STREAM_LOAD(ShaderParameters, source);
}
//----------------------------------------------------------------------------
void ShaderParameters::Link (InStream& source)
{
	Object::Link(source);

	source.ResolveLink(mShader);
	source.ResolveLink(mNumConstants, mConstants);

	int readedVersion = GetReadedVersion();
	
	if (0 == readedVersion)
	{
		source.ResolveLink(mNumTextures, mTextures);
	}
	else if(1 == readedVersion)
	{
		assertion(0!=msTextureUserLoadFun, "msTextureUserLoadFun must not be 0.\n");

		for (int i=0; i<mNumTextures; i++)
		{
			std::string resPath = mTextureResPath[i];

			if (!resPath.empty())
			{
				if (strEmptyResPath != resPath)
				{
					mTextures[i] = msTextureUserLoadFun(mTextureResPath[i].c_str());

					//Texture2D *text2D = DynamicCast<Texture2D>(mTextures[i]);
					//if (text2D && !text2D->HasMipmaps())
					//{
					//	text2D->GenerateMipmaps();
					//}
				}
				else
				{
					source.ResolveLink(mTextures[i]);
				}
			}
			else
			{
				mTextures[i] = 0;
			}
		}
	}
	else if (2 == readedVersion)
	{
		assertion(0!=msTextureUserLoadFun, "msTextureUserLoadFun must not be 0.\n");

		for (int i=0; i<mNumTextures; i++)
		{
			std::string resPath = mTextureResPath[i];

			if (!resPath.empty())
			{
				if (strEmptyResPath != resPath)
				{
					mTextures[i] = msTextureUserLoadFun(mTextureResPath[i].c_str());
				}
			}
			else
			{
				mTextures[i] = 0;
			}
		}
	}
}
//----------------------------------------------------------------------------
void ShaderParameters::PostLink ()
{
	Object::PostLink();
}
//----------------------------------------------------------------------------
bool ShaderParameters::Register (OutStream& target) const
{
	if (Object::Register(target))
	{
		if(target.IsObjectCopy()) target.Register(mShader, true);
		else target.Register(mShader);

		target.Register(mNumConstants, mConstants);

		if (0 == GetRttiType().GetVersion())
		{
			target.Register(mNumTextures, mTextures);	
		}
		else if (1 == GetRttiType().GetVersion())
		{
			for (int i=0; i<mNumTextures; i++)
			{
				if (mTextures[i])
				{
					std::string resPath = mTextures[i]->GetResourcePath();
					if (resPath.empty())
					{
						target.Register(mTextures[i]);
					}
				}
			}
		}
		else if (2 == GetRttiType().GetVersion())
		{
			for (int i=0; i<mNumTextures; i++)
			{
				if (mTextures[i])
				{
					std::string resPath = mTextures[i]->GetResourcePath();
					if (resPath.empty())
					{
					//	target.Register(mTextures[i]);
					}
				}
			}
		}

		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void ShaderParameters::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Object::Save(target);
	PX2_VERSION_SAVE(target);

	target.WritePointer(mShader);
	target.WritePointerW(mNumConstants, mConstants);

	if (0 == GetRttiType().GetVersion())
	{
		target.WritePointerW(mNumTextures, mTextures);
	}
	else if (1 == GetRttiType().GetVersion())
	{
		target.Write(mNumTextures);
		for (int i=0; i<mNumTextures; i++)
		{
			if (mTextures[i])
			{
				std::string resPath = mTextures[i]->GetResourcePath();
				if (!resPath.empty())
				{
					target.WriteString(resPath);
				}
				else
				{
					target.WriteString(strEmptyResPath);
					target.WritePointer(mTextures[i]);
				}
			}
			else
			{
				target.WriteString("");
			}
		}
	}
	else if (2 == GetRttiType().GetVersion())
	{
		target.Write(mNumTextures);
		for (int i=0; i<mNumTextures; i++)
		{
			if (mTextures[i])
			{
				std::string resPath = mTextures[i]->GetResourcePath();
				if (!resPath.empty())
				{
					target.WriteString(resPath);
				}
				else
				{
					target.WriteString(strEmptyResPath);
				}
			}
			else
			{
				target.WriteString("");
			}
		}
	}

	PX2_END_DEBUG_STREAM_SAVE(ShaderParameters, target);
}
//----------------------------------------------------------------------------
int ShaderParameters::GetStreamingSize (Stream &stream) const
{
	int size = Object::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);
	size += PX2_POINTERSIZE(mShader);
	size += sizeof(mNumConstants);
	size += mNumConstants*PX2_POINTERSIZE(mConstants[0]);
	size += sizeof(mNumTextures);

	if (Stream::ST_IN == stream.GetStreamType())
	{
		int readedVersion = GetReadedVersion();

		if (0 == readedVersion)
		{
			size += mNumTextures*PX2_POINTERSIZE(mTextures[0]);	
		}
		else if (1 == readedVersion)
		{
			for (int i=0; i<mNumTextures; i++)
			{
				size += PX2_STRINGSIZE(mTextureResPath[i]);
				if (strEmptyResPath == mTextureResPath[i])
				{
					size += PX2_POINTERSIZE(mTextures[i]);
				}
			}
		}
		else if (2 == readedVersion)
		{
			for (int i=0; i<mNumTextures; i++)
			{
				size += PX2_STRINGSIZE(mTextureResPath[i]);
			}
		}
	}
	else
	{
		if (0 == GetRttiType().GetVersion())
		{
			size += mNumTextures*PX2_POINTERSIZE(mTextures[0]);	
		}
		else if (1 == GetRttiType().GetVersion())
		{
			for (int i=0; i<mNumTextures; i++)
			{
				if (mTextures[i])
				{
					std::string resPath = mTextures[i]->GetResourcePath();
					if ("" != resPath)
					{
						size += PX2_STRINGSIZE(resPath);
					}
					else
					{
						size += PX2_STRINGSIZE(strEmptyResPath);
						size += PX2_POINTERSIZE(mTextures[i]);
					}
				}
				else 
				{
					size += PX2_STRINGSIZE("");
				}
			}
		}
		else if (2 == GetRttiType().GetVersion())
		{
			for (int i=0; i<mNumTextures; i++)
			{
				if (mTextures[i])
				{
					std::string resPath = mTextures[i]->GetResourcePath();
					if ("" != resPath)
					{
						size += PX2_STRINGSIZE(resPath);
					}
					else
					{
						size += PX2_STRINGSIZE(strEmptyResPath);
					}
				}
				else 
				{
					size += PX2_STRINGSIZE("");
				}
			}
		}
	}

	return size;
}
//----------------------------------------------------------------------------
TextureUserLoadFun ShaderParameters::msTextureUserLoadFun = 0;
//----------------------------------------------------------------------------
void ShaderParameters::SetUserLoadFun (TextureUserLoadFun userLoadFun)
{
	msTextureUserLoadFun = userLoadFun;
}
//----------------------------------------------------------------------------
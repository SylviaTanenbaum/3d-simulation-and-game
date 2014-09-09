/*
*
* 文件名称	：	PX2Renderable.cpp
*
*/

#include "PX2Renderable.hpp"
#include "PX2Culler.hpp"
#include "PX2VertexBufferAccessor.hpp"
#include "PX2Texture2DMaterial.hpp"
#include "PX2SkinTex2DMaterial.hpp"
#include "PX2StandardESMaterial_Default.hpp"
#include "PX2ShaderParameters.hpp"
#include "PX2Texture2MulMaterial.hpp"
#include "PX2StandardESMaterial_Default.hpp"
#include "PX2StandardESMaterial_AlphaTest.hpp"
#include "PX2ShineDiffuseConstant.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI_V(PX2, Movable, Renderable, 5);
PX2_IMPLEMENT_STREAM(Renderable);
PX2_IMPLEMENT_ABSTRACT_FACTORY(Renderable);

//----------------------------------------------------------------------------
Renderable::Renderable (PrimitiveType type)
:
mRenderUsageBits(0),
mEyeDistance(0.0f),
mType(type),
mVFormat(0),
mVBuffer(0),
mIBuffer(0),
mMaterial(0),
mSortIndex(0),
mIsUseShareBuffers(false),
mDBObject_V(0),
mDBObject_I(0),
mIBOffset(0),
mIBNumElements(0),
mIsBackObject(true),
mIsBackTarget(false),
mIsUseLightTexture(false),
mBakeSizeType(BST_NORMAL)
{
	AllowRed = true;
	AllowGreen = true;
	AllowBlue = true;
	AllowAlpha = true;

	SetRenderLayer(RL_SCENE);
	SetUpdatePriority(-1);

	mDefaultShine = new0 Shine();
	mDefaultShine->SetName("Shine");
}
//----------------------------------------------------------------------------
Renderable::Renderable (PrimitiveType type, VertexFormat* vformat,
				VertexBuffer* vbuffer, IndexBuffer* ibuffer)
				:
mType(type),
mVFormat(vformat),
mVBuffer(vbuffer),
mIBuffer(ibuffer),
mMaterial(0),
mSortIndex(0),
mIsUseShareBuffers(false),
mDBObject_V(0),
mDBObject_I(0),
mIBOffset(0),
mIBNumElements(0),
mIsBackObject(true),
mIsBackTarget(false),
mIsUseLightTexture(false),
mBakeSizeType(BST_NORMAL)
{
	AllowRed = true;
	AllowGreen = true;
	AllowBlue = true;
	AllowAlpha = true;

	SetRenderLayer(RL_SCENE);
	UpdateModelSpace(GU_MODEL_BOUND_ONLY);
	SetUpdatePriority(-1);

	mDefaultShine = new0 Shine();
	mDefaultShine->SetName("Shine");
}
//----------------------------------------------------------------------------
Renderable::~Renderable ()
{
}
//----------------------------------------------------------------------------
void Renderable::SetRenderLayer (RenderLayer layer, int sublayer)
{
	mLayer = layer;
	//mSortIndex = (layer<<16)|(mSortIndex&0xff00ffff);
	mSortIndex = (layer<<24)|(sublayer<<16)|(mSortIndex&0xffff);
}
//----------------------------------------------------------------------------
bool Renderable::AddLight (Light *light)
{
	bool bIn = false;

	for (int i=0; i<(int)mInfulencedLights.size(); i++)
	{
		if (light == mInfulencedLights[i])
			bIn = true; 
	}

	if (!bIn)
	{
		mInfulencedLights.push_back(light);
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
bool Renderable::RemoveLight (Light *light)
{
	std::vector<LightPtr>::iterator it = mInfulencedLights.begin();
	for (; it!=mInfulencedLights.end(); it++)
	{
		if (light == *it)
		{
			mInfulencedLights.erase(it);
			return true;
		}
	}

	return false;
}
//----------------------------------------------------------------------------
void Renderable::ClearLights ()
{
	mInfulencedLights.clear();
}
//----------------------------------------------------------------------------
int Renderable::GetNumLights ()
{
	return (int)mInfulencedLights.size();
}
//----------------------------------------------------------------------------
Light *Renderable::GetLight (int i)
{
	assertion(0<=i && i<(int)mInfulencedLights.size(),
		"i should be in right range.");

	if (0<=i && i<(int)mInfulencedLights.size())
	{
		return mInfulencedLights[i];
	}

	return 0;
}
//----------------------------------------------------------------------------
void Renderable::SetLightTexture (Texture2D *tex)
{
	if (tex)
	{
		mLightTexPath = tex->GetResourcePath();
	}
	else
	{
		mLightTexPath = "";
	}

	MaterialInstance *mi = GetMaterialInstance();
	if (mi)
	{
		Material *material = DynamicCast<Material>(mi->GetMaterial());
		Texture2DMaterial *tex2DMtl = DynamicCast<Texture2DMaterial>(material);
		SkinTex2DMaterial *skin2DMtl = DynamicCast<SkinTex2DMaterial>(material);
		StandardESMaterial_Default *stdMtl = DynamicCast<StandardESMaterial_Default>(material);

		if (tex2DMtl || skin2DMtl || stdMtl)
		{
			Texture2D *tex2d = DynamicCast<Texture2D>(mi->GetPixelTexture(0, 0));
			if (tex2d && !mIsUseLightTexture)
			{
				mNormalTexPath = tex2d->GetResourcePath();
			}
		}
	}
}
//----------------------------------------------------------------------------
void Renderable::SetUseLightTexture (bool use)
{
	if (!IsBakeTarget())
		return;

	if (!ShaderParameters::msTextureUserLoadFun)
		return;
	
	MaterialInstance *mi = GetMaterialInstance();
	if (!mi)
		return;

	if (mIsUseLightTexture == use)
		return;

	if (use)
	{
		if (!mNormalTexPath.empty() && !mLightTexPath.empty())
		{
			Texture2D *normalTex = DynamicCast<Texture2D>(ShaderParameters::msTextureUserLoadFun(
				mNormalTexPath.c_str()));

			Texture2D *lightTex = DynamicCast<Texture2D>(ShaderParameters::msTextureUserLoadFun(
				mLightTexPath.c_str()));

			if (normalTex && lightTex)
			{
				mNormalMaterialInstance = GetMaterialInstance();

				MaterialInstance *mi = Texture2MulMaterial::CreateUniqueInstance(
					normalTex, Shader::SF_LINEAR, Shader::SC_CLAMP, Shader::SC_CLAMP,
					lightTex, Shader::SF_LINEAR, Shader::SC_CLAMP, Shader::SC_CLAMP);
				SetMaterialInstance(mi);

				mIsUseLightTexture = use;
			}
		}
	}
	else
	{
		if (mNormalMaterialInstance)
		{
			SetMaterialInstance(mNormalMaterialInstance);
			mIsUseLightTexture = use;
		}
	}
}
//----------------------------------------------------------------------------
void Renderable::ConvertLightMtl ()
{
	MaterialInstance *mi = GetMaterialInstance();
	if (mi)
	{
		Texture2DMaterial *tex2DMtl = DynamicCast<Texture2DMaterial>(
			mi->GetMaterial());

		if (tex2DMtl)
		{
			Texture2D *tex2d = DynamicCast<Texture2D>(mi->GetPixelTexture(0, 0));
			mDefaultShine->Ambient = Float4(1.0f, 1.0f, 1.0f, 1.0f);
			mDefaultShine->Diffuse = Float4(1.0f, 1.0f, 1.0f, 1.0f);
			MaterialInstance *newmi = StandardESMaterial_AlphaTest::CreateUniqueInstance(tex2d, 0, mDefaultShine);
			SetMaterialInstance(newmi);
		}
	}
}
//----------------------------------------------------------------------------
void Renderable::SetAlpha (float alpha)
{
	Movable::SetAlpha(alpha);

	if (mMaterial)
	{
		StandardESMaterial_Default *stdESMtl_Default = DynamicCast<StandardESMaterial_Default>(mMaterial->GetMaterial());
		if (stdESMtl_Default)
		{
			ShineDiffuseConstant *sDiffConst = DynamicCast<ShineDiffuseConstant>(mMaterial->GetVertexConstant(0, "gShineDiffuse"));
			if (sDiffConst)
			{
				sDiffConst->GetShine()->Diffuse[3] = alpha;
			}
		}
	}
}
//----------------------------------------------------------------------------
void Renderable::UpdateModelSpace (UpdateType)
{
	UpdateModelBound();
}
//----------------------------------------------------------------------------
void Renderable::OnForceBind ()
{
}
//----------------------------------------------------------------------------
void Renderable::UpdateWorldBound ()
{
	mModelBound.TransformBy(WorldTransform, WorldBound);
}
//----------------------------------------------------------------------------
void Renderable::UpdateModelBound ()
{
	int numVertices = mVBuffer->GetNumElements();
	int stride = mVFormat->GetStride();

	int posIndex = mVFormat->GetIndex(VertexFormat::AU_POSITION);
	if (posIndex == -1)
	{
		assertion(false, "Update requires vertex positions\n");
		return;
	}

	VertexFormat::AttributeType posType =
		mVFormat->GetAttributeType(posIndex);
	if (posType != VertexFormat::AT_FLOAT3
		&&  posType != VertexFormat::AT_FLOAT4)
	{
		assertion(false, "Positions must be 3-tuples or 4-tuples\n");
		return;
	}

	char* data = mVBuffer->GetData();
	int posOffset = mVFormat->GetOffset(posIndex);
	mModelBound.ComputeFromData(numVertices, stride, data + posOffset);
}
//----------------------------------------------------------------------------
void Renderable::GetVisibleSet (Culler& culler, bool)
{
	AdjustTransparent();

	const Camera *camera = culler.GetCamera();

	assertion(camera!=0, "camera must not be 0.");

	AVector cameraDir = camera->GetDVector();
	AVector diff = WorldBound.GetCenter() - camera->GetPosition();

	mEyeDistance = cameraDir.Dot(diff);

	culler.Insert(this);
}
//----------------------------------------------------------------------------
void Renderable::AdjustTransparent ()
{
	if (!mMaterial)
	{
		SetTransparent(false);
		return;
	}

	for (int i=0; i<mMaterial->GetNumPasses(); i++)
	{
		AlphaProperty *alphaProperty =
			mMaterial->GetPass(i)->GetAlphaProperty();
		if (alphaProperty)
		{
			if (alphaProperty->BlendEnabled)
			{
				SetTransparent(true);
				return;
			}
			else
			{
				SetTransparent(false);
				return;
			}
		}
	}

	SetTransparent(false);
}
//----------------------------------------------------------------------------
bool Renderable::LessThan (const Renderable *renderable0,
						   const Renderable *renderable1)
{
	if (renderable0->mSortIndex == renderable1->mSortIndex)
	{
		if (renderable0->IsTransparent())
			return renderable0->mEyeDistance > renderable1->mEyeDistance;
		else
		{
			return renderable0 < renderable1;
		}
	}

	return renderable0->mSortIndex < renderable1->mSortIndex;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Begin load/save
//----------------------------------------------------------------------------
void Renderable::LoadPX2VF (const std::string& name, PrimitiveType& type,
					   VertexFormat*& vformat, VertexBuffer*& vbuffer, IndexBuffer*& ibuffer,
					   int mode)
{
	FileIO inFile(name, mode);
	if (!inFile)
	{
		assertion(false, "Failed to open file %s\n", name.c_str());
		return;
	}

	int iType;
	inFile.Read(sizeof(int), &iType);
	type = (PrimitiveType)iType;

	vformat = LoadVertexFormat(inFile);
	vbuffer = LoadVertexBuffer(inFile, vformat);
	ibuffer = LoadIndexBuffer(inFile);

	inFile.Close();
}
//----------------------------------------------------------------------------
void Renderable::SavePX2VF (const std::string& name, int mode)
{
	FileIO outFile(name, mode);
	if (!outFile)
	{
		assertion(false, "Failed to open file %s\n", name.c_str());
		return;
	}

	int type = (int)mType;
	outFile.Write(sizeof(int), &type);

	SaveVertexFormat(outFile);
	SaveVertexBuffer(outFile);
	SaveIndexBuffer(outFile);

	outFile.Close();
}
//----------------------------------------------------------------------------
VertexFormat* Renderable::LoadVertexFormat (FileIO& inFile)
{
	int numAttributes;
	inFile.Read(sizeof(int), &numAttributes);

	VertexFormat* vformat = new0 VertexFormat(numAttributes);
	for (int i = 0; i < numAttributes; ++i)
	{
		unsigned int streamIndex, offset, usageIndex;
		int type, usage;

		inFile.Read(sizeof(unsigned int), &streamIndex);
		inFile.Read(sizeof(unsigned int), &offset);
		inFile.Read(sizeof(int), &type);
		inFile.Read(sizeof(int), &usage);
		inFile.Read(sizeof(unsigned int), &usageIndex);

		vformat->SetAttribute(i, streamIndex, offset,
			(VertexFormat::AttributeType)type,
			(VertexFormat::AttributeUsage)usage, usageIndex);
	}

	int stride;
	inFile.Read(sizeof(int), &stride);
	vformat->SetStride(stride);

	return vformat;
}
//----------------------------------------------------------------------------
VertexBuffer* Renderable::LoadVertexBuffer (FileIO& inFile, VertexFormat* vformat)
{
	int numElements, elementSize, usage;
	inFile.Read(sizeof(int), &numElements);
	inFile.Read(sizeof(int), &elementSize);
	inFile.Read(sizeof(int), &usage);

	VertexBuffer* vbuffer = new0 VertexBuffer(numElements, elementSize,
		(Buffer::Usage)usage);

	VertexBufferAccessor vba(vformat, vbuffer);
	vba.Read(inFile);

	return vbuffer;
}
//----------------------------------------------------------------------------
IndexBuffer* Renderable::LoadIndexBuffer (FileIO& inFile)
{
	int numElements;
	inFile.Read(sizeof(int), &numElements);

	if (numElements > 0)
	{
		int elementSize, usage, offset;
		inFile.Read(sizeof(int), &elementSize);
		inFile.Read(sizeof(int), &usage);
		inFile.Read(sizeof(int), &offset);

		IndexBuffer* ibuffer = new0 IndexBuffer(numElements, elementSize,
			(Buffer::Usage)usage);
		ibuffer->SetOffset(offset);

		inFile.Read(elementSize, ibuffer->GetNumBytes()/elementSize,
			ibuffer->GetData());

		return ibuffer;
	}

	return 0;
}
//----------------------------------------------------------------------------
void Renderable::SaveVertexFormat (FileIO& outFile)
{
	int numAttributes = mVFormat->GetNumAttributes();
	outFile.Write(sizeof(int), &numAttributes);

	for (int i = 0; i < numAttributes; ++i)
	{
		unsigned int streamIndex, offset, usageIndex;
		VertexFormat::AttributeType vftype;
		VertexFormat::AttributeUsage vfusage;
		mVFormat->GetAttribute(i, streamIndex, offset, vftype, vfusage,
			usageIndex);
		int type = (int)vftype;
		int usage = (int)vfusage;

		outFile.Write(sizeof(unsigned int), &streamIndex);
		outFile.Write(sizeof(unsigned int), &offset);
		outFile.Write(sizeof(int), &type);
		outFile.Write(sizeof(int), &usage);
		outFile.Write(sizeof(unsigned int), &usageIndex);
	}

	int stride = mVFormat->GetStride();
	outFile.Write(sizeof(int), &stride);
}
//----------------------------------------------------------------------------
void Renderable::SaveVertexBuffer (FileIO& outFile)
{
	int numElements = mVBuffer->GetNumElements();
	int elementSize = mVBuffer->GetElementSize();
	Buffer::Usage vbusage = mVBuffer->GetUsage();
	int usage = (int)vbusage;
	outFile.Write(sizeof(int), &numElements);
	outFile.Write(sizeof(int), &elementSize);
	outFile.Write(sizeof(int), &usage);

	VertexBufferAccessor vba(mVFormat, mVBuffer);
	vba.Write(outFile);
}
//----------------------------------------------------------------------------
void Renderable::SaveIndexBuffer (FileIO& outFile)
{
	if (mIBuffer)
	{
		int numElements = mIBuffer->GetNumElements();
		int elementSize = mIBuffer->GetElementSize();
		Buffer::Usage ibusage = mIBuffer->GetUsage();
		int usage = (int)ibusage;
		int offset = mIBuffer->GetOffset();
		outFile.Write(sizeof(int), &numElements);
		outFile.Write(sizeof(int), &elementSize);
		outFile.Write(sizeof(int), &usage);
		outFile.Write(sizeof(int), &offset);

		outFile.Write(elementSize, mIBuffer->GetNumBytes()/elementSize,
			mIBuffer->GetData());
	}
	else
	{
		int numElements = 0;
		outFile.Write(sizeof(int), &numElements);
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Property
//----------------------------------------------------------------------------
void Renderable::RegistProperties ()
{
	Movable::RegistProperties();

	AddPropertyClass("Renderable");

	std::vector<std::string> primitiveTypes;
	primitiveTypes.push_back("PT_NONE");
	primitiveTypes.push_back("PT_POLYPOINT");
	primitiveTypes.push_back("PT_POLYSEGMENTS_DISJOINT");
	primitiveTypes.push_back("PT_POLYSEGMENTS_CONTIGUOUS");
	primitiveTypes.push_back("PT_TRIANGLES");
	primitiveTypes.push_back("PT_TRIMESH");
	primitiveTypes.push_back("PT_TRISTRIP");
	primitiveTypes.push_back("PT_TRIFAN");
	AddPropertyEnum("PrimitiveType", (int)GetPrimitiveType(), primitiveTypes, 
		false);
	AddProperty("ModelBoundCenter", PT_APOINT3, GetModelBound().GetCenter(), false);
	AddProperty("ModelBoundRadius", PT_FLOAT, GetModelBound().GetRadius(), false);

	std::vector<std::string> renderLayers;
	renderLayers.push_back("RL_BACKGROUND");
	renderLayers.push_back("RL_SKY");
	renderLayers.push_back("RL_TERRAIN");
	renderLayers.push_back("RL_SCENE");
	renderLayers.push_back("RL_UI");
	renderLayers.push_back("RL_UI_RANGE");
	renderLayers.push_back("RL_UI_RANGE_ELEMENT");
	AddPropertyEnum("RenderLayer", (int)GetRenderLayer(), renderLayers);

	AddProperty("SortIndex", PT_INT, GetSortIndex(), false);
	AddProperty("NumLights", PT_INT, GetNumLights(), false);
	AddProperty("EyeDistance", PT_FLOAT, mEyeDistance, false);
	AddProperty("IsTransparent", PT_BOOL, IsTransparent(), false);

	AddProperty("IsBakeObject", PT_BOOL, IsBakeObject());
	AddProperty("IsBakeTarget", PT_BOOL, IsBakeTarget());

	std::vector<std::string> bakeSizeTypes;
	bakeSizeTypes.push_back("BST_NORMAL");
	bakeSizeTypes.push_back("BST_64");
	bakeSizeTypes.push_back("BST_128");
	bakeSizeTypes.push_back("BST_256");
	bakeSizeTypes.push_back("BST_512");
	bakeSizeTypes.push_back("BST_1024");
	AddPropertyEnum("BakeSizeType", (int)GetBakeSizeType(), bakeSizeTypes);
}
//----------------------------------------------------------------------------
void Renderable::OnPropertyChanged (const PropertyObject &obj)
{
	Movable::OnPropertyChanged(obj);

	if ("RenderLayer" == obj.Name)
	{
		SetRenderLayer((RenderLayer)PX2_ANY_AS(obj.Data, int));
	}
	else if ("IsBakeObject" == obj.Name)
	{
		SetBakeObject(PX2_ANY_AS(obj.Data, bool));
	}
	else if ("IsBakeTarget" == obj.Name)
	{
		SetBakeTarget(PX2_ANY_AS(obj.Data, bool));
	}
	else if ("BakeSizeType" == obj.Name)
	{
		SetBakeSizeType((BakeSizeType)PX2_ANY_AS(obj.Data, int));
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称支持
//----------------------------------------------------------------------------
Object* Renderable::GetObjectByName (const std::string& name)
{
	Object* found = Movable::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	PX2_GET_OBJECT_BY_NAME(mVFormat, name, found);
	PX2_GET_OBJECT_BY_NAME(mVBuffer, name, found);
	PX2_GET_OBJECT_BY_NAME(mIBuffer, name, found);
	PX2_GET_OBJECT_BY_NAME(mMaterial, name, found);

	return 0;
}
//----------------------------------------------------------------------------
void Renderable::GetAllObjectsByName (const std::string& name,
								  std::vector<Object*>& objects)
{
	Movable::GetAllObjectsByName(name, objects);

	PX2_GET_ALL_OBJECTS_BY_NAME(mVFormat, name, objects);
	PX2_GET_ALL_OBJECTS_BY_NAME(mVBuffer, name, objects);
	PX2_GET_ALL_OBJECTS_BY_NAME(mIBuffer, name, objects);
	PX2_GET_ALL_OBJECTS_BY_NAME(mMaterial, name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化
//----------------------------------------------------------------------------
Renderable::Renderable (LoadConstructor value)
:
Movable(value),
mType(PT_NONE),
mVFormat(0),
mVBuffer(0),
mIBuffer(0),
mMaterial(0),
mSortIndex(0),
mIsUseShareBuffers(false),
mDBObject_V(0),
mDBObject_I(0),
mIBOffset(0),
mIBNumElements(0),
mIsBackObject(true),
mIsBackTarget(false),
mIsUseLightTexture(false),
mBakeSizeType(BST_NORMAL)
{
	AllowRed = true;
	AllowGreen = true;
	AllowBlue = true;
	AllowAlpha = true;

	SetUpdatePriority(-1);
}
//----------------------------------------------------------------------------
void Renderable::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Movable::Load(source);
	PX2_VERSION_LOAD(source);

	source.ReadEnum(mType);
	source.ReadAggregate(mModelBound);
	source.ReadPointer(mVFormat);
	source.ReadPointer(mVBuffer);
	source.ReadPointer(mIBuffer);
	source.ReadPointer(mMaterial);
	source.ReadEnum(mLayer);
	SetRenderLayer(mLayer);

	int readedVersion = GetReadedVersion();
	if (1 <= readedVersion)
	{
		source.ReadBool(AllowRed);
		source.ReadBool(AllowGreen);
		source.ReadBool(AllowBlue);
		source.ReadBool(AllowAlpha);
	}
	if (2 <= readedVersion)
	{
		source.ReadPointer(mDefaultShine);
	}
	if (3 <= readedVersion)
	{
		source.ReadBool(mIsUseLightTexture);
		source.ReadString(mLightTexPath);
		source.ReadString(mNormalTexPath);
	}
	if (4 <= readedVersion)
	{
		source.ReadEnum(mBakeSizeType);
	}
	if (5 <= readedVersion)
	{
		source.ReadBool(mIsBackObject);
		source.ReadBool(mIsBackTarget);
		source.ReadPointer(mNormalMaterialInstance);
	}

	PX2_END_DEBUG_STREAM_LOAD(Renderable, source);
}
//----------------------------------------------------------------------------
void Renderable::Link (InStream& source)
{
	Movable::Link(source);

	source.ResolveLink(mVFormat);
	source.ResolveLink(mVBuffer);
	source.ResolveLink(mIBuffer);
	source.ResolveLink(mMaterial);
	source.ResolveLink(mDefaultShine);
	source.ResolveLink(mNormalMaterialInstance);
}
//----------------------------------------------------------------------------
void Renderable::PostLink ()
{
	Movable::PostLink();

	if (!mDefaultShine)
	{
		mDefaultShine = new0 Shine();
		mDefaultShine->SetName("DefaultShine");
	}
}
//----------------------------------------------------------------------------
bool Renderable::Register (OutStream& target) const
{
	if (Movable::Register(target))
	{
		target.Register(mVFormat);
		target.Register(mVBuffer);
		target.Register(mIBuffer);
		target.Register(mMaterial);
		target.Register(mDefaultShine);
		target.Register(mNormalMaterialInstance);

		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void Renderable::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Movable::Save(target);
	PX2_VERSION_SAVE(target);

	target.WriteEnum(mType);
	target.WriteAggregate(mModelBound);
	target.WritePointer(mVFormat);
	target.WritePointer(mVBuffer);
	target.WritePointer(mIBuffer);
	target.WritePointer(mMaterial);
	target.WriteEnum(mLayer);
	target.WriteBool(AllowRed);
	target.WriteBool(AllowGreen);
	target.WriteBool(AllowBlue);
	target.WriteBool(AllowAlpha);
	target.WritePointer(mDefaultShine);
	target.WriteBool(mIsUseLightTexture);
	target.WriteString(mLightTexPath);
	target.WriteString(mNormalTexPath);
	target.WriteEnum(mBakeSizeType);
	target.WriteBool(mIsBackObject);
	target.WriteBool(mIsBackTarget);
	target.WritePointer(mNormalMaterialInstance);

	PX2_END_DEBUG_STREAM_SAVE(Renderable, target);
}
//----------------------------------------------------------------------------
int Renderable::GetStreamingSize (Stream &stream) const
{
	int size = Movable::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);
	size += PX2_ENUMSIZE(mType);
	size += sizeof(mModelBound);
	size += PX2_POINTERSIZE(mVFormat);
	size += PX2_POINTERSIZE(mVBuffer);
	size += PX2_POINTERSIZE(mIBuffer);
	size += PX2_POINTERSIZE(mMaterial);
	size += PX2_ENUMSIZE(mLayer);

	if (Stream::ST_IN == stream.GetStreamType())
	{
		int readedVersion = GetReadedVersion();

		if (1 <= readedVersion)
		{
			size += PX2_BOOLSIZE(AllowRed);
			size += PX2_BOOLSIZE(AllowGreen);
			size += PX2_BOOLSIZE(AllowBlue);
			size += PX2_BOOLSIZE(AllowAlpha);
		}
		if (2 <= readedVersion)
		{
			size += PX2_POINTERSIZE(mDefaultShine);
		}
		if (3 <= readedVersion)
		{
			size += PX2_BOOLSIZE(mIsUseLightTexture);
			size += PX2_STRINGSIZE(mLightTexPath);
			size += PX2_STRINGSIZE(mNormalTexPath);
		}
		if (4 <= readedVersion)
		{
			size += PX2_ENUMSIZE(mBakeSizeType);
		}
		if (5 <= readedVersion)
		{
			size += PX2_BOOLSIZE(mIsBackObject);
			size += PX2_BOOLSIZE(mIsBackTarget);
			size += PX2_POINTERSIZE(mNormalMaterialInstance);
		}
	}
	else
	{
		size += PX2_BOOLSIZE(AllowRed);
		size += PX2_BOOLSIZE(AllowGreen);
		size += PX2_BOOLSIZE(AllowBlue);
		size += PX2_BOOLSIZE(AllowAlpha);
		size += PX2_POINTERSIZE(mDefaultShine);
		size += PX2_BOOLSIZE(mIsUseLightTexture);
		size += PX2_STRINGSIZE(mLightTexPath);
		size += PX2_STRINGSIZE(mNormalTexPath);
		size += PX2_BOOLSIZE(mBakeSizeType);
		size += PX2_BOOLSIZE(mIsBackObject);
		size += PX2_BOOLSIZE(mIsBackTarget);
		size += PX2_BOOLSIZE(mNormalMaterialInstance);
	}

	return size;
}
//----------------------------------------------------------------------------
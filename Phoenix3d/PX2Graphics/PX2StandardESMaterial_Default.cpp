/*
*
* �ļ�����	��	PX2StandardESMaterial_Default.cpp
*
*/

#include "PX2StandardESMaterial_Default.hpp"
#include "PX2PVWMatrixConstant.hpp"
#include "PX2WMatrixConstant.hpp"
#include "PX2CameraWorldPositionConstant.hpp"
#include "PX2ShineEmissiveConstant.hpp"
#include "PX2ShineAmbientConstant.hpp"
#include "PX2ShineDiffuseConstant.hpp"
#include "PX2ShineSpecularConstant.hpp"
#include "PX2LightAmbientConstant.hpp"
#include "PX2LightDiffuseConstant.hpp"
#include "PX2LightSpecularConstant.hpp"
#include "PX2LightAttenuationConstant.hpp"
#include "PX2LightModelDVectorConstant.hpp"
#include "PX2ShaderKeys.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Material, StandardESMaterial_Default);
PX2_IMPLEMENT_STREAM(StandardESMaterial_Default);
PX2_IMPLEMENT_FACTORY(StandardESMaterial_Default);
PX2_IMPLEMENT_DEFAULT_NAMES(Material, StandardESMaterial_Default);

//----------------------------------------------------------------------------
StandardESMaterial_Default::StandardESMaterial_Default ()
{
	VertexShader* vshader = new0 VertexShader("PX2.StandardESMaterial_Default",
		4, 3, 7, 0, false);
	vshader->SetInput(0, "modelPosition", Shader::VT_FLOAT3, Shader::VS_POSITION);
	vshader->SetInput(1, "modelColor0", Shader::VT_FLOAT4, Shader::VS_COLOR0);
	vshader->SetInput(2, "modelNormal", Shader::VT_FLOAT3, Shader::VS_NORMAL);
	vshader->SetInput(3, "modelTCoord0", Shader::VT_FLOAT2, Shader::VS_TEXCOORD0);

	vshader->SetOutput(0, "clipPosition", Shader::VT_FLOAT4, Shader::VS_POSITION);
	vshader->SetOutput(1, "vertexTCoord0", Shader::VT_FLOAT2, Shader::VS_TEXCOORD0);
	vshader->SetOutput(2, "vertexTCoord1", Shader::VT_FLOAT4, Shader::VS_TEXCOORD1);

	vshader->SetConstant(0, "gPVWMatrix", 4);
	vshader->SetConstant(1, "gShineEmissive", 1);
	vshader->SetConstant(2, "gShineAmbient", 1);
	vshader->SetConstant(3, "gShineDiffuse", 1);
	vshader->SetConstant(4, "gLightAmbient", 1);
	vshader->SetConstant(5, "gLightDiffuse", 1);
	vshader->SetConstant(6, "gLightModelDirection", 1);
	vshader->SetBaseRegisters(msVRegisters);
	vshader->SetPrograms(msVPrograms);

	vshader->SetShaderKey(SKT_STANNDES_DEF);

	PixelShader* pshader = new0 PixelShader("PX2.StandardESMaterial_Default",
		2, 1, 0, 1, false);
	pshader->SetInput(0, "vertexTCoord0", Shader::VT_FLOAT2, Shader::VS_TEXCOORD0);
	pshader->SetInput(1, "vertexTCoord1", Shader::VT_FLOAT4, Shader::VS_TEXCOORD1);

	pshader->SetOutput(0, "pixelColor", Shader::VT_FLOAT4, Shader::VS_COLOR0);

	pshader->SetSampler(0, "gDiffuseSampler", Shader::ST_2D);
	pshader->SetFilter(0, Shader::SF_LINEAR);
	pshader->SetCoordinate(0, 0, Shader::SC_CLAMP);
	pshader->SetCoordinate(0, 1, Shader::SC_CLAMP);
	pshader->SetTextureUnits(msPTextureUnits);
	pshader->SetPrograms(msPPrograms);

	pshader->SetShaderKey(SKT_STANNDES_DEF);

	MaterialPass* pass = new0 MaterialPass();
	pass->SetVertexShader(vshader);
	pass->SetPixelShader(pshader);
	pass->SetAlphaProperty(new0 AlphaProperty());
	pass->SetCullProperty(new0 CullProperty());
	pass->SetDepthProperty(new0 DepthProperty());
	pass->SetOffsetProperty(new0 OffsetProperty());
	pass->SetStencilProperty(new0 StencilProperty());
	pass->SetWireProperty(new0 WireProperty());

	MaterialTechnique* technique = new0 MaterialTechnique();
	technique->InsertPass(pass);
	InsertTechnique(technique);
}
//----------------------------------------------------------------------------
StandardESMaterial_Default::~StandardESMaterial_Default ()
{
}
//----------------------------------------------------------------------------
MaterialInstance* StandardESMaterial_Default::CreateInstance (
	PX2::Texture2D *diffTex, PX2::Light *dirLight, PX2::Shine* shine) const
{
	MaterialInstance *instance = new0 MaterialInstance(this, 0);

	if (!dirLight)
	{
		dirLight = new0 Light(Light::LT_DIRECTIONAL);
		dirLight->Ambient = Float4(1.0f, 1.0f, 1.0f, 1.0f);
		dirLight->Diffuse = Float4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	if (!shine)
	{
		shine = new0 Shine();
		shine->Ambient = Float4(1.0f, 1.0f, 1.0f, 1.0f);
		shine->Diffuse = Float4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	// vertex
	instance->SetVertexConstant(0, "gPVWMatrix", new0 PVWMatrixConstant());
	instance->SetVertexConstant(0, "gShineEmissive", 
		new0 ShineEmissiveConstant(shine));
	instance->SetVertexConstant(0, "gShineAmbient",
		new0 ShineAmbientConstant(shine));
	instance->SetVertexConstant(0, "gShineDiffuse",
		new0 ShineDiffuseConstant(shine));
	instance->SetVertexConstant(0, "gLightAmbient",
		new0 LightAmbientConstant(dirLight));
	instance->SetVertexConstant(0, "gLightDiffuse",
		new0 LightDiffuseConstant(dirLight));
	instance->SetVertexConstant(0, "gLightModelDirection",
		new0 LightModelDVectorConstant(dirLight));

	// pixel
	if (diffTex)
	{
		//if (!diffTex->HasMipmaps())
		//	diffTex->GenerateMipmaps();
	}

	instance->SetPixelTexture(0, "gDiffuseSampler", diffTex);

	return instance;
}
//----------------------------------------------------------------------------
MaterialInstance* StandardESMaterial_Default::CreateUniqueInstance (	
	Texture2D *diffTex, Light *dirLight, Shine* shine)
{
	StandardESMaterial_Default *mtl = new0 StandardESMaterial_Default(); 
	return mtl->CreateInstance(diffTex, dirLight, shine);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Streaming support.
//----------------------------------------------------------------------------
StandardESMaterial_Default::StandardESMaterial_Default (LoadConstructor value)
	:
Material(value)
{
}
//----------------------------------------------------------------------------
void StandardESMaterial_Default::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Material::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(StandardESMaterial_Default, source);
}
//----------------------------------------------------------------------------
void StandardESMaterial_Default::Link (InStream& source)
{
	Material::Link(source);
}
//----------------------------------------------------------------------------
void StandardESMaterial_Default::PostLink ()
{
	Material::PostLink();

	MaterialPass* pass = mTechniques[0]->GetPass(0);
	VertexShader* vshader = pass->GetVertexShader();
	PixelShader* pshader = pass->GetPixelShader();
	vshader->SetBaseRegisters(msVRegisters);
	vshader->SetPrograms(msVPrograms);
	pshader->SetTextureUnits(msPTextureUnits);
	pshader->SetPrograms(msPPrograms);

	vshader->SetShaderKey(SKT_STANNDES_DEF);
	pshader->SetShaderKey(SKT_STANNDES_DEF);
}
//----------------------------------------------------------------------------
bool StandardESMaterial_Default::Register (OutStream& target) const
{
	if (Material::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void StandardESMaterial_Default::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Material::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(StandardESMaterial_Default, target);
}
//----------------------------------------------------------------------------
int StandardESMaterial_Default::GetStreamingSize (Stream &stream) const
{
	int size = Material::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);
	return size;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// profile
//----------------------------------------------------------------------------
int StandardESMaterial_Default::msDx9VRegisters[7] =
	{ 0, 4, 5, 6, 7, 8, 9 };
int StandardESMaterial_Default::msOglVRegisters[7] =
	{ 1, 5, 6, 7, 8, 9, 10 };
int StandardESMaterial_Default::msOpenGLES2VRegisters[7] = 
	{ 0, 0, 0, 0, 0, 0, 0 };
int* StandardESMaterial_Default::msVRegisters[Shader::MAX_PROFILES] =
{
	0,
	msDx9VRegisters,
	msDx9VRegisters,
	msDx9VRegisters,
	msOglVRegisters,
	msOpenGLES2VRegisters
};

std::string StandardESMaterial_Default::msVPrograms[Shader::MAX_PROFILES] =
{
	// VP_NONE
	"",

	// VP_VS_1_1
	"",

	// VP_VS_2_0
	"vs_2_0\n"
	"def c10, 1.00000000, 0.00000000, 0, 0\n"
	"dcl_position0 v0\n"
	"dcl_texcoord0 v3\n"
	"dcl_normal0 v2\n"
	"dcl_color0 v1\n"
	"mov r0.xyz, c8\n"
	"mov r1.xyz, c7\n"
	"mul r1.xyz, c5, r1\n"
	"dp3 r0.w, v2, -c9\n"
	"max r0.w, r0, c10.y\n"
	"mul r0.xyz, c6, r0\n"
	"add r1.xyz, r1, c4\n"
	"mad r0.xyz, r0, r0.w, r1\n"
	"mov r0.w, c6\n"
	"mul oT1, r0, v1\n"
	"mov r0.w, c10.x\n"
	"mov r0.xyz, v0\n"
	"dp4 oPos.w, r0, c3\n"
	"dp4 oPos.z, r0, c2\n"
	"dp4 oPos.y, r0, c1\n"
	"dp4 oPos.x, r0, c0\n"
	"mov oT0.xy, v3\n",

	// VP_VS_3_0
	"vs_3_0\n"
	"dcl_position o0\n"
	"dcl_texcoord0 o1\n"
	"dcl_texcoord1 o2\n"
	"def c10, 1.00000000, 0.00000000, 0, 0\n"
	"dcl_position0 v0\n"
	"dcl_texcoord0 v3\n"
	"dcl_normal0 v2\n"
	"dcl_color0 v1\n"
	"mov r0.xyz, c8\n"
	"mov r1.xyz, c7\n"
	"mul r1.xyz, c5, r1\n"
	"dp3 r0.w, v2, -c9\n"
	"max r0.w, r0, c10.y\n"
	"mul r0.xyz, c6, r0\n"
	"add r1.xyz, r1, c4\n"
	"mad r0.xyz, r0, r0.w, r1\n"
	"mov r0.w, c6\n"
	"mul o2, r0, v1\n"
	"mov r0.w, c10.x\n"
	"mov r0.xyz, v0\n"
	"dp4 o0.w, r0, c3\n"
	"dp4 o0.z, r0, c2\n"
	"dp4 o0.y, r0, c1\n"
	"dp4 o0.x, r0, c0\n"
	"mov o1.xy, v3\n",

	// VP_ARBVP1
	"",

	// vp_gles2
	"uniform mat4 gPVWMatrix;\n"
	"uniform mediump vec4 gShineEmissive;\n"
	"uniform mediump vec4 gShineAmbient;\n"
	"uniform mediump vec4 gShineDiffuse;\n"
	"uniform mediump vec4 gLightAmbient;\n"
	"uniform mediump vec4 gLightDiffuse;\n"
	"uniform mediump vec4 gLightModelDirection;\n"
	"attribute mediump vec3 modelPosition;\n"
	"attribute mediump vec3 modelNormal;\n"
	"attribute mediump vec2 modelTCoord0;\n"
	"varying mediump vec2 vertexTCoord0;\n"
	"varying mediump vec4 vertexTCoord1;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = gPVWMatrix*vec4(modelPosition, 1.0);\n"
	"	vertexTCoord0 = modelTCoord0;\n"
	"	vertexTCoord1.rgb = gShineEmissive.rgb"
	"		+ gLightAmbient.rgb*gShineAmbient.rgb"
	"		+ gLightDiffuse.rgb*gShineDiffuse.rgb"
	"		* max(0.0, dot(modelNormal, -gLightModelDirection.rgb));\n"
	"	vertexTCoord1.a = gShineDiffuse.a;\n"
	"}\n"
};

int StandardESMaterial_Default::msAllPTextureUnits[1] = { 0 };
int* StandardESMaterial_Default::msPTextureUnits[Shader::MAX_PROFILES] =
{
	0,
	msAllPTextureUnits,
	msAllPTextureUnits,
	msAllPTextureUnits,
	msAllPTextureUnits,
	msAllPTextureUnits
};

std::string StandardESMaterial_Default::msPPrograms[Shader::MAX_PROFILES] =
{
	// PP_NONE
	"",

	// PP_PS_1_1
	"",

	// PP_PS_2_0
	"ps_2_0\n"
	"dcl_2d s0\n"
	"def c0, 1.00000000, 0, 0, 0\n"
	"dcl t0.xy\n"
	"dcl t1\n"
	"mov r0.x, t0\n"
	"add r0.y, -t0, c0.x\n"
	"texld r0, r0, s0\n"
	"mul r0, r0, t1\n"
	"mov oC0, r0\n",

	// PP_PS_3_0
	"ps_3_0\n"
	"dcl_2d s0\n"
	"def c0, 1.00000000, 0, 0, 0\n"
	"dcl_texcoord0 v0.xy\n"
	"dcl_texcoord1 v1\n"
	"mov r0.x, v0\n"
	"add r0.y, -v0, c0.x\n"
	"texld r0, r0, s0\n"
	"mul oC0, r0, v1\n",

	// PP_ARBFP1
	"",

	// fp_gles2
	"varying mediump vec2 vertexTCoord0;\n"
	"varying mediump vec4 vertexTCoord1;\n"
	"uniform sampler2D gDiffuseSampler;\n"
	"void main()\n"
	"{\n"
	"	mediump vec2 texCoord0 = vec2(vertexTCoord0.x, 1.0-vertexTCoord0.y);\n"
	"	gl_FragColor = texture2D(gDiffuseSampler, texCoord0)*vertexTCoord1;\n"
	"}\n"
};
//----------------------------------------------------------------------------

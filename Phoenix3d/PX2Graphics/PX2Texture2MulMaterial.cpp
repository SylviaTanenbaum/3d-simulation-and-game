/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Texture2MulMaterial.cpp
*
*/

#include "PX2Texture2MulMaterial.hpp"
#include "PX2PVWMatrixConstant.hpp"
#include "PX2ShaderKeys.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Material, Texture2MulMaterial);
PX2_IMPLEMENT_STREAM(Texture2MulMaterial);
PX2_IMPLEMENT_FACTORY(Texture2MulMaterial);
PX2_IMPLEMENT_DEFAULT_NAMES(Material, Texture2MulMaterial);

//----------------------------------------------------------------------------
Texture2MulMaterial::Texture2MulMaterial ()
{
	VertexShader* vshader = new0 VertexShader("PX2.Texture2Mul",
		3, 3, 1, 0, false);
	vshader->SetInput(0, "modelPosition", Shader::VT_FLOAT3,
		Shader::VS_POSITION);
	vshader->SetInput(1, "modelTCoord0", Shader::VT_FLOAT2,
		Shader::VS_TEXCOORD0);
	vshader->SetInput(2, "modelTCoord1", Shader::VT_FLOAT2,
		Shader::VS_TEXCOORD1);
	vshader->SetOutput(0, "clipPosition", Shader::VT_FLOAT4,
		Shader::VS_POSITION);
	vshader->SetOutput(1, "vertexTCoord0", Shader::VT_FLOAT2,
		Shader::VS_TEXCOORD0);
	vshader->SetOutput(2, "vertexTCoord1", Shader::VT_FLOAT2,
		Shader::VS_TEXCOORD1);
	vshader->SetConstant(0, "PVWMatrix", 4);
	vshader->SetBaseRegisters(msVRegisters);
	vshader->SetPrograms(msVPrograms);

	PixelShader* pshader = new0 PixelShader("PX2.Texture2Mul",
		2, 1, 0, 2, false);
	pshader->SetInput(0, "vertexTCoord0", Shader::VT_FLOAT2,
		Shader::VS_TEXCOORD0);
	pshader->SetInput(1, "vertexTCoord1", Shader::VT_FLOAT2,
		Shader::VS_TEXCOORD1);
	pshader->SetOutput(0, "pixelColor", Shader::VT_FLOAT4,
		Shader::VS_COLOR0);
	pshader->SetSampler(0, "Sampler0", Shader::ST_2D);
	pshader->SetSampler(1, "Sampler1", Shader::ST_2D);
	pshader->SetTextureUnits(msPTextureUnits);
	pshader->SetPrograms(msPPrograms);

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

	vshader->SetShaderKey(SKT_TEXTURE2DMUL);
	pshader->SetShaderKey(SKT_TEXTURE2DMUL);
}
//----------------------------------------------------------------------------
Texture2MulMaterial::~Texture2MulMaterial ()
{
}
//----------------------------------------------------------------------------
PixelShader* Texture2MulMaterial::GetPixelShader () const
{
	return mTechniques[0]->GetPass(0)->GetPixelShader();
}
//----------------------------------------------------------------------------
MaterialInstance* Texture2MulMaterial::CreateInstance (Texture2D* texture0,
	Texture2D* texture1) const
{
	MaterialInstance* instance = new0 MaterialInstance(this, 0);
	instance->SetVertexConstant(0, 0, new0 PVWMatrixConstant());
	instance->SetPixelTexture(0, 0, texture0);
	instance->SetPixelTexture(0, 1, texture1);

	return instance;
}
//----------------------------------------------------------------------------
MaterialInstance* Texture2MulMaterial::CreateUniqueInstance (
	Texture2D* texture0, Shader::SamplerFilter filter0,
	Shader::SamplerCoordinate coordinate00,
	Shader::SamplerCoordinate coordinate01, Texture2D* texture1,
	Shader::SamplerFilter filter1, Shader::SamplerCoordinate coordinate10,
	Shader::SamplerCoordinate coordinate11)
{
	Texture2MulMaterial* effect = new0 Texture2MulMaterial();
	PixelShader* pshader = effect->GetPixelShader();
	pshader->SetFilter(0, filter0);
	pshader->SetCoordinate(0, 0, coordinate00);
	pshader->SetCoordinate(0, 1, coordinate01);
	pshader->SetFilter(1, filter1);
	pshader->SetCoordinate(1, 0, coordinate10);
	pshader->SetCoordinate(1, 1, coordinate11);
	return effect->CreateInstance(texture0, texture1);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Streaming support.
//----------------------------------------------------------------------------
Texture2MulMaterial::Texture2MulMaterial (LoadConstructor value)
	:
Material(value)
{
}
//----------------------------------------------------------------------------
void Texture2MulMaterial::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Material::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(Texture2MulMaterial, source);
}
//----------------------------------------------------------------------------
void Texture2MulMaterial::Link (InStream& source)
{
	Material::Link(source);
}
//----------------------------------------------------------------------------
void Texture2MulMaterial::PostLink ()
{
	Material::PostLink();

	MaterialPass* pass = mTechniques[0]->GetPass(0);
	VertexShader* vshader = pass->GetVertexShader();
	PixelShader* pshader = pass->GetPixelShader();
	vshader->SetBaseRegisters(msVRegisters);
	vshader->SetPrograms(msVPrograms);
	pshader->SetTextureUnits(msPTextureUnits);
	pshader->SetPrograms(msPPrograms);

	vshader->SetShaderKey(SKT_TEXTURE2DMUL);
	pshader->SetShaderKey(SKT_TEXTURE2DMUL);
}
//----------------------------------------------------------------------------
bool Texture2MulMaterial::Register (OutStream& target) const
{
	return Material::Register(target);
}
//----------------------------------------------------------------------------
void Texture2MulMaterial::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Material::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(Texture2MulMaterial, target);
}
//----------------------------------------------------------------------------
int Texture2MulMaterial::GetStreamingSize (Stream &stream) const
{
	return Material::GetStreamingSize(stream);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Profiles.
//----------------------------------------------------------------------------
int Texture2MulMaterial::msDx9VRegisters[1] = { 0 };
int Texture2MulMaterial::msOglVRegisters[1] = { 1 };
int Texture2MulMaterial::msOpenGLES2VRegisters[1] = { 0 };
int* Texture2MulMaterial::msVRegisters[Shader::MAX_PROFILES] =
{
	0,
	msDx9VRegisters,
	msDx9VRegisters,
	msDx9VRegisters,
	msOglVRegisters,
	msOpenGLES2VRegisters
};

std::string Texture2MulMaterial::msVPrograms[Shader::MAX_PROFILES] =
{
	// VS_NONE
	"",

	// VS_1_1
	"vs_1_1\n"
	"def c4, 1.00000000, 0, 0, 0\n"
	"dcl_position0 v0\n"
	"dcl_texcoord0 v1\n"
	"dcl_texcoord1 v2\n"
	"mov r0.w, c4.x\n"
	"mov r0.xyz, v0\n"
	"dp4 oPos.w, r0, c3\n"
	"dp4 oPos.z, r0, c2\n"
	"dp4 oPos.y, r0, c1\n"
	"dp4 oPos.x, r0, c0\n"
	"mov oT0.xy, v1\n"
	"mov oT1.xy, v2\n",

	// VS_2_0
	"vs_2_0\n"
	"def c4, 1.00000000, 0, 0, 0\n"
	"dcl_position0 v0\n"
	"dcl_texcoord0 v1\n"
	"mov r0.w, c4.x\n"
	"mov r0.xyz, v0\n"
	"dp4 oPos.w, r0, c3\n"
	"dp4 oPos.z, r0, c2\n"
	"dp4 oPos.y, r0, c1\n"
	"dp4 oPos.x, r0, c0\n"
	"mov oT0.xy, v1\n",

	// VS_3_0
	"vs_3_0\n"
	"dcl_position o0\n"
	"dcl_texcoord0 o1\n"
	"def c4, 1.00000000, 0, 0, 0\n"
	"dcl_position0 v0\n"
	"dcl_texcoord0 v1\n"
	"mov r0.w, c4.x\n"
	"mov r0.xyz, v0\n"
	"dp4 o0.w, r0, c3\n"
	"dp4 o0.z, r0, c2\n"
	"dp4 o0.y, r0, c1\n"
	"dp4 o0.x, r0, c0\n"
	"mov o1.xy, v1\n",

	// ARBVP1
	"!!ARBvp1.0\n"
	"",

	// vp_gles2
	"uniform mat4 PVWMatrix;\n"
	"attribute mediump vec3 modelPosition;\n"
	"attribute mediump vec2 modelTCoord0;\n"
	"varying mediump vec2 vertexTCoord0;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = PVWMatrix * vec4(modelPosition, 1.0);\n"
	"	vertexTCoord0 = modelTCoord0;\n"
	"}\n"
};

int Texture2MulMaterial::msAllPTextureUnits[2] = { 0, 1 };
int* Texture2MulMaterial::msPTextureUnits[Shader::MAX_PROFILES] =
{
	0,
	msAllPTextureUnits,
	msAllPTextureUnits,
	msAllPTextureUnits,
	msAllPTextureUnits,
	msAllPTextureUnits
};

std::string Texture2MulMaterial::msPPrograms[Shader::MAX_PROFILES] =
{
	// PS_NONE
	"",

	// PS_1_1
	"ps.1.1\n"
	"tex t0\n"
	"tex t1\n"
	"mul r0, t0, t1\n",

	// PS_2_0
	"ps_2_0\n"
	"dcl_2d s0\n"
	"dcl_2d s1\n"
	"def c0, 1.00000000, 0, 0, 0\n"
	"dcl t0.xy\n"
	"mov r1.x, t0\n"
	"add r1.y, -t0, c0.x\n"
	"texld r0, r1, s1\n"
	"texld r1, r1, s0\n"
	"mul r0, r1, r0\n"
	"mov oC0, r0\n",

	// PS_3_0
	"ps_3_0\n"
	"dcl_2d s0\n"
	"dcl_2d s1\n"
	"def c0, 1.00000000, 0, 0, 0\n"
	"dcl_texcoord0 v0.xy\n"
	"mov r0.x, v0\n"
	"add r0.y, -v0, c0.x\n"
	"texld r1, r0, s1\n"
	"texld r0, r0, s0\n"
	"mul oC0, r0, r1\n",

	// ARBFP1
	"!!ARBfp1.0\n"
	"",

	// fp_gles2
	"varying mediump vec2 vertexTCoord0;\n"
	"uniform sampler2D Sampler0;\n"
	"uniform sampler2D Sampler1;\n"
	"void main()\n"
	"{\n"
	"	mediump vec2 texCoord0 = vec2(vertexTCoord0.x, 1.0-vertexTCoord0.y);\n"
	"	mediump vec4 color0 = texture2D(Sampler0, texCoord0);\n"
	"	mediump vec4 color1 = texture2D(Sampler1, texCoord0);\n"
	"	gl_FragColor.rgb = color0.rgb*color1.rgb;\n"
	"	gl_FragColor.a = 1.0;\n"
	"}\n"
};
//----------------------------------------------------------------------------
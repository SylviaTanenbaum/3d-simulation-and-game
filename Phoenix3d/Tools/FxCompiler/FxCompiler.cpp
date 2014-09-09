/*
*
* �ļ�����	��	FxCompiler.cpp
*
*/

#include "FxCompiler.hpp"

const std::string FxCompiler::msSrcBlendMode[AlphaProperty::SBM_QUANTITY] =
{
	"SBM_ZERO",
	"SBM_ONE",
	"SBM_DST_COLOR",
	"SBM_ONE_MINUS_DST_COLOR",
	"SBM_SRC_ALPHA",
	"SBM_ONE_MINUS_SRC_ALPHA",
	"SBM_DST_ALPHA",
	"SBM_ONE_MINUS_DST_ALPHA",
	"SBM_SRC_ALPHA_SATURATE",
	"SBM_CONSTANT_COLOR",
	"SBM_ONE_MINUS_CONSTANT_COLOR",
	"SBM_CONSTANT_ALPHA",
	"SBM_ONE_MINUS_CONSTANT_ALPHA"
};

const std::string FxCompiler::msDstBlendMode[AlphaProperty::DBM_QUANTITY] =
{
	"DBM_ZERO",
	"DBM_ONE",
	"DBM_SRC_COLOR",
	"DBM_ONE_MINUS_SRC_COLOR",
	"DBM_SRC_ALPHA",
	"DBM_ONE_MINUS_SRC_ALPHA",
	"DBM_DST_ALPHA",
	"DBM_ONE_MINUS_DST_ALPHA",
	"DBM_CONSTANT_COLOR",
	"DBM_ONE_MINUS_CONSTANT_COLOR",
	"DBM_CONSTANT_ALPHA",
	"DBM_ONE_MINUS_CONSTANT_ALPHA"
};

const std::string FxCompiler::msAlphaCompareMode[AlphaProperty::CM_QUANTITY] =
{
	"CM_NEVER",
	"CM_LESS",
	"CM_EQUAL",
	"CM_LEQUAL",
	"CM_GREATER",
	"CM_NOTEQUAL",
	"CM_GEQUAL",
	"CM_ALWAYS"
};

const std::string FxCompiler::msDepthCompareMode[DepthProperty::CM_QUANTITY] =
{
	"CM_NEVER",
	"CM_LESS",
	"CM_EQUAL",
	"CM_LEQUAL",
	"CM_GREATER",
	"CM_NOTEQUAL",
	"CM_GEQUAL",
	"CM_ALWAYS"
};

const std::string FxCompiler::msStencilCompareMode[StencilProperty::CM_QUANTITY] =
{
	"CM_NEVER",
	"CM_LESS",
	"CM_EQUAL",
	"CM_LEQUAL",
	"CM_GREATER",
	"CM_NOTEQUAL",
	"CM_GEQUAL",
	"CM_ALWAYS"
};

const std::string FxCompiler::msStencilOperationType[StencilProperty::OT_QUANTITY] =
{
	"OT_KEEP",
	"OT_ZERO",
	"OT_REPLACE",
	"OT_INCREMENT",
	"OT_DECREMENT",
	"OT_INVERT"
};

const std::string FxCompiler::msVProfileName[Shader::MAX_PROFILES] =
{
	"",
	"vs_1_1",
	"vs_2_0",
	"vs_3_0",
	"arbvp1",
	"vp_gles2"
};

const std::string FxCompiler::msPProfileName[Shader::MAX_PROFILES] =
{
	"",
	"ps_1_1",
	"ps_2_0",
	"ps_3_0",
	"arbfp1",
	"fp_gles2"
};

const std::string FxCompiler::msVTName[Shader::VT_QUANTITY] =
{
	"VT_NONE",

	"VT_FLOAT",
	"VT_FLOAT1",   "VT_FLOAT2",   "VT_FLOAT3",   "VT_FLOAT4",
	"VT_FLOAT1X1", "VT_FLOAT1X2", "VT_FLOAT1X3", "VT_FLOAT1X4",
	"VT_FLOAT2X1", "VT_FLOAT2X2", "VT_FLOAT2X3", "VT_FLOAT2X4",
	"VT_FLOAT3X1", "VT_FLOAT3X2", "VT_FLOAT3X3", "VT_FLOAT3X4",
	"VT_FLOAT4X1", "VT_FLOAT4X2", "VT_FLOAT4X3", "VT_FLOAT4X4",

	"VT_HALF",
	"VT_HALF1",    "VT_HALF2",    "VT_HALF3",    "VT_HALF4",
	"VT_HALF1X1",  "VT_HALF1X2",  "VT_HALF1X3",  "VT_HALF1X4",
	"VT_HALF2X1",  "VT_HALF2X2",  "VT_HALF2X3",  "VT_HALF2X4",
	"VT_HALF3X1",  "VT_HALF3X2",  "VT_HALF3X3",  "VT_HALF3X4",
	"VT_HALF4X1",  "VT_HALF4X2",  "VT_HALF4X3",  "VT_HALF4X4",

	"VT_INT",
	"VT_INT1",     "VT_INT2",     "VT_INT3",     "VT_INT4",
	"VT_INT1X1",   "VT_INT1X2",   "VT_INT1X3",   "VT_INT1X4",
	"VT_INT2X1",   "VT_INT2X2",   "VT_INT2X3",   "VT_INT2X4",
	"VT_INT3X1",   "VT_INT3X2",   "VT_INT3X3",   "VT_INT3X4",
	"VT_INT4X1",   "VT_INT4X2",   "VT_INT4X3",   "VT_INT4X4",

	"VT_FIXED",
	"VT_FIXED1",   "VT_FIXED2",   "VT_FIXED3",   "VT_FIXED4",
	"VT_FIXED1X1", "VT_FIXED1X2", "VT_FIXED1X3", "VT_FIXED1X4",
	"VT_FIXED2X1", "VT_FIXED2X2", "VT_FIXED2X3", "VT_FIXED2X4",
	"VT_FIXED3X1", "VT_FIXED3X2", "VT_FIXED3X3", "VT_FIXED3X4",
	"VT_FIXED4X1", "VT_FIXED4X2", "VT_FIXED4X3", "VT_FIXED4X4",

	"VT_BOOL",
	"VT_BOOL1",    "VT_BOOL2",    "VT_BOOL3",    "VT_BOOL4",
	"VT_BOOL1X1",  "VT_BOOL1X2",  "VT_BOOL1X3",  "VT_BOOL1X4",
	"VT_BOOL2X1",  "VT_BOOL2X2",  "VT_BOOL2X3",  "VT_BOOL2X4",
	"VT_BOOL3X1",  "VT_BOOL3X2",  "VT_BOOL3X3",  "VT_BOOL3X4",
	"VT_BOOL4X1",  "VT_BOOL4X2",  "VT_BOOL4X3",  "VT_BOOL4X4"
};

const std::string FxCompiler::msVSName[Shader::VS_QUANTITY] =
{
	"VS_NONE",
	"VS_POSITION",
	"VS_BLENDWEIGHT",
	"VS_NORMAL",
	"VS_COLOR0",
	"VS_COLOR1", 
	"VS_FOGCOORD",
	"VS_PSIZE",
	"VS_BLENDINDICES",
	"VS_TEXCOORD0",
	"VS_TEXCOORD1",
	"VS_TEXCOORD2",
	"VS_TEXCOORD3",
	"VS_TEXCOORD4",
	"VS_TEXCOORD5",
	"VS_TEXCOORD6",
	"VS_TEXCOORD7",
	"VS_FOG",
	"VS_TANGENT",
	"VS_BINORMAL",
	"VS_COLOR2",
	"VS_COLOR3",
	"VS_DEPTH0"
};

const std::string FxCompiler::msSTName[Shader::ST_QUANTITY] =
{
	"ST_NONE",
	"ST_1D",
	"ST_2D",
	"ST_3D",
	"ST_CUBE"
};

FxCompiler::FxCompiler ()
{
	mCompileSucceeded = false;
	mActiveProfile = 0;

	for (int i=0; i<(int)Shader::MAX_PROFILES; ++i)
	{
		mCgVStatus[i] = -1;
		mCgPStatus[i] = -1;
	}
}
//----------------------------------------------------------------------------
FxCompiler::~FxCompiler ()
{
	mCurMaterial = 0;
}
//----------------------------------------------------------------------------
bool FxCompiler::Compile (const std::string &XMLName)
{
	bool success = mXMLData.LoadFile(XMLName);
	if (success)
	{
		mRootNode = mXMLData.GetRootNode();
	}
	else
	{
		assertion(false, "Failed to load %s.", XMLName);
	}

	bool compileSuccess = false;

	// material
	XMLNode materialNode = mRootNode;
	if (!materialNode.IsNull())
	{
		if (!ProcessMaterialNode(materialNode))
		{
			assertion(false, "Process material node error.");

			compileSuccess = false;
		}
	}
	else
	{
		assertion(false, "Material node error.");

		compileSuccess = false;

		return false;
	}

	string fileName = string(materialNode.AttributeToString("name")) + 
		string(".px2fx");

	// ����
	mCurMaterial->SavePX2fx(fileName);

	return true;
}
//----------------------------------------------------------------------------
bool FxCompiler::ProcessMaterialNode (XMLNode materialNode)
{
	string materialName = materialNode.AttributeToString("name");

	mCurMaterial = new0 Material();
	mCurMaterial->SetName(materialName);

	// Technique
	XMLNode techniqueNode = materialNode.IterateChild();
	while (!techniqueNode.IsNull())
	{
		if (!ProcessTechniqueNode(techniqueNode))
		{
			assertion(false, "Process technique %s node failed.",
				techniqueNode.AttributeToString("name"));

			return false;
		}

		techniqueNode = materialNode.IterateChild(techniqueNode);
	}

	return true;
}
//----------------------------------------------------------------------------
bool FxCompiler::ProcessTechniqueNode (XMLNode techniqueNode)
{
	string techniqueName = techniqueNode.AttributeToString("name");

	MaterialTechniquePtr materialTechnique = new0 MaterialTechnique();
	materialTechnique->SetName(techniqueName);

	mCurMaterial->InsertTechnique(materialTechnique);

	// pass
	XMLNode passNode = techniqueNode.IterateChild();
	while (!passNode.IsNull())
	{
		if (!ProcessPassNode(passNode, materialTechnique))
		{
			assertion(false, "Process pass %s node failed.",
				passNode.AttributeToString("name"));

			return false;
		}

		passNode = techniqueNode.IterateChild(passNode);
	}

	return true;
}
//----------------------------------------------------------------------------
bool FxCompiler::ProcessPassNode (XMLNode passNode, MaterialTechnique* technique)
{
	string passName = passNode.AttributeToString("name");

	MaterialPassPtr materialPass = new0 MaterialPass();
	materialPass->SetName(passName);

	technique->InsertPass(materialPass);

	// vertexshader
	XMLNode vertexShaderNode = passNode.GetChild("vertexshader");
	XMLNode childNodeVS = vertexShaderNode.IterateChild();
	while (!childNodeVS.IsNull())
	{
		std::string name = childNodeVS.GetName();

		if ("var" == name)
		{
			std::string type(childNodeVS.AttributeToString("type"));
			std::string filename(childNodeVS.AttributeToString("file"));
			std::string entryname(childNodeVS.AttributeToString("entry"));
			
			if ("cg" == type)
			{
				if (!CompileShader(true, filename, entryname))
				{
					assertion(false, "Process vertexshader failed.");

					return false;
				}
			}
			else if ("gles2" == type)
			{
				mCgVStatus[5] = 0;
			}
		}

		childNodeVS = vertexShaderNode.IterateChild(childNodeVS);
	}

	// pixelshader
	XMLNode pixelShaderNode = passNode.GetChild("pixelshader");
	XMLNode childNodePS = pixelShaderNode.IterateChild();
	while (!childNodePS.IsNull())
	{
		std::string name = childNodePS.GetName();

		if ("var" == name)
		{
			std::string type(childNodePS.AttributeToString("type"));
			std::string filename(childNodePS.AttributeToString("file"));
			std::string entryname(childNodePS.AttributeToString("entry"));

			if ("cg" == type)
			{
				if (!CompileShader(false, filename, entryname))
				{
					assertion(false, "Process pixelshader failed.");

					return false;
				}
			}
			else if ("gles2" == type)
			{
				mCgPStatus[5] = 0;
			}
		}

		childNodePS = vertexShaderNode.IterateChild(childNodePS);
	}

	// �����ɫ����
	if (!CheakShaderPairs())
		return false;

	// renderproperty
	XMLNode renderPropertyNode = passNode.GetChild("renderproperty");
	if (!renderPropertyNode.IsNull())
	{
		XMLNode propertyNode = renderPropertyNode.IterateChild();
		while (!propertyNode.IsNull())
		{
			ProcessRenderProperty(propertyNode, materialPass);

			propertyNode = renderPropertyNode.IterateChild(propertyNode);
		}
	}
	else
	{
		materialPass->SetAlphaProperty(new0 AlphaProperty());
		materialPass->SetCullProperty(new0 CullProperty());
		materialPass->SetDepthProperty(new0 DepthProperty());
		materialPass->SetOffsetProperty(new0 OffsetProperty());
		materialPass->SetStencilProperty(new0 StencilProperty());
		materialPass->SetWireProperty(new0 WireProperty());
	}

	if (!UpdateMaterialPass(mCurVertexShaderName, mCurPixelShaderName, 
		materialPass))
		return false;

	return true;
}
//----------------------------------------------------------------------------
bool FxCompiler::CompileShader (bool v, string filename, string shaderName)
{
	std::string command;

	for (int i=1; i<Shader::MAX_PROFILES; ++i)
	{
		if (i==5)
			continue;

		if (v)
		{
			mCurVertexShaderName = shaderName;

			// ������ھɵĶ�����ɫ�����򣬽���ɾ��
			command = "del " + shaderName + "." + msVProfileName[i] + ".txt";
			system(command.c_str());

			// ���붥����ɫ��
			command = "cgc -profile " + msVProfileName[i];
			if (i == 1)
			{
				// VS_1_1 ��Ҫ�汾ѡ����Ϣ
				command += " -profileopts dcls";
			}
			command += " -entry v_" + shaderName + " -o " + shaderName + ".";
			command += msVProfileName[i] + ".txt " + filename;
			mCgVStatus[i] = system(command.c_str());
		}
		else
		{
			mCurPixelShaderName = shaderName;

			// ������ھɵ�������ɫ�����򣬽���ɾ��
			command = "del " + shaderName + "." + msPProfileName[1] + ".txt";
			system(command.c_str());

			// ����������ɫ��
			command = "cgc -profile " + msPProfileName[i];
			command += " -entry p_" + shaderName + " -o " + shaderName + ".";
			command += msPProfileName[i] + ".txt " + filename;
			mCgPStatus[i] = system(command.c_str()); 
		}

	} // end for (i=1; i<Shader::MAX_PROFILES; ++i)

	return true;
}
//----------------------------------------------------------------------------
bool FxCompiler::CheakShaderPairs ()
{
	mCompileSucceeded = false;
	std::string command;

	for (int i=1; i<Shader::MAX_PROFILES; ++i)
	{
		if (mCgVStatus[i] == 0 && mCgPStatus[i] == 0)
		{
			mCompileSucceeded = true;
			Messages.push_back("The profile pair " + msVProfileName[i] +
				" and " + msPProfileName[i] + " compiled.\n");
		}
		else
		{
			// ��ֻ��һ����ɫ������ɹ�ʱ���������������ɫ����ɾ��
			if (mCgVStatus[i] == 0)
			{
				// ������ɫ������ͨ����������ɫ��û��	
				command = "del " + mCurVertexShaderName + "." + msVProfileName[i] +
					".txt";
				system(command.c_str());
			}
			else
			{
				Messages.push_back("Profile " + msVProfileName[i] +
					" did not compile.\n");
			}

			if (mCgPStatus[i] == 0)
			{
				// ������ɫ������ͨ����������ɫ��û��	
				command = "del " + mCurPixelShaderName + "." + msPProfileName[i] +
					".txt";
				system(command.c_str());
			}
			else
			{
				Messages.push_back("Profile " + msPProfileName[i] +
					" did not compile.\n");
			}

			Messages.push_back("The profile pair " + msVProfileName[i] +
				" and " + msPProfileName[i] + " did not compile.\n");
		}
	} // end for (i=1; i<Shader::MAX_PROFILES; ++i)

	if (!mCompileSucceeded)
	{
		Messages.push_back("All profiles failed to compile.\n");
		return false;
	}

	return true;
}
//----------------------------------------------------------------------------
bool FxCompiler::UpdateMaterialPass (string vertexShaderName,
	string pixelShaderName, MaterialPass *pass)
{
	InitializeMaps();

	Program vProgram[Shader::MAX_PROFILES];
	Program pProgram[Shader::MAX_PROFILES];

	for (int i=1; i<Shader::MAX_PROFILES; ++i)
	{
		if (5 == i)
			continue;

		mActiveProfile = i;

		std::string inVName = vertexShaderName + "." + msVProfileName[i] + ".txt";
		std::string inPName = pixelShaderName + "." + msPProfileName[i] + ".txt";

		bool hasVProfile = Parse(inVName, msVProfileName[i], vProgram[i]);

		bool hasPProfile = Parse(inPName, msPProfileName[i], pProgram[i]);

		if (hasVProfile && hasPProfile)
		{
			VertexShader *vShader = pass->GetVertexShader();
			PixelShader *pShader = pass->GetPixelShader();

			if (!vShader)
			{
				if (!CreateShaders(vProgram[i], pProgram[i], pass))
					return false;
			}
			else
			{
				if (!UpdateShaders(vProgram[i], pProgram[i], vShader, pShader))
					return false;

			}
		} // end if
	} // end for

	return true;
}
//----------------------------------------------------------------------------
bool FxCompiler::ProcessRenderProperty (XMLNode node, MaterialPass *pass)
{
	string propertyName = node.AttributeToString("property");

	if (propertyName == "Alpha")
	{
		AlphaPropertyPtr alphaProperty = new0 AlphaProperty();
		pass->SetAlphaProperty(alphaProperty);

		if (string(node.AttributeToString("param")) == "BlendEnabled")
		{
			alphaProperty->BlendEnabled = node.AttributeToBool("value");
		}
		else if (string(node.AttributeToString("param")) == "SrcBlend")
		{
			for (int i=0; i<(int)AlphaProperty::SBM_QUANTITY; i++)
			{
				if (node.AttributeToString("value") == msSrcBlendMode[i])
					alphaProperty->SrcBlend = (AlphaProperty::SrcBlendMode)i;
			}
		}
		else if (string(node.AttributeToString("param")) == "DstBlend")
		{
			for (int i=0; i<(int)AlphaProperty::DBM_QUANTITY; i++)
			{
				if (node.AttributeToString("value") == msDstBlendMode[i])
					alphaProperty->DstBlend = (AlphaProperty::DstBlendMode)i;
			}
		}
		else if (string(node.AttributeToString("param")) == "CompareEnabled")
		{
			alphaProperty->CompareEnabled = node.AttributeToBool("value");
		}
		else if (string(node.AttributeToString("param")) == "Compare")
		{
			for (int i=0; i<(int)AlphaProperty::CM_QUANTITY; i++)
			{
				if (string(node.AttributeToString("value")) == msAlphaCompareMode[i])
					alphaProperty->Compare = (AlphaProperty::CompareMode)i;
			}
		}
		else if (string(node.AttributeToString("param")) == "Reference")
		{
			alphaProperty->Reference = node.AttributeToFloat("value");
		}
		else if (string(node.AttributeToString("param")) == "ConstantColor")
		{
			alphaProperty->ConstantColor = StringToFloat4(node.AttributeToString("value"));
		}
	}
	else if (propertyName == "Cull")
	{
		CullPropertyPtr cullProperty = new0 CullProperty();
		pass->SetCullProperty(cullProperty);

		if (string(node.AttributeToString("param")) == "Enabled")
		{
			cullProperty->Enabled = node.AttributeToBool("value");
		}
		else if (string(node.AttributeToString("param")) == "CCWOrder")
		{
			cullProperty->CCWOrder = node.AttributeToBool("value");
		}
	}
	else if (propertyName == "Depth")
	{
		DepthPropertyPtr depthProperty = new0 DepthProperty();
		pass->SetDepthProperty(depthProperty);

		if (string(node.AttributeToString("param")) == "Enabled")
		{
			depthProperty->Enabled = node.AttributeToBool("value");
		}
		else if (string(node.AttributeToString("param")) == "Writable")
		{
			depthProperty->Writable = node.AttributeToBool("value");
		}
		else if (string(node.AttributeToString("param")) == "Compare")
		{
			for (int i=0; i<(int)DepthProperty::CM_QUANTITY; i++)
			{
				if (string(node.AttributeToString("value")) == msDepthCompareMode[i])
				{
					depthProperty->Compare = DepthProperty::CompareMode(i);
				}
			}
		}
	}
	else if (propertyName == "Offset")
	{
		OffsetPropertyPtr offsetProperty = new0 OffsetProperty();
		pass->SetOffsetProperty(offsetProperty);

		if (string(node.AttributeToString("param")) == "FillEnabled")
		{
			offsetProperty->FillEnabled = node.AttributeToBool("value");
		}
		else if (string(node.AttributeToString("param")) == "LineEnabled")
		{
			offsetProperty->LineEnabled = node.AttributeToBool("LineEnabled");
		}
		else if (string(node.AttributeToString("param")) == "PointEnabled")
		{
			offsetProperty->Scale = node.AttributeToFloat("Scale");
		}
		else if (string(node.AttributeToString("param")) == "Bias")
		{
			offsetProperty->Bias = node.AttributeToFloat("Bias");
		}
	}
	else if (propertyName == "Stencil")
	{
		StencilPropertyPtr stencilProperty = new0 StencilProperty();
		pass->SetStencilProperty(stencilProperty);

		if (string(node.AttributeToString("param")) == "Enabled")
		{
			stencilProperty->Enabled = node.AttributeToBool("value");
		}
		else if (string(node.AttributeToString("param")) == "Compare")
		{
			for (int i=0; i<(int)StencilProperty::CM_QUANTITY; i++)
			{
				if (node.AttributeToString("value") == msStencilCompareMode[i])
				{
					stencilProperty->Compare = (StencilProperty::CompareMode)i;
				}
			}
		}
		else if (string(node.AttributeToString("param")) == "Reference")
		{
			stencilProperty->Reference = node.AttributeToInt("Reference");
		}
		else if (string(node.AttributeToString("param")) == "Mask")
		{
			stencilProperty->Mask = node.AttributeToInt("value");
		}
		else if (string(node.AttributeToString("param")) == "WriteMask")
		{
			stencilProperty->WriteMask = node.AttributeToInt("value");
		}
		else if (string(node.AttributeToString("param")) == "OnFail")
		{
			for (int i=0; i<(int)StencilProperty::OT_QUANTITY; i++)
			{
				if (node.AttributeToString("value") == msStencilOperationType[i])
					stencilProperty->OnFail = (StencilProperty::OperationType)i;
			}
		}
		else if (string(node.AttributeToString("param")) == "OnZFail")
		{
			for (int i=0; i<(int)StencilProperty::OT_QUANTITY; i++)
			{
				if (string(node.AttributeToString("value")) == msStencilOperationType[i])
					stencilProperty->OnZFail = (StencilProperty::OperationType)i;
			}
		}
		else if (string(node.AttributeToString("param")) == "OnZPass")
		{
			for (int i=0; i<(int)StencilProperty::OT_QUANTITY; i++)
			{
				if (string(node.AttributeToString("value")) == msStencilOperationType[i])
					stencilProperty->OnZPass = (StencilProperty::OperationType)i;
			}
		}
	}
	else if (propertyName == "Wire")
	{
		WirePropertyPtr wireProperty = new0 WireProperty();
		pass->SetWireProperty(wireProperty);

		if (string(node.AttributeToString("param")) == "Enabled")
			wireProperty->Enabled = node.AttributeToBool("Enabled");
	}

	return true;
}
//----------------------------------------------------------------------------
Float4 FxCompiler::StringToFloat4 (std::string value)
{
	Float4 color;
	//	char r = value.
	return color;
}
//----------------------------------------------------------------------------
void FxCompiler::InitializeMaps ()
{
	mVariableTypes.insert(std::make_pair("float", Shader::VT_FLOAT));
	mVariableTypes.insert(std::make_pair("float1", Shader::VT_FLOAT1));
	mVariableTypes.insert(std::make_pair("float2", Shader::VT_FLOAT2));
	mVariableTypes.insert(std::make_pair("float3", Shader::VT_FLOAT3));
	mVariableTypes.insert(std::make_pair("float4", Shader::VT_FLOAT4));
	mVariableTypes.insert(std::make_pair("float1x1", Shader::VT_FLOAT1X1));
	mVariableTypes.insert(std::make_pair("float1x2", Shader::VT_FLOAT1X2));
	mVariableTypes.insert(std::make_pair("float1x3", Shader::VT_FLOAT1X3));
	mVariableTypes.insert(std::make_pair("float1x4", Shader::VT_FLOAT1X4));
	mVariableTypes.insert(std::make_pair("float2x1", Shader::VT_FLOAT2X1));
	mVariableTypes.insert(std::make_pair("float2x2", Shader::VT_FLOAT2X2));
	mVariableTypes.insert(std::make_pair("float2x3", Shader::VT_FLOAT2X3));
	mVariableTypes.insert(std::make_pair("float2x4", Shader::VT_FLOAT2X4));
	mVariableTypes.insert(std::make_pair("float3x1", Shader::VT_FLOAT3X1));
	mVariableTypes.insert(std::make_pair("float3x2", Shader::VT_FLOAT3X2));
	mVariableTypes.insert(std::make_pair("float3x3", Shader::VT_FLOAT3X3));
	mVariableTypes.insert(std::make_pair("float3x4", Shader::VT_FLOAT3X4));
	mVariableTypes.insert(std::make_pair("float4x1", Shader::VT_FLOAT4X1));
	mVariableTypes.insert(std::make_pair("float4x2", Shader::VT_FLOAT4X2));
	mVariableTypes.insert(std::make_pair("float4x3", Shader::VT_FLOAT4X3));
	mVariableTypes.insert(std::make_pair("float4x4", Shader::VT_FLOAT4X4));

	mVariableTypes.insert(std::make_pair("half", Shader::VT_HALF));
	mVariableTypes.insert(std::make_pair("half1", Shader::VT_HALF1));
	mVariableTypes.insert(std::make_pair("half2", Shader::VT_HALF2));
	mVariableTypes.insert(std::make_pair("half3", Shader::VT_HALF3));
	mVariableTypes.insert(std::make_pair("half4", Shader::VT_HALF4));
	mVariableTypes.insert(std::make_pair("half1x1", Shader::VT_HALF1X1));
	mVariableTypes.insert(std::make_pair("half1x2", Shader::VT_HALF1X2));
	mVariableTypes.insert(std::make_pair("half1x3", Shader::VT_HALF1X3));
	mVariableTypes.insert(std::make_pair("half1x4", Shader::VT_HALF1X4));
	mVariableTypes.insert(std::make_pair("half2x1", Shader::VT_HALF2X1));
	mVariableTypes.insert(std::make_pair("half2x2", Shader::VT_HALF2X2));
	mVariableTypes.insert(std::make_pair("half2x3", Shader::VT_HALF2X3));
	mVariableTypes.insert(std::make_pair("half2x4", Shader::VT_HALF2X4));
	mVariableTypes.insert(std::make_pair("half3x1", Shader::VT_HALF3X1));
	mVariableTypes.insert(std::make_pair("half3x2", Shader::VT_HALF3X2));
	mVariableTypes.insert(std::make_pair("half3x3", Shader::VT_HALF3X3));
	mVariableTypes.insert(std::make_pair("half3x4", Shader::VT_HALF3X4));
	mVariableTypes.insert(std::make_pair("half4x1", Shader::VT_HALF4X1));
	mVariableTypes.insert(std::make_pair("half4x2", Shader::VT_HALF4X2));
	mVariableTypes.insert(std::make_pair("half4x3", Shader::VT_HALF4X3));
	mVariableTypes.insert(std::make_pair("half4x4", Shader::VT_HALF4X4));

	mVariableTypes.insert(std::make_pair("int", Shader::VT_INT));
	mVariableTypes.insert(std::make_pair("int1", Shader::VT_INT1));
	mVariableTypes.insert(std::make_pair("int2", Shader::VT_INT2));
	mVariableTypes.insert(std::make_pair("int3", Shader::VT_INT3));
	mVariableTypes.insert(std::make_pair("int4", Shader::VT_INT4));
	mVariableTypes.insert(std::make_pair("int1x1", Shader::VT_INT1X1));
	mVariableTypes.insert(std::make_pair("int1x2", Shader::VT_INT1X2));
	mVariableTypes.insert(std::make_pair("int1x3", Shader::VT_INT1X3));
	mVariableTypes.insert(std::make_pair("int1x4", Shader::VT_INT1X4));
	mVariableTypes.insert(std::make_pair("int2x1", Shader::VT_INT2X1));
	mVariableTypes.insert(std::make_pair("int2x2", Shader::VT_INT2X2));
	mVariableTypes.insert(std::make_pair("int2x3", Shader::VT_INT2X3));
	mVariableTypes.insert(std::make_pair("int2x4", Shader::VT_INT2X4));
	mVariableTypes.insert(std::make_pair("int3x1", Shader::VT_INT3X1));
	mVariableTypes.insert(std::make_pair("int3x2", Shader::VT_INT3X2));
	mVariableTypes.insert(std::make_pair("int3x3", Shader::VT_INT3X3));
	mVariableTypes.insert(std::make_pair("int3x4", Shader::VT_INT3X4));
	mVariableTypes.insert(std::make_pair("int4x1", Shader::VT_INT4X1));
	mVariableTypes.insert(std::make_pair("int4x2", Shader::VT_INT4X2));
	mVariableTypes.insert(std::make_pair("int4x3", Shader::VT_INT4X3));
	mVariableTypes.insert(std::make_pair("int4x4", Shader::VT_INT4X4));

	mVariableTypes.insert(std::make_pair("fixed", Shader::VT_FIXED));
	mVariableTypes.insert(std::make_pair("fixed1", Shader::VT_FIXED1));
	mVariableTypes.insert(std::make_pair("fixed2", Shader::VT_FIXED2));
	mVariableTypes.insert(std::make_pair("fixed3", Shader::VT_FIXED3));
	mVariableTypes.insert(std::make_pair("fixed4", Shader::VT_FIXED4));
	mVariableTypes.insert(std::make_pair("fixed1x1", Shader::VT_FIXED1X1));
	mVariableTypes.insert(std::make_pair("fixed1x2", Shader::VT_FIXED1X2));
	mVariableTypes.insert(std::make_pair("fixed1x3", Shader::VT_FIXED1X3));
	mVariableTypes.insert(std::make_pair("fixed1x4", Shader::VT_FIXED1X4));
	mVariableTypes.insert(std::make_pair("fixed2x1", Shader::VT_FIXED2X1));
	mVariableTypes.insert(std::make_pair("fixed2x2", Shader::VT_FIXED2X2));
	mVariableTypes.insert(std::make_pair("fixed2x3", Shader::VT_FIXED2X3));
	mVariableTypes.insert(std::make_pair("fixed2x4", Shader::VT_FIXED2X4));
	mVariableTypes.insert(std::make_pair("fixed3x1", Shader::VT_FIXED3X1));
	mVariableTypes.insert(std::make_pair("fixed3x2", Shader::VT_FIXED3X2));
	mVariableTypes.insert(std::make_pair("fixed3x3", Shader::VT_FIXED3X3));
	mVariableTypes.insert(std::make_pair("fixed3x4", Shader::VT_FIXED3X4));
	mVariableTypes.insert(std::make_pair("fixed4x1", Shader::VT_FIXED4X1));
	mVariableTypes.insert(std::make_pair("fixed4x2", Shader::VT_FIXED4X2));
	mVariableTypes.insert(std::make_pair("fixed4x3", Shader::VT_FIXED4X3));
	mVariableTypes.insert(std::make_pair("fixed4x4", Shader::VT_FIXED4X4));

	mVariableTypes.insert(std::make_pair("bool", Shader::VT_BOOL));
	mVariableTypes.insert(std::make_pair("bool1", Shader::VT_BOOL1));
	mVariableTypes.insert(std::make_pair("bool2", Shader::VT_BOOL2));
	mVariableTypes.insert(std::make_pair("bool3", Shader::VT_BOOL3));
	mVariableTypes.insert(std::make_pair("bool4", Shader::VT_BOOL4));
	mVariableTypes.insert(std::make_pair("bool1x1", Shader::VT_BOOL1X1));
	mVariableTypes.insert(std::make_pair("bool1x2", Shader::VT_BOOL1X2));
	mVariableTypes.insert(std::make_pair("bool1x3", Shader::VT_BOOL1X3));
	mVariableTypes.insert(std::make_pair("bool1x4", Shader::VT_BOOL1X4));
	mVariableTypes.insert(std::make_pair("bool2x1", Shader::VT_BOOL2X1));
	mVariableTypes.insert(std::make_pair("bool2x2", Shader::VT_BOOL2X2));
	mVariableTypes.insert(std::make_pair("bool2x3", Shader::VT_BOOL2X3));
	mVariableTypes.insert(std::make_pair("bool2x4", Shader::VT_BOOL2X4));
	mVariableTypes.insert(std::make_pair("bool3x1", Shader::VT_BOOL3X1));
	mVariableTypes.insert(std::make_pair("bool3x2", Shader::VT_BOOL3X2));
	mVariableTypes.insert(std::make_pair("bool3x3", Shader::VT_BOOL3X3));
	mVariableTypes.insert(std::make_pair("bool3x4", Shader::VT_BOOL3X4));
	mVariableTypes.insert(std::make_pair("bool4x1", Shader::VT_BOOL4X1));
	mVariableTypes.insert(std::make_pair("bool4x2", Shader::VT_BOOL4X2));
	mVariableTypes.insert(std::make_pair("bool4x3", Shader::VT_BOOL4X3));
	mVariableTypes.insert(std::make_pair("bool4x4", Shader::VT_BOOL4X4));

	mSemantics.insert(std::make_pair("POSITION", Shader::VS_POSITION));
	mSemantics.insert(std::make_pair("POSITION0", Shader::VS_POSITION));
	mSemantics.insert(std::make_pair("BLENDWEIGHT", Shader::VS_BLENDWEIGHT));
	mSemantics.insert(std::make_pair("NORMAL", Shader::VS_NORMAL));
	mSemantics.insert(std::make_pair("NORMAL0", Shader::VS_NORMAL));
	mSemantics.insert(std::make_pair("COLOR", Shader::VS_COLOR0));
	mSemantics.insert(std::make_pair("COLOR0", Shader::VS_COLOR0));
	mSemantics.insert(std::make_pair("COLOR1", Shader::VS_COLOR1));
	mSemantics.insert(std::make_pair("FOGCOORD", Shader::VS_FOGCOORD));
	mSemantics.insert(std::make_pair("PSIZE", Shader::VS_PSIZE));
	mSemantics.insert(std::make_pair("BLENDINDICES", Shader::VS_BLENDINDICES));
	mSemantics.insert(std::make_pair("TEXCOORD0", Shader::VS_TEXCOORD0));
	mSemantics.insert(std::make_pair("TEXCOORD1", Shader::VS_TEXCOORD1));
	mSemantics.insert(std::make_pair("TEXCOORD2", Shader::VS_TEXCOORD2));
	mSemantics.insert(std::make_pair("TEXCOORD3", Shader::VS_TEXCOORD3));
	mSemantics.insert(std::make_pair("TEXCOORD4", Shader::VS_TEXCOORD4));
	mSemantics.insert(std::make_pair("TEXCOORD5", Shader::VS_TEXCOORD5));
	mSemantics.insert(std::make_pair("TEXCOORD6", Shader::VS_TEXCOORD6));
	mSemantics.insert(std::make_pair("TEXCOORD7", Shader::VS_TEXCOORD7));
	mSemantics.insert(std::make_pair("FOG", Shader::VS_FOG));
	mSemantics.insert(std::make_pair("TANGENT", Shader::VS_TANGENT));
	mSemantics.insert(std::make_pair("TANGENT0", Shader::VS_TANGENT));
	mSemantics.insert(std::make_pair("BINORMAL", Shader::VS_BINORMAL));
	mSemantics.insert(std::make_pair("BINORMAL0", Shader::VS_BINORMAL));
	mSemantics.insert(std::make_pair("COLOR2", Shader::VS_COLOR2));
	mSemantics.insert(std::make_pair("COLOR3", Shader::VS_COLOR3));
	mSemantics.insert(std::make_pair("DEPTH0", Shader::VS_DEPTH0));

	mSamplerTypes.insert(std::make_pair("sampler1D", Shader::ST_1D));
	mSamplerTypes.insert(std::make_pair("sampler2D", Shader::ST_2D));
	mSamplerTypes.insert(std::make_pair("samplerSHADOW", Shader::ST_2D));
	mSamplerTypes.insert(std::make_pair("sampler3D", Shader::ST_3D));
	mSamplerTypes.insert(std::make_pair("samplerCUBE", Shader::ST_CUBE));
}
//----------------------------------------------------------------------------
bool FxCompiler::Parse (const std::string& fileName,
	const std::string& profileName, Program& program)
{
	std::ifstream inFile(fileName.c_str());
	if (!inFile)
	{
		// �ļ������ڣ���������汾����ɫ������ʧ�ܡ�
		Messages.push_back("Profile " + profileName + " not supported.\n");
		return false;
	}

	program.Text = "";

	while (!inFile.eof())
	{
		// ���һ��
		std::string line;
		getline(inFile, line);

		if (line.empty())
			continue;

		// �κη�ע�����ݶ�����ɫ�������һ���֡�
		if (line[0] != '/' && line[0] != '#')
		{
			program.Text += line + "\n";
			continue;
		}

		std::vector<std::string> tokens;
		std::string::size_type begin;

		// ����
		begin = line.find("var", 0);
		if (begin != std::string::npos)
		{
			GetTokens(line, begin, tokens);
			if (tokens.size() >= 2 && tokens[0] == "var")
			{
				std::string used = tokens.back();
				if (used == "0" || used == "1")
				{
					if (used == "1")
					{
						program.Variables.push_back(tokens);
					}
					continue;
				}
			}
			inFile.close();
			ReportError("Invalid variable line", &tokens);
			return false;
		}

		// �汾
		begin = line.find("profile", 0);
		if (begin != std::string::npos)
		{
			GetTokens(line, begin, tokens);
			if (tokens.size() >= 2 && tokens[0] == "profile")
			{
				// When the user has already compiled the programs, it is
				// because a profile is a special one.  The "!!ARBfp1.0"
				// string and the last token of "#profile specialProfile"
				// most likely do not match, so do not compare them.
				if (tokens[1] == profileName)
				{
					continue;
				}
			}
			inFile.close();
			ReportError("Invalid profile line", &tokens);
			return false;
		}

		// ��ɫ�����ƣ���ɫ��������ڵ㣩
		begin = line.find("program", 0);
		if (begin != std::string::npos)
		{
			GetTokens(line, begin, tokens);
			if (tokens.size() >= 2 && tokens[0] == "program")
			{
				program.Name = tokens[1];
				continue;
			}
			inFile.close();
			ReportError("Invalid program line", &tokens);
			return false;
		}
	}

	inFile.close();
	return true;
}
//----------------------------------------------------------------------------
void FxCompiler::GetTokens (const std::string& line,
	std::string::size_type begin, std::vector<std::string>& tokens)
{
	while (begin != std::string::npos)
	{
		// ����һ��token������һ��token
		std::string::size_type end = line.find(" ", begin);

		// Extract the token.
		std::string token = line.substr(begin, end - begin);
		tokens.push_back(token);

		// �����ո�
		begin = line.find_first_not_of(" ", end);
	}
}
//----------------------------------------------------------------------------
bool FxCompiler::CreateShaders (const Program &vProgram, 
	const Program &pProgram,
	MaterialPass *pass)
{
	InputArray vInputs, pInputs;
	OutputArray vOutputs, pOutputs;
	ConstantArray vConstants, pConstants;
	SamplerArray vSamplers, pSamplers;

	if (!Process(vProgram, vInputs, vOutputs, vConstants, vSamplers))
	{
		return false;
	}

	if (!Process(pProgram, pInputs, pOutputs, pConstants, pSamplers))
	{
		return false;
	}

	VertexShaderPtr vertexShader = 
		(VertexShader*)CreateShader(true, vProgram, vInputs, vOutputs,
		vConstants, vSamplers);

	PixelShaderPtr pixelShader =
		(PixelShader*)CreateShader(false, pProgram, pInputs, pOutputs,
		pConstants, pSamplers);

	pass->SetVertexShader(vertexShader);
	pass->SetPixelShader(pixelShader);

	return true;
}
//----------------------------------------------------------------------------
bool FxCompiler::UpdateShaders (const Program &vProgram, 
	const Program &pProgram, VertexShader *vShader,
	PixelShader *pShader)
{
	InputArray vInputs, pInputs;
	OutputArray vOutputs, pOutputs;
	ConstantArray vConstants, pConstants;
	SamplerArray vSamplers, pSamplers;

	if (!Process(vProgram, vInputs, vOutputs, vConstants, vSamplers))
	{
		return false;
	}

	if (!Process(pProgram, pInputs, pOutputs, pConstants, pSamplers))
	{
		return false;
	}

	if (!UpdateShader(vShader, vProgram, vInputs, vOutputs, vConstants,
		vSamplers))
	{
		return false;
	}

	if (!UpdateShader(pShader, pProgram, pInputs, pOutputs, pConstants,
		pSamplers))
	{
		return false;
	}

	return true;
}
//----------------------------------------------------------------------------
bool FxCompiler::UpdateShader (Shader* shader, const Program& program,
	InputArray& inputs, OutputArray& outputs, 
	ConstantArray& constants, SamplerArray& samplers)
{
	int numInputs = (int)inputs.size();
	if (numInputs != shader->GetNumInputs())
	{
		ReportError("Mismatch in number of inputs.\n");
		return false;
	}

	int numOutputs = (int)outputs.size();
	if (numOutputs != shader->GetNumOutputs())
	{
		ReportError("Mismatch in number of outputs.\n");
		return false;
	}

	int numConstants = (int)constants.size();
	if (numConstants != shader->GetNumConstants())
	{
		ReportError("Mismatch in number of constants.\n");
		return false;
	}

	int numSamplers = (int)samplers.size();
	if (numSamplers != shader->GetNumSamplers())
	{
		ReportError("Mismatch in number of samplers.\n");
		return false;
	}

	std::string message;
	int i;
	for (i = 0; i < numInputs; ++i)
	{
		Input& input = inputs[i];
		if (input.Name != shader->GetInputName(i))
		{
			message =  "Mismatch in input names '" +
				input.Name +
				"' and '" +
				shader->GetInputName(i);

			ReportError(message);
			return false;
		}
		if (input.Type != shader->GetInputType(i))
		{
			message =  "Mismatch in input types '" +
				msVTName[input.Type] +
				"' and '" +
				msVTName[shader->GetInputType(i)];

			ReportError(message);
			return false;
		}
		if (input.Semantic != shader->GetInputSemantic(i))
		{
			message =  "Mismatch in input semantics '" +
				msVSName[input.Semantic] +
				"' and '" +
				msVSName[shader->GetInputSemantic(i)];

			ReportError(message);
			return false;
		}
	}

	for (i = 0; i < numOutputs; ++i)
	{
		Output& output = outputs[i];
		if (output.Name != shader->GetOutputName(i))
		{
			message =  "Mismatch in output names '" +
				output.Name +
				"' and '" +
				shader->GetOutputName(i);

			ReportError(message);
			return false;
		}
		if (output.Type != shader->GetOutputType(i))
		{
			message =  "Mismatch in output types '" +
				msVTName[output.Type] +
				"' and '" +
				msVTName[shader->GetOutputType(i)];

			ReportError(message);
			return false;
		}
		if (output.Semantic != shader->GetOutputSemantic(i))
		{
			message =  "Mismatch in output semantics '" +
				msVSName[output.Semantic] +
				"' and '" +
				msVSName[shader->GetOutputSemantic(i)];

			ReportError(message);
			return false;
		}
	}

	for (i = 0; i < numConstants; ++i)
	{
		Constant& constant = constants[i];
		if (constant.Name != shader->GetConstantName(i))
		{
			message =  "Mismatch in constant names '" +
				constant.Name +
				"' and '" +
				shader->GetConstantName(i);

			ReportError(message);
			return false;
		}
		if (constant.NumRegistersUsed != shader->GetNumRegistersUsed(i))
		{
			char number0[8], number1[8];
			sprintf(number0, "%d", constant.NumRegistersUsed);
			sprintf(number1, "%d", shader->GetNumRegistersUsed(i));
			message =  "Mismatch in constant registers used '" +
				std::string(number0) +
				"' and '" +
				std::string(number1);

			ReportError(message);
			return false;
		}
		shader->SetBaseRegister(mActiveProfile, i, constant.BaseRegister);
	}

	for (i = 0; i < numSamplers; ++i)
	{
		Sampler& sampler = samplers[i];
		if (sampler.Name != shader->GetSamplerName(i))
		{
			message =  "Mismatch in sampler names '" +
				sampler.Name +
				"' and '" +
				shader->GetSamplerName(i);

			ReportError(message);
			return false;
		}
		if (sampler.Type != shader->GetSamplerType(i))
		{
			message =  "Mismatch in sampler types '" +
				msSTName[sampler.Type] +
				"' and '" +
				msSTName[shader->GetSamplerType(i)];

			ReportError(message);
			return false;
		}
		shader->SetTextureUnit(mActiveProfile, i, sampler.Unit);
	}

	shader->SetProgram(mActiveProfile, program.Text);

	return true;
}
//----------------------------------------------------------------------------
bool FxCompiler::Process (const Program& program, InputArray& inputs,
	OutputArray& outputs, ConstantArray& constants,
	SamplerArray& samplers)
{
	// ��������������ʽ֮һ��
	//   var TYPE NAME : $vin.SEMANTIC  : inputType           : index : 1
	//   var TYPE NAME : $vout.SEMANTIC : outputType          : index : 1
	//   var TYPE NAME :                : c[REGISTER]         : index : 1
	//   var TYPE NAME :                : c[REGISTER], NUMREG : index : 1
	//   var TYPE NAME :                : texunit UNITNUMBER  : -1    : 1
	//   var TYPE NAME :                :		  UNITNUMBER  : -1    : 1	��// ps_1_1�У�
	// ���һ��ֵΪ��0�����ߡ�1������ʾ��������������ɫ���������Ƿ�ʹ�á�

	TokenArrays::const_iterator iter = program.Variables.begin();
	TokenArrays::const_iterator end = program.Variables.end();
	for (/**/; iter != end; ++iter)
	{
		const TokenArray& tokens = *iter;

		// token����ӵ��10����11��token��
		if (tokens.size() < 10 || tokens.size() > 11)
		{
			ReportError("Invalid number of tokens", &tokens);
			return false;
		}

		// ��ñ�������
		Shader::VariableType vartype = Shader::VT_NONE;
		Shader::SamplerType samtype = Shader::ST_NONE;
		std::string::size_type begin = tokens[1].find("sampler", 0);
		if (begin != std::string::npos)
		{
			SamplerTypeMap::iterator iter = mSamplerTypes.find(tokens[1]);
			if (iter == mSamplerTypes.end())
			{
				ReportError("Invalid sampler type", &tokens);
				return false;
			}
			samtype = iter->second;
		}
		else
		{
			VariableTypeMap::iterator iter = mVariableTypes.find(tokens[1]);
			if (iter == mVariableTypes.end())
			{
				ReportError("Invalid variable type", &tokens);
				return false;
			}
			vartype = iter->second;
		}

		// ��ñ�������
		std::string name = tokens[2];

		// ������ʱһ����һ��������һ�����顣�����һ�����飬������Ҫȷ��ʹ
		// �ö��ټĴ�����
		bool varArray;
		begin = name.find("[", 0);
		if (begin != std::string::npos)
		{
			varArray = true;
			name = name.substr(0, begin);  // ȥ�� "[register]"
		}
		else
		{
			varArray = false;
		}

		// �ָ���
		if (tokens[3] != ":")
		{
			ReportError("Expecting separator character at index 3", &tokens);
			return false;
		}

		// ȷ����������������������������
		begin = tokens[4].find("$vin.", 0);
		if (begin != std::string::npos)
		{
			// ���������
			if (!GetInput(tokens, name, vartype, inputs))
			{
				return false;
			}
			continue;
		}

		begin = tokens[4].find("$vout.", 0);
		if (begin != std::string::npos)
		{
			// ���������
			if (!GetOutput(tokens, name, vartype, outputs))
			{
				return false;
			}
			continue;
		}

		if (tokens[4] == ":")
		{
			begin = tokens[1].find("sampler", 0);
			if (begin != std::string::npos)
			{
				// ��������ɫ�����������
				if (!GetSampler(tokens, name, samtype, samplers))
				{
					return false;
				}
			}
			else
			{
				// ��������ɫ������
				if (varArray)
				{
					if (constants.size() > 0 && name == constants.back().Name)
					{
						// ��ɫ�����������һ��Ԫ�أ�ֻҪ��������һ��������ĩβ��
						// ���ӼĴ�������
						++constants.back().NumRegistersUsed;
					}
					else
					{
						// Ϊ��һ����������������ɫ������
						if (!GetConstant(tokens, name, vartype, constants))
						{
							return false;
						}
					}
				}
				else
				{
					if (!GetConstant(tokens, name, vartype, constants))
					{
						return false;
					}
				}
			}
			continue;
		}

		ReportError("Failed to find classifier", &tokens);
		return false;
	}

	return true;
}
//----------------------------------------------------------------------------
bool FxCompiler::GetInput (const TokenArray& tokens, const std::string& name,
	Shader::VariableType type, InputArray& inputs)
{
	std::string::size_type begin = 5;  // ����"$vin."
	std::string semanticName = tokens[4].substr(begin, std::string::npos);
	SemanticMap::iterator siter = mSemantics.find(semanticName);
	if (siter == mSemantics.end())
	{
		ReportError("Invalid $vin classifier", &tokens);
		return false;
	}

	Input input;
	input.Name = name;
	input.Type = type;
	input.Semantic = siter->second;
	inputs.push_back(input);
	return true;
}
//----------------------------------------------------------------------------
bool FxCompiler::GetOutput (const TokenArray& tokens, const std::string& name,
	Shader::VariableType type, OutputArray& outputs)
{
	std::string::size_type begin = 6;  // skip over "$vout."
	std::string semanticName = tokens[4].substr(begin, std::string::npos);
	SemanticMap::iterator siter = mSemantics.find(semanticName);
	if (siter == mSemantics.end())
	{
		ReportError("Invalid $vout classifier", &tokens);
		return false;
	}

	Output output;
	output.Name = name;
	output.Type = type;
	output.Semantic = siter->second;
	outputs.push_back(output);
	return true;
}
//----------------------------------------------------------------------------
bool FxCompiler::GetConstant (const TokenArray& tokens,
	const std::string& name, Shader::VariableType type,
	ConstantArray& constants)
{
	std::string::size_type begin, end;

	if (tokens[5].size() < 4
		||  tokens[5][0] != 'c'
		||  tokens[5][1] != '['
		||  (end = tokens[5].find("]", 0)) == std::string::npos)
	{
		ReportError("Expecting 'c[register]' token", &tokens);
		return false;
	}

	// ��ó����Ĵ�������
	begin = 2; // '['����һ���ַ�����
	std::string number = tokens[5].substr(begin, end - begin);
	int baseRegister = atoi(number.c_str());
	if (baseRegister == 0 && number != "0")
	{
		ReportError("Invalid base register", &tokens);
		return false;
	}

	// �����Ĵ�����Ԫ�ĸ�����һ���Ĵ�����ԪΪһ��float4��
	int numRegistersUsed;
	if (tokens[5].find(",", 0) == std::string::npos)
	{
		// �������ʹ��һ��float4
		numRegistersUsed = 1;
	}
	else
	{
		// ����ʹ�ö���Ĵ�����Ԫ
		numRegistersUsed = atoi(tokens[6].c_str());
		if (numRegistersUsed == 0)
		{
			ReportError("Invalid number of registers", &tokens);
			return false;
		}
	}

	Constant constant;
	constant.Name = name;
	constant.Type = type;
	constant.BaseRegister = baseRegister;
	constant.NumRegistersUsed = numRegistersUsed;
	constants.push_back(constant);
	return true;
}
//----------------------------------------------------------------------------
bool FxCompiler::GetSampler (const TokenArray& tokens,
	const std::string& name, Shader::SamplerType type,
	SamplerArray& samplers)
{
	int unit;

	if (mActiveProfile != 1)
	{
		if (tokens[5] != "texunit")
		{
			ReportError("Expecting 'texunit' token", &tokens);
			return false;
		}

		// ��ò���������ͼ��unit
		unit = atoi(tokens[6].c_str());
		if (unit == 0 && tokens[6] != "0")
		{
			ReportError("Invalid texture unit", &tokens);
			return false;
		}
	}
	else  // ps_1_1 (vs_1_1 ��֧���������)
	{
		// ��ò���������ͼ��unit
		unit = atoi(tokens[5].c_str());
		if (unit == 0 && tokens[5] != "0")
		{
			ReportError("Invalid texture unit", &tokens);
			return false;
		}
	}

	Sampler sampler;
	sampler.Name = name;
	sampler.Type = type;
	sampler.Unit = unit;
	sampler.Filter = Shader::SF_NEAREST;
	sampler.Coordinate[0] = Shader::SC_CLAMP_EDGE;
	sampler.Coordinate[1] = Shader::SC_CLAMP_EDGE;
	sampler.Coordinate[2] = Shader::SC_CLAMP_EDGE;
	sampler.LodBias = 0.0f;
	sampler.Anisotropy = 1.0f;
	sampler.BorderColor = Float4(0.0f, 0.0f, 0.0f, 0.0f);
	samplers.push_back(sampler);
	return true;
}
//----------------------------------------------------------------------------
Shader* FxCompiler::CreateShader (bool isVShader, const Program& program,
	InputArray& inputs, OutputArray& outputs, ConstantArray& constants,
	SamplerArray& samplers)
{
	int numInputs = (int)inputs.size();
	int numOutputs = (int)outputs.size();
	int numConstants = (int)constants.size();
	int numSamplers = (int)samplers.size();

	Shader* shader;
	if (isVShader)
	{
		shader = new0 VertexShader(program.Name, numInputs, numOutputs,
			numConstants, numSamplers, true);
	}
	else
	{
		shader = new0 PixelShader(program.Name, numInputs, numOutputs,
			numConstants, numSamplers, true);
	}

	int i;
	for (i = 0; i < numInputs; ++i)
	{
		Input& input = inputs[i];
		shader->SetInput(i, input.Name, input.Type, input.Semantic);
	}

	for (i = 0; i < numOutputs; ++i)
	{
		Output& output = outputs[i];
		shader->SetOutput(i, output.Name, output.Type, output.Semantic);
	}

	for (i = 0; i < numConstants; ++i)
	{
		Constant& constant = constants[i];
		shader->SetConstant(i, constant.Name, constant.NumRegistersUsed);
		shader->SetBaseRegister(mActiveProfile, i, constant.BaseRegister);
	}

	for (i = 0; i < numSamplers; ++i)
	{
		Sampler& sampler = samplers[i];
		shader->SetSampler(i, sampler.Name, sampler.Type);
		shader->SetFilter(i, sampler.Filter);
		shader->SetCoordinate(i, 0, sampler.Coordinate[0]);
		shader->SetCoordinate(i, 1, sampler.Coordinate[1]);
		shader->SetCoordinate(i, 2, sampler.Coordinate[2]);
		shader->SetLodBias(i, sampler.LodBias);
		shader->SetAnisotropy(i, sampler.Anisotropy);
		shader->SetBorderColor(i, sampler.BorderColor);
		shader->SetTextureUnit(mActiveProfile, i, sampler.Unit);
	}

	shader->SetProgram(mActiveProfile, program.Text);
	return shader;
}
//----------------------------------------------------------------------------
void FxCompiler::ReportError (const std::string& message,
	const TokenArray* tokens)
{
	Messages.push_back(message);
	if (tokens)
	{
		Messages.push_back(":");
		for (int i = 0; i < (int)tokens->size(); ++i)
		{
			Messages.push_back(" " + (*tokens)[i]);
		}
	}
	Messages.push_back("\n");

	assertion(false, "FxCompiler error.\n");
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// FxCompiler::Program
//----------------------------------------------------------------------------
FxCompiler::Program::Program ()
	:
Name(""),
	Text("")
{
}
//----------------------------------------------------------------------------
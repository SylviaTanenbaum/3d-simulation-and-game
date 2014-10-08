/*
*
* �ļ�����	��	PX2GraphicsRoot.cpp
*
*/

#include "PX2GraphicsRoot.hpp"
#include "PX2Environment.hpp"
#include "PX2StringHelp.hpp"
#include "PX2FString.hpp"
using namespace PX2;

std::string GraphicsRoot::PX2Path;
//----------------------------------------------------------------------------
GraphicsRoot::GraphicsRoot ()
{
	mFogParam = Float4(0.0f, 120.0f, 0.0f, 0.0f);
	mFogColor = Float4::RED;
}
//----------------------------------------------------------------------------
GraphicsRoot::~GraphicsRoot ()
{
}
//----------------------------------------------------------------------------
bool GraphicsRoot::Initlize ()
{
	// ����Ҫ����PX2_PATH����������Ӧ�ó��������ڴ˲��Ҹ�����Դ�ļ���
	PX2Path = Environment::GetVariable("PX2_PATH");
	//if (PX2Path == "")
	//{
	//	assertion(false, "Please set the PX2_PATH environment variable.\n");
	//	FILE* ofile = fopen("ApplicationError.txt", "w");
	//	fprintf(ofile, "Please set the PX2_PATH environment variable.\n");
	//	fclose(ofile);
	//	//return false;
	//}
	//PX2Path += "/";

	InitTerm::ExecuteInitializers();

	std::string directory;

	// Ӧ�ó���ǰĿ¼
	Environment::InsertDirectory("/");

	// Camera
#if defined (PX2_USE_DX9)
	// DirectXʹ�����������[0,1]�ڵľ���
	Camera::SetDefaultDepthType(Camera::PM_DEPTH_ZERO_TO_ONE);
#endif

#if defined(PX2_USE_OPENGL) || defined(PX2_USE_OPENGLES2)
	// OpenGLʹ�����������[-1,1]�ڵľ���
	Camera::SetDefaultDepthType(Camera::PM_DEPTH_MINUS_ONE_TO_ONE);
#endif

	return true;
}
//-----------------------------------------------------------------------------
bool GraphicsRoot::Terminate ()
{
	mCamera = 0;
	mAllLights.clear();

	Environment::RemoveAllDirectories();

	InitTerm::ExecuteTerminators();

	return true;
}
//----------------------------------------------------------------------------
void GraphicsRoot::AddLight (Light *light)
{
	bool bIn = false;
	for (int i=0; i<(int)mAllLights.size(); i++)
	{
		if (light == mAllLights[i])
			bIn = true;
	}

	if (!bIn)
	{
		mAllLights.push_back(light);
	}
}
//----------------------------------------------------------------------------
void GraphicsRoot::RemoveLight (Light *light)
{
	std::vector<Pointer0<Light> >::iterator it = mAllLights.begin();
	for (; it!=mAllLights.end(); it++)
	{
		if (*it == light)
		{
			mAllLights.erase(it);
			return;
		}
	}
}
//----------------------------------------------------------------------------
void GraphicsRoot::ClearAllLights ()
{
	mAllLights.clear();
}
//----------------------------------------------------------------------------
int GraphicsRoot::GetNumLights ()
{
	return (int)mAllLights.size();
}
//----------------------------------------------------------------------------
Light *GraphicsRoot::GetLight (int index)
{
	int numLights = (int)mAllLights.size();
	if (index>=0 && index<numLights)
	{
		return mAllLights[index];
	}

	return 0;
}
//----------------------------------------------------------------------------
/*
*
* �ļ�����	��	PX2ExportSettings.cpp
*
*/

#include "PX2ExportSettings.hpp"

//----------------------------------------------------------------------------
ExportSettings::ExportSettings ()
{
	// object ����
	IncludeObjects = true;
	IncludeLights = true;
	IncludeMeshes = true;

	// mesh ����
	IncludeVertexColors = false;
	IncludeNormals = true;
	IncludeTargentBiNormal = false;
	IncludeTexCoords = true;
	NumTexCoords = 1;

	// modifier ����    
	IncludeModifiers = true;
	IncludeSkins = true;

	// animation ����
	IncludeCurrentFrame = true;
	IncludeKeyFrames = false;
	IncludeAllFrames = false;
	UseLocalTime = true;
	StartFrame = 0;
	EndFrame = 0;

	memset(SrcRootDir, 0, 256);
	memset(DstRootDir, 0, 256);
}
//----------------------------------------------------------------------------
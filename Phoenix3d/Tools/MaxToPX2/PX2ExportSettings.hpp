/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2ExportSettings.hpp
*
* �汾		:	1.0 (2011/05/22)
*
* ����		��	more
*
*/

#ifndef PX2EXPORTSETTINGS_HPP
#define PX2EXPORTSETTINGS_HPP

#include "PX2MaxToPX2PluginPre.hpp"

class ExportSettings
{
public:
	ExportSettings ();

	// object ����
	bool IncludeObjects;
	bool IncludeLights;
	bool IncludeMeshes;

	// mesh ����
	bool IncludeVertexColors; 
	bool IncludeNormals;
	bool IncludeTargentBiNormal;
	bool IncludeTexCoords;
	int NumTexCoords;

	// modifier ����
	bool IncludeModifiers;
	bool IncludeSkins;

	// animation ����
	bool IncludeCurrentFrame;
	bool IncludeKeyFrames;
	bool IncludeAllFrames;
	bool UseLocalTime;
	int StartFrame;
	int EndFrame;

	// Ŀ¼
	char SrcRootDir[255];
	char DstRootDir[255];
};

#endif
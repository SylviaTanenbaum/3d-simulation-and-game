/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2EditLODTerrain.hpp
*
* �汾		:	1.0 (2011/03/05)
*
* ����		��	more
*
*/

#ifndef PX2EDITLODTERRAIN_HPP
#define PX2EDITLODTERRAIN_HPP

#include "PX2TerrainPrerequisites.hpp"
#include "PX2LODTerrain.hpp"

namespace PX2
{

	class PX2_TERRAIN_ENTRY EditLODTerrain : public LODTerrain
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(EditLODTerrain);

	public:
		EditLODTerrain ();
		virtual ~EditLODTerrain ();
		
		// �ڴ������������ͼ����
		void SetRenderer (Renderer* renderer);
		void SetRowQuantity (int rowQuantity);
		void SetColQuantity (int colQuantity);
		void SetSize (int size);
		void SetMinElevation (float minElvation);
		void SetMaxElevation (float maxElvation);
		void SetSpacing (float spacing);
		void SetUVBias (float uvBias);
		void SetBorderColor (Float4 borderColor);
		void AllocateRawTerrainPages ();

		void SetUScale (int unit, float uScale);
		void SetVScale (int unit, float vScale);
		float GetUScale (int unit);
		float GetVScale (int unit);

		void SetLayerBaseTexture (const std::string &name);
		std::string GetLayerBaseTexture ();
		void SetLayer1Texture (const std::string &name);
		std::string GetLayer1Texture ();
		void SetLayer2Texture (const std::string &name);
		std::string GetLayer2Texture ();
		void SetLayer3Texture (const std::string &name);
		std::string GetLayer3Texture ();
		void SetLayer4Texture (const std::string &name);
		std::string GetLayer4Texture ();

		LODRawTerrainPagePtr** &GetRawTerrainPages ();
		LODRawTerrainPagePtr *GetCurrentPage (float x, float y) const;

	};

	PX2_REGISTER_STREAM(EditLODTerrain);
	typedef Pointer0<EditLODTerrain> EditLODTerrainPtr;
#include "PX2EditLODTerrain.inl"

}

#endif
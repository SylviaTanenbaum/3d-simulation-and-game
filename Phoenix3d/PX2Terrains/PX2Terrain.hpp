/*
*
* �ļ�����	��	PX2Terrain.hpp
*
*/

#ifndef PX2TERRAIN_HPP
#define PX2TERRAIN_HPP

#include "PX2TerrainsPre.hpp"
#include "PX2Node.hpp"
#include "PX2Camera.hpp"
#include "PX2TerrainPage.hpp"

namespace PX2
{

	class Terrain : public Node
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(Terrain);

	public:
		virtual ~Terrain ();

		// members
		inline int GetRowQuantity () const;
		inline int GetColQuantity () const;
		inline int GetSize () const;
		inline float GetSpacing () const;
		float GetHeight (float x, float y) const;
		AVector GetNormal (float x, float y) const;

		TerrainPage* GetPage (int row, int col);
		TerrainPage* GetCurrentPage (float x, float y) const;
		bool GetPageIndex (int &outRow, int &outCol, TerrainPage *page);
		TerrainPagePtr ReplacePage (int row, int col, TerrainPage* newPage);

		virtual void UseSimpleMtl (bool use);
		bool IsUseSimpleMtl ();

		EditTerrainMaterial *GetEidtMaterial ();
		EditTerrainMaterial *GetSimpleMaterial ();
		Shine *GetShine ();

		// ��radius���������num��ֲ��
		void AddJunglers (Texture2D *tex, APoint center, float radius, int num, 
			float width, float height, float lower);
		void RemoveJunglers (Texture2D *tex, APoint center, float radius, int num);

		void SetJunglerFrequency (float fre);
		float GetJunglerFrequency ();
		void SetJunglerStrength (float strength);
		float GetJunglerStrength ();

	protected:
		Terrain(bool useSimpleMtl);

		int mNumRows, mNumCols;
		int mSize;
		float mMinElevation, mMaxElevation, mSpacing;
		TerrainPagePtr** mPages;

		bool mIsUseSimpleMtl;
		VertexFormatPtr mVFormatEdit;
		VertexFormatPtr mVFormatSimple;
		EditTerrainMaterialPtr mMtlEdit;
		EditTerrainMaterialPtr mMtlSimple;

		ShinePtr mShine;
		float mJunglerFrequency;
		float mJunglerStrength;

	private:
		Terrain();
	};

	PX2_REGISTER_STREAM(Terrain);
	typedef Pointer0<Terrain> TerrainPtr;
#include "PX2Terrain.inl"

}

#endif
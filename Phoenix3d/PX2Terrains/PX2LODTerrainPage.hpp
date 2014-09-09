/*
*
* �ļ�����	��	PX2LODTerrainPage.hpp
*
*/

#ifndef PX2LODTERRAINPAGE_HPP
#define PX2LODTERRAINPAGE_HPP

#include "PX2TerrainsPre.hpp"
#include "PX2TerrainPage.hpp"

namespace PX2
{

	class LODTerrainBlock;
	class LODTerrainVertex;

	class LODTerrainPage : public TerrainPage
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(LODTerrainPage);

	public:
		// size = 2^p + 1, p <= 7 (size = 3, 5, 9, 17, 33, 65, 129)
		LODTerrainPage (VertexFormat* vformat, int size, float* heights,
			const Float2& origin, float spacing);
		virtual ~LODTerrainPage ();

		void SetPixelTolerance (float tolerance);
		float GetPixelTolerance () const;

	protected:
		friend class LODTerrainBlock;

		void InitializeDerivedData ();

		// queue handlers
		void AddToQueue (unsigned short blockIndex);
		unsigned short RemoveFromQueue ();
		unsigned short ReadFromQueue (unsigned short index);

		bool IntersectFrustum (const Camera *camera);
		void SimplifyBlocks (const Camera* camera, const APoint &modelEye,
			const AVector &modelDir, bool closeAssumption);
		void SimplifyVertices (const APoint &modelEye,
			const AVector &modelDir, bool closeTerrainAssumption);

		// ���μ�
		friend class LODTerrain;
		void EnableBlocks ();
		void ResetBlocks ();
		void Simplify (const APoint &modelEye, const AVector &modelDir,
			bool closeAssumption);

		// ����
		float GetTextureCoordinate (int index) const;
		void Render (LODTerrainBlock &block);
		void RenderTriangle (int t, int l, int r);
		void RenderBlocks ();

		// �ɼ����ü�
		virtual void GetVisibleSet (Culler &culler, bool noCull);

		float mTextureSpacing;

		// ��
		float mPixelTolerance, mWorldTolerance;
		mutable bool mNeedsTessellation;
		int *mLookup;

		/// (2^p+1) * (2^p+1)�Ķ������飬��������
		LODTerrainVertex *mVertexs;
		VertexBufferAccessor mVBA;

		// maximum quantities
		int mTotalVQuantity, mTotalTQuantity, mTotalIQuantity;

		// quadtree of blocks
		int mBlockQuantity;
		LODTerrainBlock* mBlocks;

		// ��¼���Ӳ�Block��
		unsigned short *mQueue;
		unsigned short mNumQueue;
		unsigned short mFront, mBack;
		unsigned short mNumUnprocessed;
		unsigned short mItemsInQueue;

	public_internal:
		// �̻߳�ȡ����Ϊ z = h(x,y)��xyƽ��ʹ����������ϵ������ͼ��ʾ
		//
		// y
		// ^
		// | col 0   col 1
		// +--------+-------+
		// |   10   |  11   | row 1
		// +--------+-------+
		// |   00   |  01   | row 0
		// +--------+-------+--> x

		// ����ҳ(r,c)��(r,c+1)֮��ķ��
		void StitchNextCol (LODTerrainPage *nextCol);
		void UnstitchNextCol (LODTerrainPage *nextCol);

		// ����ҳ(r,c)��(r+1,c)֮��ķ��
		void StitchNextRow (LODTerrainPage *nextRow);
		void UnstitchNextRow (LODTerrainPage *nextRow);
	};

	PX2_REGISTER_STREAM(LODTerrainPage);
	typedef Pointer0<LODTerrainPage> LODTerrainPagePtr;
#include "PX2LODTerrainPage.inl"

}

#endif
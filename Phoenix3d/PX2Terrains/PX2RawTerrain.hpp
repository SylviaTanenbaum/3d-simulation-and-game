/*
*
* �ļ�����	��	PX2RawTerrain.hpp
*
*/

#ifndef PX2RAWTERRAIN_HPP
#define PX2RAWTERRAIN_HPP

#include "PX2Terrain.hpp"
#include "PX2RawTerrainPage.hpp"
#include "PX2EditTerrainMaterial.hpp"

namespace PX2
{
	
	class RawTerrain : public Terrain
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(RawTerrain);

	public:
		RawTerrain ();
		virtual ~RawTerrain ();

		// ��������ʱ�����õ�������
		/*
		* ��Щ�ӿڣ��ڱ༭���д�������ʹ��
		*/
		void SetRowQuantity (int numRows);
		void SetColQuantity (int numCols);
		void SetSize (int size);
		void SetSpacing (float spacing);
		void AllocateRawTerrainPages ();

		virtual void UseSimpleMtl (bool use);

	protected:
		void CreatePage (int row, int col);
	};

	PX2_REGISTER_STREAM(RawTerrain);
	typedef Pointer0<RawTerrain> RawTerrainPtr;

}

#endif
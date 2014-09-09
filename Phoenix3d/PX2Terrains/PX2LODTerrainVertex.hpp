/*
*
* �ļ�����	��	PX2LODTerrainVertex.hpp
*
*/

#ifndef PX2LODTERRAINVERTEX_HPP
#define PX2LODTERRAINVERTEX_HPP

#include "PX2TerrainsPre.hpp"
#include "PX2Assert.hpp"

namespace PX2
{

	/// LOD���ζ�����
	class LODTerrainVertex
	{
	public:
		LODTerrainVertex ();

		void SetDependent (int i, LODTerrainVertex *pkDependent);
		LODTerrainVertex *GetDependent (int i);
		bool IsEnabled () const;
		void Enable ();
		void Disable ();

	protected:
		LODTerrainVertex *mDependent[2];
		bool mEnabled; //< �ö����Ƿ������������
	};

#include "PX2LODTerrainVertex.inl"
}

#endif
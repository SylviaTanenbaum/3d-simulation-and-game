/*
*
* �ļ�����	��	PX2UniMaterialMesh.hpp
*
*/

#ifndef PX2UNIMATERIALMESH_HPP
#define PX2UNIMATERIALMESH_HPP

#include "PX2MaxToPX2PluginPre.hpp"

class UniMaterialMesh
{
public:
	UniMaterialMesh ();
	~UniMaterialMesh ();

	int &VQuantity ();
	PX2::Float3 *&VertexMap ();
	PX2::Float3 *&NormalMap ();
	int &CQuantity ();
	PX2::Float3 *&ColorMap ();
	int &TQuantity ();
	PX2::Float2 *&TextureCoordMap ();
	int &FQuantity ();
	int *&Face ();
	int *&CFace ();
	int *&TFace ();

	void SetShineProperty (PX2::Shine *shine);
	void SetMaterialInstance (PX2::MaterialInstance *mi);

	// һ��Max�������ӵ�ж��UVW���ꡣPhoenix2ֻ֧��һ��UV���꣨W�����Ե�����
	// ����Max����ӵ�е�N��UVW������뱻���Ƶ�N��Phoenix2�Ķ��������У�ÿ����
	// ��ֻӵ��һ��UV���ꡣ
	void DuplicateGeometry ();

	void SetExportTargentBinormal (bool exp);
	void SetNumTexcoordToExport (int num);
	void SetExportSkin (bool skin);
	PX2::TriMesh *ToTriMesh ();

	class VertexAttr
	{
	public:
		VertexAttr ();
		bool operator== (const VertexAttr &vFormat) const;
		bool operator< (const VertexAttr &vFormat) const;
		int V, C, T;
	};

private:

	// --
	int mVertexMapQuantity;
	PX2::Float3 *mVertexMap;
	PX2::Float3 *mNormalMap;

	int mColorMapQuantity;
	PX2::Float3 *mColorMap;

	int mTQuantity;
	PX2::Float2 *mTextureCoordMap;
	// --

	int mFQuantity;
	int *mVFace;	// ÿ��Ԫ�ش���һ�����ϣ�һ������Ķ�������
	int *mCFace;	// ÿ��Ԫ�ش���һ�����ϣ�һ���������ɫ����
	int *mTFace;	// ÿ��Ԫ�ش���һ�����ϣ�һ���������ͼ��������

	bool mExportTargentBinormal;
	int mNumTexcoordToExport;
	bool mExportSkin;

	PX2::ShinePtr mShine;
	PX2::MaterialInstancePtr mMaterialInstance;
};

#endif
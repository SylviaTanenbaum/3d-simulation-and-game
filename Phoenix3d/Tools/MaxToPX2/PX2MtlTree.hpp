/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2MtlTree.hpp
*
* �汾		:	1.0 (2011/05/22)
*
* ����		��	more
*
*/

#ifndef PX2MTLTREE_HPP
#define PX2MTLTREE_HPP

#include "PX2Shine.hpp"
#include "PX2MaterialInstance.hpp"

class MtlTree
{
public:
	MtlTree (PX2::Shine *shine=0);

	// ������
	void SetMChildQuantity (int quantity);
	int GetMChildQuantity () const;
	void SetShine (PX2::Shine *shine);
	PX2::Shine *GetShine ();
	MtlTree &GetMChild (int i);

	// ��ͼ��
	void SetMaterialInstance (PX2::MaterialInstance *mi);
	PX2::MaterialInstance *GetMaterialInstance ();

private:
	PX2::ShinePtr mShine;
	PX2::MaterialInstancePtr mMaterialInstance;
	std::vector<MtlTree> mMChild;
};

#endif
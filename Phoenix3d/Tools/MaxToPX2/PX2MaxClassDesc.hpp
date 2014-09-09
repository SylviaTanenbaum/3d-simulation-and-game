/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2MaxClassDesc.hpp
*
* �汾		:	1.0 (2011/04/18)
*
* ����		��	more
*
*/

#ifndef PX2MAX8CLASSDESC_HPP
#define PX2MAX8CLASSDESC_HPP

#include "PX2MaxToPX2PluginPre.hpp"

class PX2MaxClassDesc : public ClassDesc2
{
public:
	PX2MaxClassDesc ();

	virtual int IsPublic ();
	virtual void *Create (BOOL loading = FALSE);

	virtual const TCHAR* ClassName ();
	virtual SClass_ID SuperClassID ();
	virtual Class_ID ClassID ();
	virtual const TCHAR* Category ();
	virtual const TCHAR* InternalName ();
	virtual HINSTANCE HInstance();

	static HINSTANCE msInstance;

	static Class_ID ID;
	static PX2MaxClassDesc TheClassDesc;
};

#endif
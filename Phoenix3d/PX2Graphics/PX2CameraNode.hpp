/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2CameraNode.hpp
*
* �汾		:	1.0 (2011/04/07)
*
* ����		��	more
*
*/

#ifndef PX2CAMERANODE_HPP
#define PX2CAMERANODE_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Camera.hpp"
#include "PX2Node.hpp"

namespace PX2
{

	/// ����ڵ���
	/**
	* Node������任������Camera�Ŀռ䷽λ��Node��������ת��������Camera����
	* ���᷽������任�ĵ�0��������ķ���direction����������1�����������
	* ��up����������2����������ң�right��������
	*/
	class CameraNode : public Node
	{
	public:
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_PROPERTY;
		PX2_DECLARE_STREAM(CameraNode);

	public:
		/// ���캯��
		/**
		* �ڹ��캯���У�����ĵ�ǰ����ϵͳ����ΪNode�ı��ر任��
		* local translation		  = camera location
		* local rotation column 0 = camera direction
		* local rotation column 1 = camera up
		* local rotation column 2 = camera right
		*/
		CameraNode (Camera* camera = 0);
		virtual ~CameraNode ();

		/// �������
		/**
		* ����ĵ�ǰ����ϵͳ������ΪNode�ı��ر任��Node����任��
		* UpdateWorldData���¼��㣬���������ϵͳ������ΪNode����任��
		*/
		void SetCamera (Camera* camera);

		Camera* GetCamera ();
		const Camera* GetCamera () const;

		void EnableUpdate (bool enable);
		bool IsEnableUpdate ();

	protected:
		virtual void UpdateWorldData (double applicationTime);

		CameraPtr mCamera;
		bool mEnableUpdate;
	};

	PX2_REGISTER_STREAM(CameraNode);
	typedef Pointer0<CameraNode> CameraNodePtr;
#include "PX2CameraNode.inl"


}

#endif

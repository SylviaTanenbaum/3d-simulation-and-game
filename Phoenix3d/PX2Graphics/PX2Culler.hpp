/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Culler.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2CULLER_HPP
#define PX2CULLER_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Camera.hpp"
#include "PX2Movable.hpp"
#include "PX2VisibleSet.hpp"

namespace PX2
{
	
	/// �����ü�����
	class Culler
	{
	public:
		/**
		* �ü�����Ҫ������������cameraû�б����ݸ����캯��������Ҫ��
		* ComputeVisibleSet����֮ǰ����SetCamera��
		*/
		Culler (const Camera* camera = 0);
		virtual ~Culler ();

		// ����ͽ�ͷ������
		inline void SetCamera (const Camera* camera);
		inline const Camera* GetCamera () const;
		void SetFrustum (const float* frustum);
		inline const float* GetFrustum () const;
		inline VisibleSet& GetVisibleSet ();

		/// ����ɼ����󵽿ɼ��б�
		/**
		* �����������ش˺��������������ʵ��һ��ѡ�����飬ʵ����С����״̬�ı䣬
		* ����ʵ��һ������֧�����ϵͳ��
		*/
		virtual void Insert (Renderable* visible);

		// ����Բ�������ӽ�ͷ��֮��Ĳü��棬����ü���Ҫ��������������ϵ��
		enum { MAX_PLANE_QUANTITY = 32 };
		inline int GetPlaneQuantity () const;
		inline const HPlane* GetPlanes () const;
		inline void SetPlaneState (unsigned int planeState);
		inline unsigned int GetPlaneState () const;
		inline void PushPlane (const HPlane& plane);
		inline void PopPlane ();

		/// ������������Χ��Ͳü�����бȽϣ����ɼ��жϣ�ֻ��Movable���ô˺�����
		bool IsVisible (const Bound& bound);

		/// �ü������ĺ���
		/**
		* ������������ü�������������������������У�������������������Ǳ�ڿ�
		* ������
		*/
		void ComputeVisibleSet (Movable* scene);
		
		// ���㻷������
		void ComputeEnvironment ();

	protected:
		// �ü�����Ҫ�����
		const Camera* mCamera;

		/** 
		* ��������Ľ�ͷ��Ŀ��������������ʽϵͳ�ڲü���ʱ��ı��ͷ�壨����]
		* ��˵�������ϵͳ������Ӱ�쵽�����
		*/
		float mFrustum[Camera::VF_QUANTITY];

		/** 
		* ����ü��������ͷ����صģ�����Ҳ���������û��Զ���Ĳü��档��Ա
		* mPlaneState����bit�洢��Ϊ��־�ģ���ʾ�����ڲü�ϵͳ���Ƿ񼤻bitΪ
		* 1��ʾƽ��ʽ����ģ�����ƽ���ǲ�����ġ�һ�������ƽ������Χ����Ƚϣ�
		* ���м����ƽ�治�Ƚϡ���������֧�ָ�Ч�ĵȼ��ü���������˵�����һ��
		* Node�İ�Χ�����������ü��桱���ڲ�����ô�������ü��桱������Ϊ��
		* �����(inactive)����Ϊ������ڵ�����еĺ��Ӷ��ڡ���ü��桱�ڣ�����
		* Ҫ���롰��ü��桱�Ƚ��ˡ�
		*/
		int mPlaneQuantity;
		HPlane mPlane[MAX_PLANE_QUANTITY];
		unsigned int mPlaneState;

		/// �ɼ���
		VisibleSet mVisibleSet;
	};

#include "PX2Culler.inl"

}

#endif
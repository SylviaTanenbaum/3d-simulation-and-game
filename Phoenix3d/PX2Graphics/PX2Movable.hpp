/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Movable.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2SPATIAL_HPP
#define PX2SPATIAL_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Controlledable.hpp"
#include "PX2Bound.hpp"
#include "PX2Transform.hpp"

namespace PX2
{

	class Culler;
	
	/// �ռ伸������
	/**
	* ������Ҫ�ռ�����֧�ֵ����Ͷ��Ӵ���������ͬʱ֧�ֽ�ͷ��ü����ܡ��ռ�����
	* �������ռ�任����Χ�С�
	*/
	class Movable : public Controlledable
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_PROPERTY;
		PX2_DECLARE_STREAM(Movable);

	protected:
		Movable ();
	public:
		virtual ~Movable ();

		/// ���غ�����任
		/**
		* ��ĳЩ����£���Ҳ����Ҫֱ����������任�����World�������ˣ�
		* WorldIsCurrent��ʶҲ��ñ�����Ϊtrue��
		*/
		Transform LocalTransform;
		Transform WorldTransform;
		bool WorldTransformIsCurrent;

		/// �����Χ�з���
		/**
		* ��ĳЩ����£���Ҳ����Ҫֱ�����������Χ�С����WorldBound��ֱ������
		* ��WorldBoundIsCurrentӦ�ñ�����Ϊtrue��
		*/
		Bound WorldBound;
		bool WorldBoundIsCurrent;

		/// �ü�����
		enum CullingMode
		{
			/// ͨ���Ƚϰ�Χ�кͲü��棬��������Ŀɼ��ԡ�
			CULL_DYNAMIC,

			/// ǿ�����屻�ü��������һ��Node���ü��ˣ���Node�µ������ӽڵ�Ҳ
			/// ���ü���	
			CULL_ALWAYS,

			/// ��Զ���ü����塣���һ��Node�����ü�����Node�µ������ӽڵ�Ҳ��
			/// ���ü���
			CULL_NEVER
		};

		CullingMode Culling;

		void Show (bool show);
		bool IsShow () const;

		/// ���¼���״̬�Ϳ�����
		/**
		* �������¸��³����任�����ϸ��������Χ�С�
		*/
		void Update (double applicationTime = -Mathd::MAX_REAL,
			bool initiator = true);
		void SetUpdateOnce (bool once);
		bool IsUpdateOnce () const;

		/// ��ø���
		Movable* GetParent ();

		void SetParentTransformIngore (bool trans, bool rotate, bool scale);
		void GetParentTransformIngore (bool &trans, bool &rotate, bool &scale);

		// �ҽ�
		/*
		* ���ڵ㱻���ص�������ʱ�����ش˺�������ʵ���Լ���Ҫ�Ĳ�����ͨ������
		* ���ڵ��Attach��Detach�����������������Ĭ�Ϻ�����Ϊ�ա�
		*/
		virtual void OnAttach ();
		virtual void OnDetach (); 

		virtual void OnPicked (int pickInfo); // called during Picker::Execute
		virtual void OnNotPicked (int pickInfo);

		void SetDoPick (bool doPick);
		bool IsDoPick () const;

		void SetPickIngoreCullingMode (bool pickIngoreCullingMode);
		bool IsPickIngoreCullingMode () const;

		void SetNotPickedParentChildrenNotPicked (bool use);
		bool IsNotPickedParentChildrenNotPicked () const;

		// alpha
		void SetAlphaSelfCtrled (bool selfCtrled);
		bool IsAlphaSelfCtrled () const;
		virtual void SetAlpha (float alpha);
		float GetAlpha () const;

		// color
		void SetColorSelfCtrled (bool selfCtrled);
		bool IsColorSelfCtrled () const;
		virtual void SetColor (const Float3 &color);
		const Float3 &GetColor () const;

		// Update time
		void SetUpdateTime (float time);
		float GetUpdateTime () const;

		void SetUpdatePriority (int updatePriority);
		int GetUpdatePriority () const;

	protected:
		// ����״̬����
		virtual void UpdateWorldData (double applicationTime);
		virtual void UpdateWorldBound () = 0;
		void PropagateBoundToRoot ();

public_internal:
		// �����ü�
		void OnGetVisibleSet (Culler& culler, bool noCull);
		virtual void GetVisibleSet (Culler& culler, bool noCull) = 0;

		// ���ø��ڵ㣬�ڵ���attach/detach��ʱ����ô˺�����
		void SetParent (Movable* parent);

	protected:
		Movable* mParent;

	protected:
		bool mIsAlphaSelfCtrled;
		float mAlpha;
		bool mIsColorSelfCtrled;
		Float3 mColor;
		float mUpdateTime;
		float mUpdateTiming;
		float mUpdateTimingInit;

		int mUpdatePriority;

		bool mIsDoPick;
		bool mIsPickIngoreCullingMode;
		bool mIsNotPickedParentChildrenNotPicked;

		bool mIsIngoreParent_Translate;
		bool mIsIngoreParent_Rotate;
		bool mIsIngoreParent_Scale;
	};

	PX2_REGISTER_STREAM(Movable);
	typedef Pointer0<Movable> MovablePtr;
#include "PX2Movable.inl"

}

#endif
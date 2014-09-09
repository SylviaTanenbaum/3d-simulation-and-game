/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Node.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2NODE_HPP
#define PX2NODE_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Movable.hpp"
#include "PX2Culler.hpp"

namespace PX2
{

	
	/// �����ڵ���
	/**
	* ����ʵ�֡�����-���ӡ����ƣ�������֯�����Ĺ������Ӹ������������ͬ�����磺
	* BspNode��SwitchNode�ȣ�ʵ�ֲ�ͬ�ĳ�����֯��ʽ��
	*/
	class Node : public Movable
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_PROPERTY;
		PX2_DECLARE_STREAM(Node);

	public:
		Node ();
		virtual ~Node ();

		virtual void Play ();
		virtual bool IsPlaying () const;
		virtual void Stop ();
		virtual void Reset ();

		/// ��ú�������
		int GetNumChildren () const;
		int GetNumValidChildren () const;

		/// ��Ӻ��ӽڵ�
		/** 
		* ��������ɹ������غ����ں����б��е������š�
		* ����Щ����ĳ���ͼϵͳϵͳ�У�һ���ڵ�����ж�����ף������ĳ���ͼ��
		* һ�������޻�ͼ��DGA��������������£����׺��ӵĹ�ϵ�������Ĺ�ϵ�����
		* ����ҪΪ�ڵ��Ҹ��¡����ס�ʱ����Ҫ�Ƚ����ɵġ����ӹ�ϵ�����������
		* DetachChild���ڵ㣬Ȼ������һ�������ס�AttachChild�˽ڵ㡣
		*	������DetachChild��ʱ�򣬵��ĺ��ӽڵ�ġ�������self-destruct�������
		* �㲻����������������Ļ�����������ӹҵ�һ��smartָ���ϡ�
		*	������
		*	Node* pkNode0 = PX2_NEW Node;
		*	Movable* pkChild0 = <...>;
		*	pkNode0->AttachChild(pkChild0);  // child at index 0
		*	Node* pkNode1 = <...>;
		*
		*	// ��������һ��assert����ΪpkChild0�Ѿ���һ�����׽ڵ�pkNode0��
		*	pkNode1->AttachChild(pkChild0);
		*	
		*	// Ϊ�˷�ֹ��������self-destruct���������Ѻ��ӹҵ�һ��smartָ���ϡ�
		*	MovablePtr spkSaveChild = pkNode0->GetChild(0);
		*	pkNode0->DetachChild(spkSaveChild);
		*	pkNode1->AttachChild(spkSaveChild);
		*/
		virtual int AttachChild (Movable* child);

		/// �Ӹ��׽ڵ���ȥ��child
		/**
		* ���'child'�ǿգ�����child�ں��������е����������򷵻�-1��
		*/
		virtual int DetachChild (Movable* child);

		virtual bool DetachChildByName (const std::string &name);

		/// �Ӹ��׽ڵ���ȥ������Ϊi��child
		/**
		* ���0 <= i < GetNumChildren()������i�����ӵ�ָ�룬���򷵻�null��
		*/
		virtual MovablePtr DetachChildAt (int i);

		virtual void DetachAllChildren ();

		/// ��������Ϊi���ĺ��ӽڵ�
		/**
		* ���0 <= i < GetNumChildren()������֮ǰ��i���ĺ��ӽڵ�ָ�롣���i����
		* ��Χ�� ��������ӵ������б�ĩβ��������null��
		*/
		virtual MovablePtr SetChild (int i, Movable* child);

		/// �������Ϊi���ĺ��ӽڵ�
		/**
		* ���0 <= i < GetNumChildren()��������i�����ӵ�ָ�롣���������Χ����
		* ��null��
		*/
		virtual MovablePtr GetChild (int i);

		virtual MovablePtr GetChildByName (const std::string &name);

		virtual void SetAlpha (float alpha);
		virtual void SetColor (const Float3 &color);
		
		void SetDoPickPriority (bool doPickPriority); // һ������ΪNode����
		bool IsDoPickPriority () const;
		virtual void OnNotPicked (int pickInfo);

	protected:
		// ����ͼ�θ���
		virtual void UpdateWorldData (double applicationTime);
		virtual void UpdateWorldBound ();

		// �����̳вü�
		virtual void GetVisibleSet (Culler& culler, bool noCull);

		// �����б�
		std::vector<MovablePtr> mChild;
		
		std::vector<Movable*> mUpdateChild;
		bool mIsNeedCalUpdateChild;

		bool mIsDoPickPriority;
	};

	PX2_REGISTER_STREAM(Node);
	typedef Pointer0<Node> NodePtr;
#include "PX2Node.inl"

}

#endif

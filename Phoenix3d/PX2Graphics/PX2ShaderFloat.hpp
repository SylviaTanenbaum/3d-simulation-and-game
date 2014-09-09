/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2ShaderFloat.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2SHADERFLOAT_HPP
#define PX2SHADERFLOAT_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Object.hpp"

namespace PX2
{

	class Camera;
	class Renderable;
	
	/// ��ɫ�������Ĵ�����
	/**
	* ������1���Ĵ�����ÿ����������4������ֵ��
	*/
	class ShaderFloat : public Object
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(ShaderFloat);

	public:
		ShaderFloat ();
		/// ��ȱʡ���캯��
		/**
		* ����ļĴ�����������Ǹ���ÿһ���Ĵ�������4��floating-pointֵ��
		*/
		ShaderFloat (int numRegisters);
		virtual ~ShaderFloat ();

		// �����������Ĵ�������
		void SetNumRegisters (int numRegisters);

		// ��Ա����
		inline int GetNumRegisters () const;
		inline const float* GetData () const;
		inline float* GetData ();

		//���üĴ���ֵ
		/*
		* SetRegister��data����4��float��register i��
		* SetRegisters��data����mNumElements��float��register��
		* Get*�����෴��
		*/
		void SetRegister (int i, const float* data);
		void SetRegisters (const float* data);
		void GetRegister (int i, float* data);
		void GetRegisters (float* data);

		/// ���üĴ���ֵ
		/**
		* ��SetRegisters����˼��һ���ġ���һ���Ĵ����ṹ�����˵�'const float*'
		* ����ʽת���������ֵ�����ͷǳ������ˡ�
		*/
		ShaderFloat& operator= (const float* data);

		// ͨ��������������
		inline float operator[] (int i) const;
		inline float& operator[] (int i);

		// �������������ɫ�������Ķ�̬���¡������ڸ�������������ɫ������Ҳ
		// ��Ҫ�ı䡣
		inline void EnableUpdater ();
		inline void DisableUpdater ();
		inline bool AllowUpdater () const;
		virtual void Update (const Renderable* renderable, const Camera* camera);

		virtual void Float_OnRegistProperties (Object *parObj);
		virtual void Float_OnPropertyChanged (Object *parObj, const PropertyObject &obj);

	protected:
		int mNumElements;
		float* mData;
		bool mAllowUpdater;
	};

	PX2_REGISTER_STREAM(ShaderFloat);
	typedef Pointer0<ShaderFloat> ShaderFloatPtr;
#include "PX2ShaderFloat.inl"

}

#endif

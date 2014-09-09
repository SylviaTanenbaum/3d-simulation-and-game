/*
*
* �ļ�����	��	PX2KeyframeController.hpp
*
*/

#ifndef PX2KEYFRAMECONTROLLER_HPP
#define PX2KEYFRAMECONTROLLER_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2TransformController.hpp"
#include "PX2HMatrix.hpp"
#include "PX2HQuaternion.hpp"

namespace PX2
{

	class KeyframeController : public TransformController
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(KeyframeController);

	public:
		/**
		* ���translations��rotations����scales������ͬ�Ĺؼ�֡ʱ�䣬����
		* numCommonTimesΪ�Ǹ�������ؼ�֡ʱ�䲻����������numCommonTimesΪ0��
		* �������Ĳ������õ����ʵ�ֵ�������ڸ����ͱ任Ϊ����������Ϊ0��
		*/
		KeyframeController (int numCommonTimes, int numTranslations,
			int numRotations, int numScales, const Transform& localTransform);

		virtual ~KeyframeController ();

		// ��Ա����
		inline int GetNumCommonTimes () const;
		inline float* GetCommonTimes () const;

		inline int GetNumTranslations () const;
		inline float* GetTranslationTimes () const;
		inline APoint* GetTranslations () const;

		inline int GetNumRotations () const;
		inline float* GetRotationTimes () const;
		inline HQuaternion* GetRotations () const;

		inline int GetNumScales () const;
		inline float* GetScaleTimes () const;
		inline float* GetScales () const;

		// ��������
		/*
		* ʱ��Ϊ����
		*/
		virtual bool Update (double applicationTime);

	protected:
		// ���ݸ�����ʱ����㵱ǰ��֡
		static void GetKeyInfo (float ctrlTime, int numTimes, float* times,
			int& lastIndex, float& normTime, int& i0, int& i1);

		APoint GetTranslate (float normTime, int i0, int i1);
		HMatrix GetRotate (float normTime, int i0, int i1);
		float GetScale (float normTime, int i0, int i1);

		// ��translations��rotations��scales����ʱ��ʱ����ʹ��������顣
		int mNumCommonTimes;
		float* mCommonTimes;

		int mNumTranslations;
		float* mTranslationTimes;
		APoint* mTranslations;

		int mNumRotations;
		float* mRotationTimes;
		HQuaternion* mRotations;

		int mNumScales;
		float* mScaleTimes;
		float* mScales;

		// ��¼�������������в�ֵ��
		int mTLastIndex, mRLastIndex, mSLastIndex, mCLastIndex;
	};

	PX2_REGISTER_STREAM(KeyframeController);
	typedef Pointer0<KeyframeController> KeyframeControllerPtr;
#include "PX2KeyframeController.inl"

}

#endif
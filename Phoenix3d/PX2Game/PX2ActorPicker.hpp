/*
*
* �ļ�����	��	PX2ActorPicker.hpp
*
*/

#ifndef PX2ACTORPICKER_HPP
#define PX2ACTORPICKER_HPP

#include "PX2GamePre.hpp"
#include "PX2ActorPickRecord.hpp"

namespace PX2
{

	class Scene;

	/// ��ɫѡ������
	/** 
	* �ߵı�����ʽΪP + t*D��P����ԭ�㣬D�ǵ�λ���ȵķ���������t�Ƿ����ϵ�
	* ���Ų�����������[tmin,tmax]�ڣ�tmin < tmax��P��D��������������ϵ���ֵ��
	* ��ͬ���Ͳ���ѡ�񣬾����ߵ����͡�
	* ֱ��line:		tmin = -Mathf::MAX_REAL, tmax = Mathf::MAX_REAL
	* ����ray��		tmin = 0, tmax = Mathf::MAX_REAL
	* �߶�segment��	tmin = 0, tmax > 0
	*/
	class ActorPicker
	{
	public:
		ActorPicker ();

		/// ִ�м�⣬����¼���浽Records�С�
		/**
		* ���ô˺����Զ���ռ�¼���顣�����ǰ��¼���������Ϣ��������ȱ��档
		*/
		void Execute (Scene* scene, const APoint& origin, 
			const AVector& direction, float tmin, float tmax);

		/// ���ؾ���ֵT��ӽ�0�Ľ�ɫ��¼
		/**
		* ���RecordsΪ�գ�������Чֵ��
		*/
		const ActorPickRecord &GetClosestToZero () const;

		std::vector<ActorPickRecord> Records;

	private:
		APoint mOrigin;
		AVector mDirection;
		float mTMin, mTMax;

		// ��Recordsû��Ԫ��ʱ�������ʾ��Ч�ĳ�Ա�ᱻGet*�������ء�
		static const ActorPickRecord msInvalid;
	};

}

#endif
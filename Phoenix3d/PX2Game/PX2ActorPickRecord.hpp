/*
*
* �ļ�����	��	PX2ActorPickRecord.hpp
*
*/

#ifndef PX2ACTORPICKRECORD_HPP
#define PX2ACTORPICKRECORD_HPP

#include "PX2GamePre.hpp"
#include "PX2Actor.hpp"

namespace PX2
{

	class ActorPickRecord
	{
	public:
		ActorPickRecord ()
		{
			T = 0.0f;
		}

		~ActorPickRecord ()
		{
		}

		ActorPtr Intersected;

		// ����P + t*D�е�����Ԫ������T������t�ı�ʾ��
		float T;
	};

}

#endif
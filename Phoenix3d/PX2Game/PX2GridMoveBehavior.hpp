/*
*
* �ļ�����	��	PX2GridMoveBehavior.hpp
*
*/

#ifndef PX2GRIDMOVEBEHAVIOR_HPP
#define PX2GRIDMOVEBEHAVIOR_HPP

#include "PX2GamePre.hpp"
#include "PX2AVector.hpp"
#include "PX2APoint.hpp"

namespace GridMove
{
	class MoveUnit;
	class MoveManager;
}

namespace PX2
{

	class Actor;
	class PathFinder;

	class GridMoveBehavior
	{
	public:
		GridMoveBehavior(Actor *actor);
		~GridMoveBehavior();

		void Clear ();

		GridMove::MoveUnit *GetMoveUnit();

		void SetSpeed (float speed);
		bool StandOnMask();

		// ���targetActor!=0, ��targetActor��ΪĿ�꣬
		// �����targetPos��ΪĿ�꣬ ���targetPosҲΪ0�� ֹͣ
		void SetTarget(Actor *targetActor, const APoint *targetPos);

		//���û��·���� ����false
		bool Update(float elapsedSeconds, APoint &pos, AVector &direction);

	private:
		Actor *mActor;
		Actor *mTargetActor;
		GridMove::MoveUnit *mUnit;
		float mStopAccumTime;
	};

#include "PX2GridMoveBehavior.inl"

}

#endif
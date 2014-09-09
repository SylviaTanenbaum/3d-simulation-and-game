
#ifndef __MOVEUNIT_H__
#define __MOVEUNIT_H__

#include "../RVO/Vector2.h"
#include "GridMovePre.h"
#include "GridMap.h"

#ifdef USE_RVO
namespace RVO
{
	class RVOSimulator;
}
#endif

namespace GridMove
{

	class MoveManager;

	class MoveUnit
	{
		enum
		{
			STATE_STOP = 0,
			STATE_MOVE
		};

		friend class MoveManager;
	public:

		// ʹ��ROVʱ��Ч
		void SetCollisionRadius(float radius);

		void SetMaskRadius(float radius);

		void ClearObstacle();
		bool IsStop()
		{
			return mState == STATE_STOP;
		}

		void LeaveMap();
		void SetPosition(float x, float y);
		void SetSpeed(float speed);
		void SetTarget(float x, float y); //�����Ŀ���ֱ����
		void SetTarget(MoveUnit *target, int range);
		void Stop();
		bool IsOnObstacle();

		void Update(float dtime);

		void GetPosition(float &x, float &y);
		void GetDirection(float &x, float &y);

	private:
		MoveUnit();
		~MoveUnit();
		void SetObstacle(const RVO::Vector2 &pos);
		void GoPath(const RVO::Vector2 &finalgoal);
		void CheckNewPath();
		bool GetNearGoal(RVO::Vector2 &goal); //·��̫����Ѱ·̫�ģ��������̣� �����Ƿ�������

	private:
#ifdef USE_RVO
		RVO::RVOSimulator *mSimulator;
		size_t mAgent;
#endif

		float mSpeed;
		float mAccumMoveLen;

		int mState;
		RVO::Vector2 mTargetPos;

		CNaviPath mNaviPath;
		int mCurPathPoint;
		int mMoveSegLen;

		RVO::Vector2 mCurPos;
		RVO::Vector2 mCurDir;

		float mMaskRadius;
		RVO::Vector2 mMaskStopPoint;
		bool mMaskStop;
	};

}

#endif
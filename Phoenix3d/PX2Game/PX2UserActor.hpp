/*
*
* �ļ�����	��	PX2Player.hpp
*
*/

#ifndef PX2PLAYER_HPP
#define PX2PLAYER_HPP

#include "PX2GamePre.hpp"

namespace PX2
{

	class User;

	class UserActor
	{
	public:
		UserActor ();
		virtual ~UserActor ();

		virtual void Update (float appTime, float elapsedTime);

		User *GetUser ();

		void SetName (const std::string &name);
		const std::string &GetName () const;

		void SetServerID (int id);
		int GetServerID () const;

		virtual void SetNickName (const std::string &name);
		const std::string &GetNickName () const;

		virtual void SetLevel (int level);
		int GetLevel () const;
		virtual void SetMaxLevel (int maxLevel);
		int GetMaxLevel () const;

		virtual void SetCurLevelExp (int exp); 
		int GetCurLevelExp () const;
		virtual void SetCurLevelMaxExp (int maxExp);
		int GetCurLevelMaxExp () const;

		virtual void SetCurLevelEnergy (int energy); 
		int GetCurLevelEnergy () const;
		virtual void SetCurLevelMaxEnergy (int maxEnergy);
		int GetCurLevelMaxEnergy () const;

		void SetGold (int gold);
		int GetGold () const;

		void SetMoney (int money);
		int GetMoney () const;

public_internal:
		void SetUser (User *user);

	protected:
		User *mUser;
		int mServerID;
		std::string mName;
		std::string mNickName;
		int mLevel;
		int mMaxLevel;
		int mCurLevelExp;  // ��ǰ�ȼ���ɫ���о���
		int mCurLevelMaxExp; // ��ǰ�ȼ���������
		int mCurLevelEnergy; // ��ǰ�ȼ���������ֵ
		int mCurLevelMaxEnergy; // ��ǰ�ȼ�����ֵ����
		int mGold;
		int mMoney;
	};

#include "PX2UserActor.inl"
	typedef Pointer0<UserActor> UserActorPtr;

}

#endif
/*
*
* �ļ�����	��	PX2Skill.hpp
*
*/

#ifndef PX2SKILL_HPP
#define PX2SKILL_HPP

#include "PX2GamePre.hpp"
#include "PX2Gameable.hpp"
#include "PX2SkillInstance.hpp"
#include "PX2SkillStep.hpp"
#include "PX2PropModify.hpp"

namespace PX2
{
	
	class Character;

	class Skill : public Gameable
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_PROPERTY;
		PX2_DECLARE_STREAM(Skill);

	public:
		Skill ();
		virtual ~Skill ();

		// Save
	public:
		virtual void SaveToXMLNode (XMLNode nodeParent);
		virtual void LoadFromXMLNode (XMLNode node);

		// Character
	public:
		Character *GetCharacter ();
		virtual void OnAdded ();
		virtual void OnRemove ();

public_internal:
		void SetCharacter (Character *character);

	protected:
		Character *mCharacter;
		
		// General
	public:
		virtual void Initlize ();
		virtual void Update (double appSeconds, double elapsedSeconds);

		// ���� ids
	public:
		void SetID (int id);
		int GetID () const;

		virtual void SetTypeID (int typeID);
		int GetTypeID () const;

		void SetTypeString (const std::string &typeString);
		const std::string &GetTypeString () const;

	protected:
		int mID;
		int mTypeID;
		std::string mTypeString;

		// def
	public:
		void SetDefPointer (void *pointer);
		void *GetDefPointer ();

	protected:
		void *mDefPointer;

		// ����
	public:
		void SetActivateProbability (float prob);
		float GetActivateProbability () const;

		// ���ȼ�
		void SetPriority (int priority);
		int GetPriority () const;

		// CDʱ��
		PX2_DECLARE_PM_F(CDTime);

	public:
		// ����/����
		void SetPositive (bool passive);
		bool IsPositive () const;

		void SetDieActivate (bool dieAct);
		bool IsDieActivate () const;

		// Ⱥ��/����
		void SetBeRangeAffect (bool rangeAffect);
		bool IsRangeAffect () const;
		void SetNumTargetsLock (int num); // ����Ŀ�����������Ϊ-1 ������
		int GetNumTargetsLock () const;

		// ������Χ
		PX2_DECLARE_PM_F(TrigerDistance);

		// ������Χ
	public:
		enum RangeType
		{
			RT_NEAR,
			RT_FAR,
			RT_MAX_TYPE
		};
		void SetRangeType (RangeType type);
		RangeType GetRangeType () const;

		enum ShapeType
		{
			ST_SPHERE,
			ST_FAN,
			ST_BOX,
			ST_MAX_TYPE
		};
		void SetShapeType (ShapeType type);
		ShapeType GetShapeType () const;

		PX2_DECLARE_PM_F(RadiusLength); // �뾶���߳���
		PX2_DECLARE_PM_F(Width);
		PX2_DECLARE_PM_F(FanDegree);

	public:
		//  ����
		void SetHasTrack (bool hasTrack);
		bool IsHasTrack () const;

		// ����
		void SetAbleToBuilding (bool ableToBuilding);
		bool IsAbleToBuilding () const;

		// �Ƿ��ж������Instance, Ĭ��Ϊ1
		void SetNumMultiInstance (int numMulti);
		int GetNumMultiInstance () const;

		// �ȼ�
		void SetLevel (int level);
		int GetLevel () const;
		void SetMaxLevel (int level);
		int GetMaxLevel () const;

		// �ű�
		void SetScriptHandler_OnAdded (const std::string &handler);
		const std::string &GetScriptHandler_OnAdded () const;
		void SetScriptHandler_OnRemove (const std::string &handler);
		const std::string &GetScriptHandler_OnRemove () const;

	protected:
		float mActivateProbability;
		int mPriority;
		bool mIsPositive;
		bool mIsDieActivate;
		
		RangeType mRangeType;
		bool mIsHasTrack;
		bool mIsAbleToBuilding;
		ShapeType mShapeType;

		bool mIsRangeAffect;
		int mNumTargetsLock;
		
		int mNumMultiInstance;

		int mLevel;
		int mMaxLevel;

		std::string mScriptHandler_OnAdded;
		std::string mScriptHandler_OnRemove;

		// ����
	public:
		void SetActivateNeedCharacterAimTarget (bool need);
		bool IsActivateNeedCharacterAnimTarget () const;

		void SetActivateAllowTimes (int times);
		int GetActivateAllowTimes () const;
		void SetActivatedTimes (int times);
		int GetActivatedTimes () const;
		bool IsActivateHasTimes () const;

		std::bitset<PX2_ACTOR_BS_SIZE> GetSkillQueryBitSet ();
		bool IsCallOver () const;
		virtual bool Activate ();
		virtual void DisActivate ();
		bool IsActivatting () const;
		void ResetCD ();
		void SetOnCD (bool cd);
		bool IsOnCD() const;
		void SetOnCDTime (float onCDTime);
		float GetOnCDTime () const;
		
		int GetNumInstances () const;
		void ClearSkillInstance ();

	protected:
		bool mIsActivateNeedCharacterAnimTarget;
		int mActivateAllowTimes;
		int mActivatedTimes;
		bool mIsOnCD;
		float mOnCDTime;
		bool mIsActivatting;
		std::vector<SkillInstancePtr> mSkillInstances;

		// ����
	public:
		bool SetFirstSkillStep (SkillStep *step);
		SkillStep *GetFirstSkillStep ();
		SkillStep *GetSkillStepByName (const std::string &name);
		SkillStep *GetLastSkillStep ();

	protected:
		SkillStepPtr mFirstSkillStep;

		// �˺�
	public:
		enum AffectGroupType
		{
			AGT_ENEMY,
			AGT_SELF,
			AGT_BOTH,
			AGT_MAX_TYPE
		};
		void SetAffectGroupType (AffectGroupType type);
		AffectGroupType GetAffectGroupType () const;

		void SetPhysicsAP (int val);
		int GetPhysicsAP () const;
		void SetMagicAP (int val);
		int GetMagicAP () const;
		void SetCriticalPercent (float percent);
		float GetCriticalPercent () const;
		void SetCriticalProbability (float prob);
		float GetCriticalProbability () const;
		int GetPhysicsAPLast () const;
		int GetMagicAPLast () const;

		// "JianSu"
		// "DingShen"
		// "ZhuoShao"
		// "JiYun"
		// "BaoJi"
		void AddAffectParam (const std::string &name, float val);
		void RemoveAffectParam (const std::string &name);
		bool IsHasAffectParam (const std::string &name);
		float GetAffectParam (const std::string &name);

	protected:
		AffectGroupType mAffectGroupType;
		int mPhysicsAP;
		int mMagicAP;
		float mCriticalPercent;
		float mCriticalProbability;
		std::map<std::string, float> mAffectParams;

		// Query Range
	public:
		bool IsInRadiusLength (const Character *target);
		bool IsInTrigerDistance (const Character *target);

		static bool IsInRange(const APoint &fromPos, float fromLength,
			float fromWidth, const AVector &fromFaceDir, float fromDegree, 
			const APoint &targetPos, float targetRadius, ShapeType type, bool doBoxRolate);

		static bool IsInBoxRange (const APoint &center, const AVector &dir,
			float length, float width, const APoint &point, float targetRadius);

		static bool IsInFanRange (const APoint &center, const AVector &dir,
			float radian, const APoint &point);
	};

#include "PX2Skill.inl"
	PX2_REGISTER_STREAM(Skill);
	typedef Pointer0<Skill> SkillPtr;

}

#endif
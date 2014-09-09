/*
*
* �ļ�����	��	PX2SkillStepTrack.hpp
*
*/

#ifndef PX2SKILLSTEPFARTRACK_HPP
#define PX2SKILLSTEPFARTRACK_HPP

#include "PX2SkillStep.hpp"

namespace PX2
{

	class SkillInstance;

	class SkillStepFarTrack : public SkillStep
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_PROPERTY;
		PX2_DECLARE_STREAM(SkillStepFarTrack);

	public:
		SkillStepFarTrack ();
		~SkillStepFarTrack ();

		void SetRangeRadius (float rangeRadius);
		float GetRangeRadius () const;

		void SetBeTrackToActor (bool isToActor);
		bool IsTrackToActor () const;

		void SetTrackDir (const AVector &dir);
		const AVector &GetTrackDir () const;

		void SetSpeed (float speed);
		float GetSpeed () const;

		// ֻ����IsTrackToActorΪfalseʱ��ʱ�����Ч��
		void SetTrackTime (float seconds);
		float GetTrackTime () const;

		void SetDegree (float degree);
		float GetDegree () const;

		void SetSideDegree (float degree);
		float GetSideDegree () const;

		void SetAlignTrace (bool alignTrace);
		bool IsAlignTrace () const;

		void SetDoDamageOnTrack (bool doDamgeOnTrack);
		bool IsDoDamageOnTrack () const;

		void SetDamageOnTrackFrequency (float fre);
		float GetDamageOnTrackFrequency () const;

		void SetCurTrackSkillInstance (SkillInstance *si);
		SkillInstance *GetCurTrackSkillInstance ();
		void SetScriptHandler_OnTrack (const std::string &handler);
		const std::string &GetScriptHandler_OnTrack () const;

		virtual void OnEnter (SkillInstance *instance);

public_internal:
		virtual void SaveToXMLNode (XMLNode nodeParent);
		virtual void LoadFromXMLNode (XMLNode node);

	protected:
		bool mIsTrackToActor;
		AVector mTrackDir;
		float mRangeRadius;
		float mSpeed;
		float mTrackTime;
		float mDegree;
		float mSideDegree;
		bool mIsAlignTrace;
		bool mIsDoDamageOnTrack;
		float mDamageOnTrackFrequency;
		std::string mScriptHandler_OnTrack;
		SkillInstance *mCurTrackSkillInstance;
	};

#include "PX2SkillStepFarTrack.inl"
	PX2_REGISTER_STREAM(SkillStepFarTrack);
	typedef Pointer0<SkillStepFarTrack> SkillStepFarTrackPtr;

}

#endif
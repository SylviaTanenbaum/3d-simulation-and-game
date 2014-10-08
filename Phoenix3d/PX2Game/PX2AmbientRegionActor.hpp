/*
*
* ÎÄ¼þÃû³Æ	£º	PX2AmbientRegionActor.hpp
*
*/

#ifndef PX2AMBIENTACTOR_HPP
#define PX2AMBIENTACTOR_HPP

#include "PX2TriggerActor.hpp"
#include "PX2Light.hpp"

namespace PX2
{

	class AmbientRegionActor : public TriggerActor
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_PROPERTY;
		PX2_DECLARE_STREAM(AmbientRegionActor);

	public:
		AmbientRegionActor ();
		virtual ~AmbientRegionActor ();

		void SetGISkyLightColor (const Float3 &color);
		const Float3 &GetGISkyLightColor () const;
		
		void SetAmbientColor (const Float3 &color);
		const Float3 &GetAmbientColor () const;

		void SetLightDiffColor (const Float3 &color);
		const Float3 &GetLightDiffColor () const;
		
		void SetLightSpecColor (const Float3 &color);
		const Float3 &GetLightSpecColor () const;	

		void SetAmbientScale (float scale);
		void SetDiffuseScale (float scale);
		void SetSpecularScale (float scale);
		float GetAmbientScale () const;
		float GetDiffuseScale () const;
		float GetSpecularScale () const;
		
		void SetLightIntensity (float intensity);
		float GetLightIntensity () const;

		void SetBakeShadowAngle (float shadowAnge);
		float GetBakeShadowAngle () const;
		
		void SetHorAngle (float angle);
		float GetHorAngle () const;
		
		void SetVerAngle (float angle);
		float GetVerAngle () const;
		
		const Light *GetLight () const;
		Light *GetLight ();

		virtual void CalLights ();

		virtual void DoEnter ();
		virtual void DoExecute (Event *event);
		virtual void DoLeave ();

public_internal:
		virtual void SetScene (Scene *scene);

	protected:
		Float3 mAmbientColor;
		Float3 mDirLightDiffColor;
		Float3 mLightSpecColor;
		float mLightIntensity;
		float mHorAngle; // (0-360)
		float mVerAngle; // (0-90)

		LightPtr mLight;

		float mBakeShadowAngle;
		Float2 mFogParam;
		Float3 mFogColor;
		Float3 mBakeSkyLightColor;

		float mAmbientScale;
		float mDiffuseScale;
		float mSpecularScale;

		Float2 mShineParam;
	};

	PX2_REGISTER_STREAM(AmbientRegionActor);
	typedef Pointer0<AmbientRegionActor> AmbientRigionActorPtr;
#include "PX2AmbientRegionActor.inl"

}

#endif
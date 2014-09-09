/*
*
* �ļ�����	��	PX2Culler.cpp
*
*/

#include "PX2Culler.hpp"
#include "PX2Renderable.hpp"
#include "PX2Light.hpp"
#include "PX2GraphicsRoot.hpp"
#include "PX2StandardESMaterial_Default.hpp"
#include "PX2StandardESMaterial_AlphaTest.hpp"
#include "PX2LightAmbientConstant.hpp"
#include "PX2LightDiffuseConstant.hpp"
#include "PX2LightSpecularConstant.hpp"
#include "PX2LightAttenuationConstant.hpp"
#include "PX2LightModelDVectorConstant.hpp"
#include "PX2JunglerMaterial.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
Culler::Culler (const Camera* camera)
:
mCamera(camera),
mPlaneQuantity(6)
{
}
//----------------------------------------------------------------------------
Culler::~Culler ()
{
}
//----------------------------------------------------------------------------
void Culler::SetFrustum (const float* frustum)
{
	if (!mCamera)
	{
		assertion(false, "SetFrustum requires the existence of a camera\n");
		return;
	}

	// ������ͷ���ֵ
	mFrustum[Camera::VF_DMIN] = frustum[Camera::VF_DMIN];
	mFrustum[Camera::VF_DMAX] = frustum[Camera::VF_DMAX];
	mFrustum[Camera::VF_UMIN] = frustum[Camera::VF_UMIN];
	mFrustum[Camera::VF_UMAX] = frustum[Camera::VF_UMAX];
	mFrustum[Camera::VF_RMIN] = frustum[Camera::VF_RMIN];
	mFrustum[Camera::VF_RMAX] = frustum[Camera::VF_RMAX];

	float dMin2 = mFrustum[Camera::VF_DMIN]*mFrustum[Camera::VF_DMIN];
	float uMin2 = mFrustum[Camera::VF_UMIN]*mFrustum[Camera::VF_UMIN];
	float uMax2 = mFrustum[Camera::VF_UMAX]*mFrustum[Camera::VF_UMAX];
	float rMin2 = mFrustum[Camera::VF_RMIN]*mFrustum[Camera::VF_RMIN];
	float rMax2 = mFrustum[Camera::VF_RMAX]*mFrustum[Camera::VF_RMAX];

	// ��������coordinate frame.
	APoint position = mCamera->GetPosition();
	AVector dVector = mCamera->GetDVector();
	AVector uVector = mCamera->GetUVector();
	AVector rVector = mCamera->GetRVector();
	float dirDotEye = position.Dot(dVector);

	// ���½��ü���
	mPlane[Camera::VF_DMIN].SetNormal(dVector);
	mPlane[Camera::VF_DMIN].SetConstant(
		dirDotEye + mFrustum[Camera::VF_DMIN]);

	// ����Զ�ü���
	mPlane[Camera::VF_DMAX].SetNormal(-dVector);
	mPlane[Camera::VF_DMAX].SetConstant(
		-(dirDotEye + mFrustum[Camera::VF_DMAX]));

	// ���µײü���
	float invLength = Mathf::InvSqrt(dMin2 + uMin2);
	float c0 = -mFrustum[Camera::VF_UMIN]*invLength;  // D component
	float c1 = +mFrustum[Camera::VF_DMIN]*invLength;  // U component
	AVector normal = c0*dVector + c1*uVector;
	float constant = position.Dot(normal);
	mPlane[Camera::VF_UMIN].SetNormal(normal);
	mPlane[Camera::VF_UMIN].SetConstant(constant);

	// ���¶��ü���
	invLength = Mathf::InvSqrt(dMin2 + uMax2);
	c0 = +mFrustum[Camera::VF_UMAX]*invLength;  // D component
	c1 = -mFrustum[Camera::VF_DMIN]*invLength;  // U component
	normal = c0*dVector + c1*uVector;
	constant = position.Dot(normal);
	mPlane[Camera::VF_UMAX].SetNormal(normal);
	mPlane[Camera::VF_UMAX].SetConstant(constant);

	// ������ü���
	invLength = Mathf::InvSqrt(dMin2 + rMin2);
	c0 = -mFrustum[Camera::VF_RMIN]*invLength;  // D component
	c1 = +mFrustum[Camera::VF_DMIN]*invLength;  // R component
	normal = c0*dVector + c1*rVector;
	constant = position.Dot(normal);
	mPlane[Camera::VF_RMIN].SetNormal(normal);
	mPlane[Camera::VF_RMIN].SetConstant(constant);

	// �����Ҳü���
	invLength = Mathf::InvSqrt(dMin2 + rMax2);
	c0 = +mFrustum[Camera::VF_RMAX]*invLength;  // D component
	c1 = -mFrustum[Camera::VF_DMIN]*invLength;  // R component
	normal = c0*dVector + c1*rVector;
	constant = position.Dot(normal);
	mPlane[Camera::VF_RMAX].SetNormal(normal);
	mPlane[Camera::VF_RMAX].SetConstant(constant);

	// ���вü��涼������
	mPlaneState = 0xFFFFFFFF;
}
//----------------------------------------------------------------------------
void Culler::Insert (Renderable* visible)
{
	mVisibleSet.Insert(visible);
}
//----------------------------------------------------------------------------
bool Culler::IsVisible (const Bound& bound)
{
	if (bound.GetRadius() == 0.0f)
	{
		return false;
	}

	// �����һ��ƽ�濪ʼ�Ƚ�
	int index = mPlaneQuantity - 1;
	unsigned int mask = (1 << index);

	for (int i = 0; i < mPlaneQuantity; ++i, --index, mask >>= 1)
	{
		if (mPlaneState & mask)
		{
			int side = bound.WhichSide(mPlane[index]);

			if (side < 0)
			{
				// �����ڲü��ķ��棬����ü���
				return false;
			}

			if (side > 0)
			{
				// �����ڲü������棬û�б�Ҫ�����Ƚ��Ӷ���
				mPlaneState &= ~mask;
			}
		}
	}

	return true;
}
//----------------------------------------------------------------------------
void Culler::ComputeVisibleSet (Movable* scene)
{
	if (mCamera && scene)
	{
		SetFrustum(mCamera->GetFrustum());
		mVisibleSet.Clear();
		scene->OnGetVisibleSet(*this, false);
	}
	else
	{
		assertion(false, "A camera and a scene are required for culling\n");
	}
}
//----------------------------------------------------------------------------
void Culler::ComputeEnvironment ()
{
	for (int i=0; i<mVisibleSet.GetNumVisible(); i++)
	{
		PX2::Renderable *renderable = mVisibleSet.GetVisible(i);
		PX2::APoint renPos = renderable->WorldTransform.GetTranslate();
		renderable->ClearLights();

		for (int j=0; j<GraphicsRoot::GetSingleton().GetNumLights(); j++)
		{
			PX2::Light *light = GraphicsRoot::GetSingleton().GetLight(j);
			PX2::APoint lightPos = light->Position;

			if (light->GetType() == Light::LT_DIRECTIONAL ||
				light->GetType() == Light::LT_AMBIENT)
			{
				renderable->AddLight(light);
			}
			else if (light->GetType() == Light::LT_POINT)
			{
				Vector3f diff = renPos - lightPos;
				float len = diff.Length();
				if (len <= 8)
					renderable->AddLight(light);
			}
		}
	}

	for (int i=0; i<mVisibleSet.GetNumVisible(); i++)
	{
		PX2::Renderable *renderable = mVisibleSet.GetVisible(i);

		PX2::Light *lightDir = 0;
		for (int j=0; j<renderable->GetNumLights(); j++)
		{
			PX2::Light *light = renderable->GetLight(j);
			if (light->GetType() == Light::LT_DIRECTIONAL)
			{
				lightDir = light;
				break;
			}
		}

		PX2::MaterialInstance *inst = renderable->GetMaterialInstance();
		if (!inst)
			continue;

		PX2::Material *mtl = inst->GetMaterial();
		PX2::StandardESMaterial_Default *esMtl_Def = DynamicCast<StandardESMaterial_Default>(mtl);
		PX2::StandardESMaterial_AlphaTest *esMtl_AT = DynamicCast<StandardESMaterial_AlphaTest>(mtl);

		LightModelDVectorConstant *modelDVectorConstant = 0;
		LightAmbientConstant *ambConstant = 0;
		LightDiffuseConstant *difConstant = 0;

		if (esMtl_Def && lightDir)
		{
			modelDVectorConstant = DynamicCast<LightModelDVectorConstant>(inst->GetVertexConstant(0, "gLightModelDirection"));
			ambConstant = DynamicCast<LightAmbientConstant>(inst->GetVertexConstant(0, "gLightAmbient"));
			difConstant = DynamicCast<LightDiffuseConstant>(inst->GetVertexConstant(0, "gLightDiffuse"));

			if (modelDVectorConstant)
				modelDVectorConstant->SetLight(lightDir);

			if (ambConstant)
				ambConstant->SetLight(lightDir);

			if (difConstant)
				difConstant->SetLight(lightDir);
		}
		else if (esMtl_AT && lightDir)
		{

			modelDVectorConstant = DynamicCast<LightModelDVectorConstant>(inst->GetVertexConstant(0, "gLightModelDirection"));
			ambConstant = DynamicCast<LightAmbientConstant>(inst->GetVertexConstant(0, "gLightAmbient"));
			difConstant = DynamicCast<LightDiffuseConstant>(inst->GetVertexConstant(0, "gLightDiffuse"));

			if (modelDVectorConstant)
				modelDVectorConstant->SetLight(lightDir);

			if (ambConstant)
				ambConstant->SetLight(lightDir);

			if (difConstant)
				difConstant->SetLight(lightDir);
		}
	}
}
//----------------------------------------------------------------------------
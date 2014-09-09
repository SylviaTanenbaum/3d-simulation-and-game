/*
*
* ÎÄ¼þÃû³Æ	£º	PX2SkinController.hpp
*
*/

#ifndef PX2SKINCONTROLLER_HPP
#define PX2SKINCONTROLLER_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Controller.hpp"
#include "PX2Node.hpp"
#include "PX2Vector3.hpp"

namespace PX2
{

	class SkinController : public Controller
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_PROPERTY;
		PX2_DECLARE_STREAM(SkinController);

	public:
		SkinController (int numVertices, int numBones);
		virtual ~SkinController ();

		void SetUseCPU (bool cpu);
		bool IsUseCPU () const;

		inline int GetNumVertices () const;
		inline int GetNumBones () const;
		inline Node** GetBones () const;
		inline std::string *GetBoneNames () const;
		inline float** GetWeights () const;
		inline APoint** GetOffsets () const;
		inline HMatrix* GetTMMatrixs () const;
		inline HMatrix* GetGPUMatrix () const;

		virtual bool Update (double applicationTime);

		void UpdateBlender (Node **lastNodes, Node **curNodes, float weight);

	protected:
		bool mIsUseCPU;

		int mNumVertices;   // nv
		int mNumBones;      // nb
		Node** mBones;      // bones[nb]
		std::string *mBonesName;
		float** mWeights;   // weight[nv][nb], index b+nb*v
		APoint** mOffsets;  // offset[nv][nb], index b+nb*v
		HMatrix *mTMMatrixs;

		APoint *mOriginPoses;
		HMatrix *mGPUMatrixs;

		bool mIsUseBlend;
		float mBlendWeight;
		NodePtr *mBones_Run;
		NodePtr *mBones_Run_Last;
	};

	PX2_REGISTER_STREAM(SkinController);
	typedef Pointer0<SkinController> SkinControllerPtr;
#include "PX2SkinController.inl"

}

#endif

/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2SceneBuilder.hpp
*
* �汾		:	1.0 (2011/05/22)
*
* ����		��	more
*
*/

#ifndef PX2SCENEBUILDER_HPP
#define PX2SCENEBUILDER_HPP

#include "PX2MaxToPX2PluginPre.hpp"
#include "PX2ExportSettings.hpp"
#include "PX2Mtls.hpp"
#include "PX2MtlTree.hpp"
#include "PX2UniMaterialMesh.hpp"

class SceneBuilder
{
public:
	/// ���캯��
	/**
	@param filename:
	����Ҫ������ļ�����
	@param exportSelected:
	true: ����ѡ��Ľڵ�
	false: ������������	
	@param settings:
	�����ŵ���ѡ��
	@param export:
	Max�ĵ�������ĵ��������ӿ�
	@param max:
	Max�ĳ���ְ�ܽӿ�
	@param pkRootNode:
	�����ĳ����������ڵ㣨����û�ѡ��Export Selected�����Ϳ���
	����Max�����ĸ��ڵ㣩��
	*/
	SceneBuilder (const TCHAR* filename, BOOL exportSelected, 
		ExportSettings *settings, ExpInterface *ept, Interface *max,
		INode *exportNode);
	~SceneBuilder ();

private:
	class AnimationTiming
	{
	public:
		AnimationTiming () : Active(FALSE), Start(0), End(0) { /**/ }

		BOOL Active;
		TimeValue Start;
		TimeValue End;
	};

	class ModifierInfo
	{
	public:
		INode *Node;
		std::vector<Modifier*> Modifiers;
	};

	enum KeyType
	{
		KT_TRANSLATION,
		KT_ROTATION,
		KT_SCALE
	};

	class KeyInfo
	{
	public:
		KeyInfo (TimeValue iTime, KeyType eType)
		{
			Time = iTime;
			Type = eType;
		}

		TimeValue Time;
		KeyType Type; 
	};
	
	// Traverse and build
	bool Traverse (INode *maxNode, PX2::Node *relatParent); // movbale��ӦmaxNode�ĸ��ڵ�
	PX2::Movable *BuildGeometry (INode *maxNode, PX2::Node *relatParent);
	PX2::Node *BuildNode (INode *maxNode, PX2::Node *relatParent);
	PX2::Movable *BuildMesh (INode *maxNode, PX2::Node *relatParentOrEqualNode);
	PX2::Transform GetLocalTransform (INode *node, TimeValue iTime);

	// Mesh
	TriObject* GetTriObject (INode* maxNode, bool *needDel);
	void SplitGeometry (Mesh *maxMesh, int mtlIndex, std::vector<UniMaterialMesh*>
		&uMeshes);
	PX2::Float3 GetVertexNormal (Mesh *maxMesh, int faceIndex, int vertex);
	void PackColors (UniMaterialMesh *mesh, Mesh *maxMesh, 
		std::vector<int> &faceIndexParts);
	void PackTextureCoords (UniMaterialMesh *mesh, Mesh *maxMesh, 
		std::vector<int> &faceIndexParts);
	void PackVertices (UniMaterialMesh *mesh, Mesh *maxMesh, 
		std::vector<int> &faceIndexParts, PX2::Float3 *normal);

	// Material
	void CollectMaterials (INode *node);
	void ConvertMaterials ();
	void ConvertMaterial (Mtl &mtl, MtlTree &mtlTree);
	/*void ConvertTexture (Texmap &tex, Class_ID classID, int subNo, TexTree &tree);*/

private:
	Mtls mMtls; // �ռ�Max������Mtl 
	std::vector<MtlTree> mMtlTreeList;

	static const TCHAR* msMapName[NTEXMAPS];
	static const char* msEnvName[5];
	static const TCHAR* msMapEnvironment;
	static const TCHAR* msMapGeneric;

	// Material 
	bool IsValidName (char* str);
	bool ConvertStringAttrib (IParamBlock2 *paramBlock, int index, 
		std::string &name, std::string &str);
	bool ConvertFloatAttrib (IParamBlock2* pkParamBlock, int index, 
		std::string &name, float &value);
	bool ConvertIntAttrib (IParamBlock2* pkParamBlock, int index, 
		std::string &name, int &value);
	bool ConvertColorAttrib (IParamBlock2 *paramBlock, int index,
		std::string &name, PX2::Float4 &color, int &increment);
	bool ConvertPoint3Attrib (IParamBlock2 *paramBlock, int index,
		std::string &name, PX2::Float3 &value);
	bool ConvertPoint4Attrib (IParamBlock2 *paramBlock, int index,
		std::string &name, PX2::Float4 &value);
	bool ConvertBoolAttrib (IParamBlock2 *paramBlock, int index,
		std::string &name, bool &value);
	bool ConvertFloatTabAttrib (IParamBlock2* paramBlock, int index, 
		std::string &name, float *table);
	bool ConvertIntListBoxAttrib (IParamBlock2* paramBlock, int index,
		std::string &name, int &value);
	bool ConvertBitMapAttrib (IParamBlock2 *paramBlock, int index, 
		std::string &name, PX2::Texture2D *&tex2d);
	bool ConvertFRGBAAttrib (IParamBlock2* paramBlock, int index,
		std::string &name, PX2::Float4 &value);

	// Light
	void BuildAmbientLight ();
	void BuildLight (INode *maxNode, PX2::Movable *movbale);
	PX2::APoint GetLightLocation (INode *node);
	PX2::Light *BuildPointLight (INode *node);
	PX2::Light *BuildSpotLight (INode *node, LightState &lightState);
	PX2::Light *BuildDirectionalLight (INode *node);

	// Animation
	static bool AreEqual (const Point3 &point1, const Point3 &point2);
	static bool AreEqual (const Quat &quat1, const Quat &quat2);
	static bool CompareKeyTimes (KeyInfo *first, KeyInfo *second);
	void BuildKeyFrameController (INode *node, PX2::Movable *movable);
	void BuildFrameController (INode *node, PX2::Movable *movable);
	bool GetAnimationTiming (INode *node, AnimationTiming &tTiming,
		AnimationTiming &rTiming, AnimationTiming &sTiming);
	void GetTrnKeyInfo (int &numKeys, Class_ID classID, IKeyControl *keyCtl,
		AnimationTiming &tTiming, std::vector<KeyInfo*> &keyInfos);
	void GetRotKeyInfo (int &numKeys, Class_ID classID, IKeyControl *keyCtl, 
		AnimationTiming &rTiming, std::vector<KeyInfo*> &keyInfos);
	void GetScaleKeyInfo (int &numKeys, Class_ID classID, IKeyControl *keyCtl,
		AnimationTiming &sTiming, std::vector<KeyInfo*> &keyInfos);

	// Modifier
	void ApplyModifiers ();
	void CollectModifiers (INode *node, std::vector<Modifier*> &modifiers);
	void ProcessSkin (INode *node, Modifier *skinMod);
	void ProcessMorpher (INode *node, Modifier *morpherMod);

	TCHAR *mFileName;
	BOOL mExportSelected;
	ExportSettings *mSettings;
	ExpInterface *mExport;
	Interface *mMax;
	INode *mExportMaxNode;
	int mTicksPerFrame;
	TimeValue mTimeStart;
	TimeValue mTimeEnd;
	TimeValue mTimeOffset;
	PX2::NodePtr mScene;
	PX2::LightPtr mAmbientLight;
	std::vector<PX2::LightPtr> mLights;
	std::vector<ModifierInfo*> mModifierList;
	
	static const float ATTENUATION;
	static const float MIN_DIFFERENCE;
};

#endif
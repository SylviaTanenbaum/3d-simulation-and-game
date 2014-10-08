/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Renderable.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2RENDERABLE_HPP
#define PX2RENDERABLE_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Movable.hpp"
#include "PX2IndexBuffer.hpp"
#include "PX2VertexBuffer.hpp"
#include "PX2VertexFormat.hpp"
#include "PX2MaterialInstance.hpp"
#include "PX2Light.hpp"
#include "PX2DynamicBufferObject.hpp"
#include "PX2Shine.hpp"
#include "PX2Texture2D.hpp"

namespace PX2
{

	class Renderer;

	/// ��Ⱦ������
	/**
	* ������Ⱦ���󶼴Ӵ���������
	*/
	class Renderable : public Movable
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_PROPERTY;
		PX2_DECLARE_STREAM(Renderable);

	public:
		enum PrimitiveType
		{
			PT_NONE,  //< default constructor
			PT_POLYPOINT,
			PT_POLYSEGMENTS_DISJOINT,
			PT_POLYSEGMENTS_CONTIGUOUS,
			PT_TRIANGLES,  //< abstract
			PT_TRIMESH,
			PT_TRISTRIP,
			PT_TRIFAN,
			PT_MAX_QUANTITY
		};

	protected:
		/**
		* �������
		*/
		Renderable (PrimitiveType type = PT_NONE);
		Renderable (PrimitiveType type, VertexFormat* vformat, VertexBuffer* vbuffer,
			IndexBuffer* ibuffer);
	public:
		virtual ~Renderable ();

		inline PrimitiveType GetPrimitiveType () const;

		inline void SetVertexFormat (VertexFormat* vformat);
		inline const VertexFormat* GetVertexFormat () const;
		inline VertexFormat* GetVertexFormat ();

		inline void SetVertexBuffer (VertexBuffer* vbuffer);
		inline const VertexBuffer* GetVertexBuffer () const;
		inline VertexBuffer* GetVertexBuffer ();

		inline void SetIndexBuffer (IndexBuffer* ibuffer);
		inline const IndexBuffer* GetIndexBuffer () const;
		inline IndexBuffer* GetIndexBuffer ();

		inline void SetIBOffset (int offset);
		inline int GetIBOffset () const;
		inline void SetIBNumElements (int num);
		inline int GetIBNumElements () const;

		inline void SetShareDBObject_V (DBObject_V *obj);
		inline const DBObject_V *GetShareDBObject_V () const;
		inline DBObject_V *GetShareDBObject_V ();

		inline void SetShareDBObject_I (DBObject_I *obj);
		inline const DBObject_I *GetShareDBObject_I () const;
		inline DBObject_I *GetShareDBObject_I ();

		void SetUseShareBuffers (bool use);
		bool IsUseShareBuffers () const;

		inline const Bound& GetModelBound () const;
		inline Bound& GetModelBound ();

		// ��Ⱦ����
		enum RenderUsage
		{
			RU_UI,
			RU_GENERAL,
			RU_REFLECT,
			RU_SHADOWMAP,
			RU_QUANTITY
		};

		void AddRenderUsage (RenderUsage usage);
		void RemoveRenderUsage (RenderUsage usage);
		unsigned int GetRenderUsage ();

		/// ��Ⱦ�㼶
		enum RenderLayer
		{
			RL_BACKGROUND = 0,
			RL_SKY,
			RL_TERRAIN,
			RL_SCENE,
			RL_UI,
			RL_UI_RANGE,
			RL_UI_RANGE_ELEMENT,
			RL_MAX
		};
		void SetRenderLayer (RenderLayer layer, int sublayer=0);
		RenderLayer GetRenderLayer () const;
		int GetSubLayer () const;

		unsigned int GetSortIndex () const;

		// ���Ƽ���ͼ�ε�Ч��ʵ��
		inline void SetMaterialInstance (MaterialInstance* material);
		inline MaterialInstance* GetMaterialInstance () const;

		bool AllowRed;
		bool AllowGreen;
		bool AllowBlue;
		bool AllowAlpha;

		// �ƹ�
		/*
		* ��ǰ��Ⱦ���յ�Ӱ��ĵƹ�
		*/
		bool AddLight (Light *light);
		bool RemoveLight (Light *light);		
		void ClearLights ();
		int GetNumLights ();
		Light *GetLight (int i);

		// Shine
		Shine *GetDefaultShine ();
		const Shine *GetDefaultShine () const;
		void SetLightTexture (Texture2D *tex);
		const std::string &GetLightTexture () const;
		const std::string &GetNormalTexture () const;

		void SetBakeObject (bool bakeObject);
		bool IsBakeObject () const;
		void SetBakeTarget (bool bakeTarget);
		bool IsBakeTarget () const;
		
		// Bake
		enum BakeSizeType
		{
			BST_NORMAL,
			BST_64,
			BST_128,
			BST_256, 
			BST_512,
			BST_1024,
			BST_MAX_TYPE
		};
		void SetBakeSizeType (BakeSizeType type);
		BakeSizeType GetBakeSizeType () const;
		
		void SetUseLightTexture (bool light, Texture2D *lightTex);
		bool IsUseLightTexture () const;

		void ConvertLightMtl ();

		virtual void SetAlpha (float alpha);

		// ����ͼ�θ�������
		enum UpdateType
		{
			GU_MODEL_BOUND_ONLY = -3,
			GU_NORMALS = -2,
			GU_USE_GEOMETRY = -1,
			GU_USE_TCOORD_CHANNEL = 0
		};

		/// ���Ӷ���ģ�͸���
		/**
		* ������Ӷ����VertexBuffer���޸��ˣ�����Ҫ���£�normals,tangents,
		* bitangents���������type�������µĹ������£�
		* GU_MODEL_BOUND_ONLY
		*	����Ŀռ�λ�øı��ˣ�ֻ���°�Χ�С�
		* �����������£���Χ��Ҳ������¡�������Ӷ����Ǵ�Triangles�����Ļ���
		* ����з�����Ϣ�������ȸ��·�����Ϣ��
		* GU_NORMALS
		*	�����귨����Ϣ�������ٸ�����������ռ䡣
		* GU_USE_GEOMETRY
		* GU_USE_TCOORD_CHANNEL + nonnegative_integer
		*	ʹ�õ�nonnegative_integer���������������������ռ䡣
		* Ϊ�˽�ʡ�Դ棬����Կ���ֻ����normals��tangents��Ȼ��ʹ��������ɫ��
		* ����bitangent��
		*	bitangent = Cross(normal, tangent)			
		*/
		virtual void UpdateModelSpace (UpdateType type);

		virtual void OnForceBind ();

public_internal:
		float mEyeDistance; // �������
		static bool LessThan (const Renderable *renderable0,
			const Renderable *renderable1);

	protected:
		void AdjustTransparent ();
		void SetTransparent (bool transparent);

public_internal:
		bool IsTransparent () const;

	protected:
		// ����ͼ�θ���
		virtual void UpdateWorldBound ();
		virtual void UpdateModelBound ();

		// �����ü�
		virtual void GetVisibleSet (Culler& culler, bool noCull);

	protected:
		// ��Ⱦ����
		unsigned int mRenderUsageBits;
		unsigned int mSortIndex; //(layer<<16)|current

		// ����ͼ������
		PrimitiveType mType;
		VertexFormatPtr mVFormat;
		VertexBufferPtr mVBuffer;
		IndexBufferPtr mIBuffer;		
		Bound mModelBound;

		DBObject_V *mDBObject_V;
		DBObject_I *mDBObject_I;
		bool mIsUseShareBuffers;

		int mIBOffset;
		int mIBNumElements;

		ShinePtr mDefaultShine;

		bool mIsBackObject;
		bool mIsBackTarget;
		BakeSizeType mBakeSizeType;
		bool mIsUseLightTexture;
		std::string mLightTexPath;
		std::string mNormalTexPath;
		MaterialInstancePtr mNormalMaterialInstance;

		// ���Ƽ���ͼ�ε�Ч��
		MaterialInstancePtr mMaterial;

		RenderLayer mLayer;
		int mSubLayer;

		// ��ǰ������Ӱ��ĵƹ�
		/*
		* �ƹⲻ�ó־û�����ÿ����Ⱦ֮ǰ������Ӱ��ĵƹ⡣
		*/
		std::vector<LightPtr> mInfulencedLights; 

		// Begin load/save
	public:
		// created properly unless we have a Load for each instantiable primitive.
		// ʹ�ó־û�ϵͳfrom/to *.tdvf Load/Save��Ⱦ������ΪRenderable�Ǿ��弸��
		// ͼ��һ��������࣬�������ǲ���ͨ���˺������أ�����������һ��Renderable��
		static void LoadPX2VF (const std::string& name, PrimitiveType& type,
			VertexFormat*& vformat, VertexBuffer*& vbuffer, IndexBuffer*& ibuffer,
			int mode = FileIO::FM_DEFAULT_READ);

		void SavePX2VF (const std::string& name,
			int mode = FileIO::FM_DEFAULT_WRITE);

	private:
		static VertexFormat* LoadVertexFormat (FileIO& inFile);
		static VertexBuffer* LoadVertexBuffer (FileIO& inFile,
			VertexFormat* vformat);
		static IndexBuffer* LoadIndexBuffer (FileIO& inFile);
		void SaveVertexFormat (FileIO& outFile);
		void SaveVertexBuffer (FileIO& outFile);
		void SaveIndexBuffer (FileIO& outFile);
		// End load/save
	};

	PX2_REGISTER_STREAM(Renderable);
	typedef Pointer0<Renderable> RenderablePtr;
#include "PX2Renderable.inl"

}

#endif

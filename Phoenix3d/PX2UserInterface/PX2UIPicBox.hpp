/*
*
* �ļ�����	��	PX2UIPicBox.hpp
*
*/

#ifndef PX2UIPICBOX_HPP
#define PX2UIPICBOX_HPP

#include "PX2UIPre.hpp"
#include "PX2Float2.hpp"
#include "PX2Size.hpp"
#include "PX2Rect.hpp"
#include "PX2Texture2D.hpp"
#include "PX2Material.hpp"
#include "PX2MaterialInstance.hpp"
#include "PX2TriMesh.hpp"
#include "PX2Camera.hpp"
#include "PX2UIMaterial.hpp"
#include "PX2UIMaterialUV3.hpp"
#include "PX2UIMaterialDark.hpp"
#include "PX2InputEvent.hpp"
#include "PX2TexPackData.hpp"

namespace PX2
{

	class UIPicBox : public TriMesh
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_PROPERTY;
		PX2_DECLARE_STREAM(UIPicBox);

	public:
		UIPicBox (const std::string &filename = "Data/engine/default.png");
		UIPicBox (const std::string &packName, const std::string &eleName);
		virtual ~UIPicBox ();

		enum PicBoxType
		{
			PBT_NORMAL,
			PBT_NINE,
			PBT_MAX_TYPE
		};
		void SetPicBoxType (PicBoxType type);
		PicBoxType GetPicBoxType ();

		void SetDynamic (bool dyn);
		bool IsDynamic () const;

		// anchor
		void SetAnchorPoint (float anchX, float anchZ);
		void SetAnchorPoint (Float2 anchor);
		const Float2 &GetAnchorPoint () const;
		Float2 &GetAnchorPoint ();

		// size
		void SetSize (float width, float height);
		void SetSize (const Sizef &size);
		const Sizef &GetSize () const;
		void SetWidth (float width);
		float GetWidth () const;
		void SetHeight (float height);
		float GetHeight () const;
		void MakeSizeWithTex ();

		void SetTexCornerSize (float width, float height);
		void SetTexCornerSize (const Sizef &size);
		const Sizef &GetTexCornerSize () const;
		Sizef &GetTexCornerSize ();
		void SetTexCornerWidth (float width);
		float GetTexCornerWidth () const;
		void SetTexCornerHeight (float height);
		float GetTexCornerHeight () const;

		// alpha color
		virtual void SetAlpha (float alpha); //< 0-1
		virtual void SetColor (const Float3 &color);

		void SetUVScaleX (float xScale);
		void SetUVScaleY (float yScale);
		void SetUVScale (Float2 uvScale);
		float GetUVScaleX () const;
		float GetUVScaleY () const;
		const Float2 &GetUVScale () const;
		Float2 &GetUVScale ();

		// material
		UIMaterial *GetUIMaterial () const;

		enum TexMode
		{
			TM_TEX,
			TM_TEXPACK_ELE,
			TM_MAX_MODE
		};
		void SetTexMode (TexMode mode);
		TexMode GetTexMode () const;

		// base texture
		void SetTexture (Texture2D *tex);
		void SetTexture (const std::string &filename);
		void SetTexture (const std::string &texPackName, const std::string &eleName);
		Texture2D *GetTexture ();
		const std::string &GetTextureFilename () const;
		void SetDoubleSide (bool d);
		bool IsDoubleSide () const;
		void SetUseAlphaTest (bool use);
		bool IsUseAlphaText () const;
		void SetFliterPoint (bool point);
		bool IsFliterPoint () const;
		void SetUseClamp (bool clamp);
		bool IsUseClamp () const;

		// added
		void SetUseAddedMask (bool use);
		bool IsUseAddedMask () const;
		void SetAddedTexture (const std::string &filename); // added
		const std::string &GetAddedTextureFilename () const;
		void SetAddedTextureUVSpeed (const Float2 &uv);
		const Float2 &GetAddedTextureUVSpeed () const;
		void SetAddedTextureUVRepeat (const Float2 &repeat);
		const Float2 &GetAddedTextureUVRepeat () const;
		void SetAddedTextureColor (const Float3 &color);
		Float3 GetAddedTextureColor () const;
		void SetAddedTextureAlpha (float alpha);
		float GetAddedTextureAlpha () const;
		void SetAddedTextureAlphaSpeed (float speed);
		float GetAddedTextureAlphaSpeed () const;
		void SetMaskTexture (const std::string &filename); // mask
		const std::string &GetMaskTexture () const;
		void SetMaskTextureAlpha (float alpha);
		float GetMaskTextureAlpha () const;
		void SetMaskTextureAlphaSpeed (float speed);
		float GetMaskTextureAlphaSpeed () const;

		// dark
		void SetUseDark (bool use);
		bool IsUserDark () const;
		void SetDarkValue (float darkValue);
		float GetDarkValue () const;

		virtual void OnForceBind ();
		
	public_internal:
		void UIAfterPicked (int info);

	protected:
		void _Init ();
		virtual void UpdateWorldData (double applicationTime);

		void UpdateBuffers (float elapsedTime);
		void UpdateVertexBuffer (float elapsedTime);
		void UpdateIndexBuffer ();
		void UpdateDynBuffers (float elapsedTime);
		void ReCreateVBuffer ();

		void UpdateMtl ();
		void SetTextureNoRecreateBuffer (const std::string &texPackName, 
			std::string eleName);

		virtual void OnPicked (int info);
		virtual void OnNotPicked (int pickInfo);

		PicBoxType mPicBoxType;
		bool mIsDynamic;
		Float2 mAnchorPoint;
		Sizef mSize;
		Sizef mCornerSize;
		Float2 mUV0;
		Float2 mUV1;
		Float2 mUV2;
		Float2 mUV3;
		Float4 mColor;
		Float2 mUVScale;
		TexPackElement mPackEle;
		bool mIsBufferNeedUpdate;

		bool mIsMtlNeedUpdate;
		TexMode mTexMode;
		UIMaterialPtr mUIMtl;
		MaterialInstancePtr mUIMtlInst;
		std::string mTexturePathname;
		std::string mTexturePackName;
		std::string mElementName;

		Texture2DPtr mTexReaded; // �ɰ汾0����ʹ�ã���������������ȡ��ͼ���ļ�����

		// added
		UIMaterialUV3Ptr mUIMtlUV3;
		MaterialInstancePtr mUIMtlInstUV3;
		ShaderFloatPtr mAddedColorFloat;
		bool mIsUseAddedMask;
		float mLastAddedAppTime;
		std::string mAddedTextureFilename; // added
		Float4 mAddedTextureColor;
		Float2 mAddedUV0;
		Float2 mAddedUV1;
		Float2 mAddedUV2;
		Float2 mAddedUV3;
		Float2 mAddedTextureUVSpeed;
		Float2 mAddedTextureUVSRepeat;
		float mAddedTextureAlphaSpeed;
		std::string mMaskTextureFilename; // mask
		float mMaskTextureAlpha;
		float mMaskTextureAlphaSpeed;

		// dark
		bool mIsUseDark;
		UIMaterialDarkPtr mUIMtlDark;
		MaterialInstancePtr mUIMtlInstDark;
		ShaderFloatPtr mDarkScaleFloat;
		Float4 mDarkParam;
	};

	PX2_REGISTER_STREAM(UIPicBox);
	typedef Pointer0<UIPicBox> UIPicBoxPtr;
#include "PX2UIPicBox.inl"

}

#endif
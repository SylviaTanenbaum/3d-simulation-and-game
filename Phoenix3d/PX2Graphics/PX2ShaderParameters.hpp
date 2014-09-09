/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2ShaderParameters.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2SHADERPARAMETERS_HPP
#define PX2SHADERPARAMETERS_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Shader.hpp"
#include "PX2ShaderFloat.hpp"
#include "PX2Texture.hpp"

namespace PX2
{

	typedef Texture *(*TextureUserLoadFun) (const char *filename);

	/// ��ɫ��������
	/**
	* һ�����ʣ�Ϊÿ����Ⱦpassά��һ������ɫ����������һ������ɫ���������ڱ���
	* ��ɫ����������ġ���ɫ����������
	*/
	class ShaderParameters : public Object
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_PROPERTY;
		PX2_DECLARE_STREAM(ShaderParameters);

	public:
		ShaderParameters (Shader* shader);
		virtual ~ShaderParameters ();

		// ��Ա����
		inline int GetNumConstants () const;
		inline int GetNumTextures () const;
		inline ShaderFloatPtr* GetConstants () const;
		inline TexturePtr* GetTextures () const;

		// ��Щ��������constants/textures����������ɹ������������ڳ��������е�
		// ������
		int SetConstant (const std::string& name, ShaderFloat* sfloat);
		int SetTexture (const std::string& name, Texture* texture);

		// ͨ�����溯�����ص�������ֱ��������ɫ������
		void SetConstant (int handle, ShaderFloat* sfloat);
		void SetTexture (int handle, Texture* texture);

		// ��Ա����
		ShaderFloat* GetConstant (const std::string& name) const;
		Texture* GetTexture (const std::string& name) const;

		// handle�������Set*�������ػ��
		ShaderFloat* GetConstant (int handle) const;
		Texture* GetTexture (int handle) const;

		// �ڻ��Ƶ�ʱ����³���
		void UpdateConstants (const Renderable* renderable, const Camera* camera);

		// ������ͼ
		static void SetUserLoadFun (TextureUserLoadFun userLoadFun);

		static TextureUserLoadFun msTextureUserLoadFun;

	protected:
		ShaderPtr mShader;
		int mNumConstants;
		ShaderFloatPtr* mConstants;
		int mNumTextures;
		TexturePtr* mTextures;
		std::vector<std::string> mTextureResPath;
	};

	PX2_REGISTER_STREAM(ShaderParameters);
	typedef Pointer0<ShaderParameters> ShaderParametersPtr;
#include "PX2ShaderParameters.inl"

}

#endif

/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2MaterialInstance.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2MATERIALINSTANCE_HPP
#define PX2MATERIALINSTANCE_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2ShaderParameters.hpp"
#include "PX2Material.hpp"

namespace PX2
{

	class MaterialInstance : public Object
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_PROPERTY;
		PX2_DECLARE_STREAM(MaterialInstance);

	public:
		MaterialInstance (const Material* material, int techniqueIndex);
		virtual ~MaterialInstance ();

		void SetBlendMode(int mode)
		{
			mBlendMode = mode;
		}

		// ��Ա����
		/*
		* ��Щ��Ҫ��Renderer��Ⱦ����ͼ��ʱ���á�
		*/
		inline Material* GetMaterial () const;
		inline int GetTechniqueIndex () const;
		inline int GetNumPasses () const;
		const MaterialPass* GetPass (int pass) const;
		ShaderParameters* GetVertexParameters (int pass) const;
		ShaderParameters* GetPixelParameters (int pass) const;

		// ��Щ��������������ɫ��������������������ɹ������س���������������
		// Ӧ�����е��������������ֵ��������Set*�����е�'handle'���������Ա���
		// �ļ����ıȽϡ�
		int SetVertexConstant (int pass, const std::string& name,
			ShaderFloat* sfloat);

		int SetPixelConstant (int pass, const std::string& name,
			ShaderFloat* sfloat);

		int SetVertexTexture (int pass, const std::string& name,
			Texture* texture);

		int SetPixelTexture (int pass, const std::string& name,
			Texture* texture);

		// 'handle'�������Set*�������ء�
		void SetVertexConstant (int pass, int handle, ShaderFloat* sfloat);
		void SetPixelConstant (int pass, int handle, ShaderFloat* sfloat);
		void SetVertexTexture (int pass, int handle, Texture* texture);
		void SetPixelTexture (int pass, int handle, Texture* texture);

		// �����ɫ������������
		ShaderFloat* GetVertexConstant (int pass, const std::string& name) const;
		ShaderFloat* GetPixelConstant (int pass, const std::string& name) const;
		Texture* GetVertexTexture (int pass, const std::string& name) const;
		Texture* GetPixelTexture (int pass, const std::string& name) const;

		// 'handle'�������Set*�������ء�
		ShaderFloat* GetVertexConstant (int pass, int handle) const;
		ShaderFloat* GetPixelConstant (int pass, int handle) const;
		Texture* GetVertexTexture (int pass, int handle) const;
		Texture* GetPixelTexture (int pass, int handle) const;

	protected:
		MaterialPtr mMaterial;
		int mTechniqueIndex;
		int mNumPasses;
		ShaderParametersPtr* mVertexParameters;
		ShaderParametersPtr* mPixelParameters;

		int mBlendMode;
	};

	PX2_REGISTER_STREAM(MaterialInstance);
	typedef Pointer0<MaterialInstance> MaterialInstancePtr;
#include "PX2MaterialInstance.inl"

}

#endif

/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Material.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2MATERIAL_HPP
#define PX2MATERIAL_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2FileIO.hpp"
#include "PX2MaterialTechnique.hpp"

namespace PX2
{

	/// ����ģ����
	class Material : public Object
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(Material);

	public:
		Material ();
		virtual ~Material ();

		/// ����Ⱦ��������ĩβ����һ����Ⱦ����
		void InsertTechnique (MaterialTechnique* technique);

		inline int GetNumTechniques () const;
		MaterialTechnique* GetTechnique (int techniqueIndex) const;

		int GetNumPasses (int techniqueIndex) const;
		MaterialPass* GetPass (int techniqueIndex, int passIndex) const;
		VertexShader* GetVertexShader (int techniqueIndex, int passIndex) const;
		PixelShader* GetPixelShader (int techniqueIndex, int passIndex) const;
		AlphaProperty* GetAlphaProperty (int techniqueIndex, int passIndex) const;
		CullProperty* GetCullProperty (int techniqueIndex, int passIndex) const;
		DepthProperty* GetDepthProperty (int techniqueIndex, int passIndex) const;
		OffsetProperty* GetOffsetProperty (int techniqueIndex, int passIndex) const;
		StencilProperty* GetStencilProperty (int techniqueIndex, int passIndex) const;
		WireProperty* GetWireProperty (int techniqueIndex, int passIndex) const;

	protected:
		std::vector<MaterialTechniquePtr> mTechniques;

		// Begin load/save
	public:
		static Material* LoadPX2fx (const std::string& name,
			int mode = FileIO::FM_DEFAULT_READ);

		void SavePX2fx (const std::string& name,
			int mode = FileIO::FM_DEFAULT_WRITE);

	protected:
		// ����֧���������*.pxfx��������Ч��
		Material (const std::string& name,
			int mode = FileIO::FM_DEFAULT_READ);

	private:
		static MaterialTechnique* LoadMaterialTechnique (FileIO& inFile);
		static MaterialPass* LoadMaterialPass (FileIO& inFile);
		static Shader* LoadShader (FileIO& inFile, bool isVertexShader);
		static AlphaProperty* LoadAlphaProperty (FileIO& inFile);
		static CullProperty* LoadCullProperty (FileIO& inFile);
		static DepthProperty* LoadDepthProperty (FileIO& inFile);
		static OffsetProperty* LoadOffsetProperty (FileIO& inFile);
		static StencilProperty* LoadStencilProperty (FileIO& inFile);
		static WireProperty* LoadWireProperty (FileIO& inFile);
		static std::string LoadString (FileIO& inFile);

		static void SaveMaterialTechnique (FileIO& outFile,
			MaterialTechnique* technique);
		static void SaveMaterialPass (FileIO& outFile, MaterialPass* pass);
		static void SaveShader (FileIO& outFile, Shader* shader);
		static void SaveAlphaProperty (FileIO& outFile, AlphaProperty* aproperty);
		static void SaveCullProperty (FileIO& outFile, CullProperty* cproperty);
		static void SaveDepthProperty (FileIO& outFile, DepthProperty* dproperty);
		static void SaveOffsetProperty (FileIO& outFile, OffsetProperty* oproperty);
		static void SaveStencilProperty (FileIO& outFile, StencilProperty* sproperty);
		static void SaveWireProperty (FileIO& outFile, WireProperty* wproperty);
		static void SaveString (FileIO& outFile, std::string& name);

		// End load/save
	};

	PX2_REGISTER_STREAM(Material);
	typedef Pointer0<Material> MaterialPtr;
#include "PX2Material.inl"

}

#endif
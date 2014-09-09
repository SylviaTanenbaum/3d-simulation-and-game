/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Texture2MulMaterial.hpp
*
*/

#ifndef PX2TEXTURE2MULMATERIAL_HPP
#define PX2TEXTURE2MULMATERIAL_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2MaterialInstance.hpp"
#include "PX2Texture2D.hpp"

namespace PX2
{

	class Texture2MulMaterial : public Material
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(Texture2MulMaterial);

	public:
		// Construction and destruction.
		Texture2MulMaterial ();
		virtual ~Texture2MulMaterial ();

		// Any change in sampler state is made via the pixel shader.
		PixelShader* GetPixelShader () const;

		// Create an instance of the effect with unique parameters.  If a
		// sampler filter mode is set to a value corresponding to mipmapping,
		// then the mipmaps will be generated if necessary.
		MaterialInstance* CreateInstance (Texture2D* texture0,
			Texture2D* texture1) const;

		// Convenience for creating an instance.  The application does not have to
		// create the effect explicitly in order to create an instance from it.
		static MaterialInstance* CreateUniqueInstance (
			Texture2D* texture0,
			Shader::SamplerFilter filter0,
			Shader::SamplerCoordinate coordinate00,
			Shader::SamplerCoordinate coordinate01,
			Texture2D* texture1,
			Shader::SamplerFilter filter1,
			Shader::SamplerCoordinate coordinate10,
			Shader::SamplerCoordinate coordinate11);

	private:
		static int msDx9VRegisters[1];
		static int msOglVRegisters[1];
		static int msOpenGLES2VRegisters[1];
		static int* msVRegisters[Shader::MAX_PROFILES];
		static std::string msVPrograms[Shader::MAX_PROFILES];
		static int msAllPTextureUnits[2];
		static int* msPTextureUnits[Shader::MAX_PROFILES];
		static std::string msPPrograms[Shader::MAX_PROFILES];
	};

	PX2_REGISTER_STREAM(Texture2MulMaterial);
	typedef Pointer0<Texture2MulMaterial> Texture2MulEffectPtr;

}

#endif

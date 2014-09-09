/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2VertexShader.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2VERTEXSHADER_HPP
#define PX2VERTEXSHADER_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Shader.hpp"

namespace PX2
{

	/// ������ɫ����
	class VertexShader : public Shader
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(VertexShader);

	public:
		VertexShader (const std::string& programName, int numInputs,
			int numOutputs, int numConstants, int numSamplers, bool profileOwner);

		virtual ~VertexShader ();

		/// ������ɫ���汾��Ϣ
		enum Profile
		{
			VP_NONE,
			VP_VS_1_1,
			VP_VS_2_0,
			VP_VS_3_0,
			VP_ARBVP1,
			VP_OPENGLES2,
		};

		static void SetProfile (Profile profile);
		static Profile GetProfile ();

	protected:
		static Profile msProfile;
	};

	PX2_REGISTER_STREAM(VertexShader);
	typedef Pointer0<VertexShader> VertexShaderPtr;

}

#endif
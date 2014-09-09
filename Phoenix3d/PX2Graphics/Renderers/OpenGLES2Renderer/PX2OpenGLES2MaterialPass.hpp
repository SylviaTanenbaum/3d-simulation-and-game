/*
* Turandot 3D ��Ϸ���� Version 1.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	TdOpenGLES2MaterialPass.hpp
*
* �汾		:	1.0 (2011/07/21)
*
* ����		��	���
*
*/

#ifndef PX2OPENGLES2MATERIALPASS_HPP
#define PX2OPENGLES2MATERIALPASS_HPP

#include "PX2OpenGLES2RendererPre.hpp"
#include "PX2PixelShader.hpp"
#include "PX2MaterialPass.hpp"

namespace PX2
{

	class Renderer;

	class PdrMaterialPass
	{
	public:
		PdrMaterialPass (Renderer *renderer, const MaterialPass *pass);
		~PdrMaterialPass ();

		void Enable (Renderer *renderer);
		void Disable (Renderer *renderer);

		GLuint GetProgram () { return mProgramObject; }

	private:
		const MaterialPass *mPass;
		GLuint mProgramObject;

		std::map<std::string, int> mAttribLocations;
	};

}

#endif
/*
*
* �ļ�����	��	PX2StringHelp.hpp
*
*/

#ifndef PX2STRINGHELP_HPP
#define PX2STRINGHELP_HPP

#include "PX2CorePre.hpp"
#include "PX2Ascii.hpp"
#include <stdlib.h>

namespace PX2
{

	class StringHelp
	{
	public:
		static bool Initlize();

		// ���ļ�·����׼������"\\"����'/'��, ���ĩβû��'/',���'/'
		static std::string StandardisePath (const std::string &path);

		/// ���ļ�·������ļ��������ļ���
		/**
		* ����"E:\\Phoenix\\Data\\Tdtf\\Normal.tdtf"��ɵĽ��Ϊ
		* outPath = "E:/Phoenix/Data//Tdtf/"
		* outBaseFileName = "Normal.tdtf"
		*/
		static void SplitFilename (const std::string &fullName,
			std::string &outPath, std::string &outBaseFileName);

		/// ���ļ�������ļ����ƺ���չ��
		/**
		* ����"Normal.tdtf"��ɵĽ��Ϊ
		* outBaseName = "Normal"
		* outExtention = "tdtf"
		*/
		static void SplitBaseFilename (const std::string &baseFileName,
			std::string &outBaseName, std::string &outExtention);

		/// ���ļ�·������ļ��������ļ����ƺ���չ����
		static void SplitFullFilename (const std::string &fullName,
			std::string &outPath, std::string &outBaseName, 
			std::string &outExtention);

		static std::string PathToWindowStyle (const std::string &fromPath);

		static int UnicodeToAnsi (char *dest, int maxChar, const wchar_t *src,
			int numSrcChar=-1);
		static int AnsiToUnicode (wchar_t *dest, int maxChar, const char *src, 
			int numSrcChar=-1);
		static int UnicodeToUTF8 (char *destBuf, int maxChar, const wchar_t *src, 
			int numSrcChar=-1);
		static int UTF8ToUnicode (wchar_t *destBuf, int maxChar, const char *src, 
			int numSrcChar=-1);

		static const char *UnicodeToAnsi (const wchar_t *src, int numSrcChar=-1);
		static wchar_t *AnsiToUnicode (const char *src, int numSrcChar=-1);
		static const char *UnicodeToUTF8( const wchar_t *src, int numSrcChar=-1);
		static const wchar_t *UTF8ToUnicode( const char *src, int numSrcChar=-1);

		static std::string IntToString (int val);
		static int StringToInt (const std::string &val);
		static std::string FloatToString (float val);

		static std::string FormatStr (const std::string &str, const std::vector<std::string> &params);
		static std::string FormatStr (const std::string &str, int val);

		// Hash
		static unsigned int Hash(const std::string &str, unsigned int type);
		static unsigned int Hash(const char *str, unsigned int type,
			int length=-1); //< ���length<0,��ʾ������ַ�������\0��β

		static std::string FormatSeconds (int seconds);
	};

	//----------------------------------------------------------------------------
	template <class S>
	S ToUpper(const S& str)
	{
		typename S::const_iterator it  = str.begin();
		typename S::const_iterator end = str.end();

		S result;
		result.reserve(str.size());
		while (it != end) result += Ascii::ToUpper(*it++);
		return result;
	}
	//----------------------------------------------------------------------------
	template <class S>
	S& ToUpperInPlace(S& str)
	{
		typename S::iterator it  = str.begin();
		typename S::iterator end = str.end();

		while (it != end) { *it = Ascii::ToUpper(*it); ++it; }
		return str;
	}
	//----------------------------------------------------------------------------
	template <class S>
	S ToLower(const S& str)
	{
		typename S::const_iterator it  = str.begin();
		typename S::const_iterator end = str.end();

		S result;
		result.reserve(str.size());
		while (it != end) result += Ascii::ToLower(*it++);
		return result;
	}
	//----------------------------------------------------------------------------
	template <class S>
	S& ToLowerInPlace(S& str)
	{
		typename S::iterator it  = str.begin();
		typename S::iterator end = str.end();

		while (it != end) { *it = Ascii::ToLower(*it); ++it; }
		return str;
	}
	//----------------------------------------------------------------------------

}

#endif
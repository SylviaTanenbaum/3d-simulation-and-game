/*
*
* �ļ�����	��	PX2StringTokenizer.hpp
*
*/

#ifndef PX2STRINGTOKENIZER_HPP
#define PX2STRINGTOKENIZER_HPP

#include "PX2CorePre.hpp"

namespace PX2
{

	/// ���ַ������зָ�
	/**
	* TOK_IGNORE_EMPTY: �� tokens ������
	* TOK_TRIM:��β���ַ������ԣ�����
	*		StringTokenizer(",ab,cd,", ","); ��������token "ab"��"cd"
	*/
	class StringTokenizer
	{
	public:
		enum Options
		{
			TOK_IGNORE_EMPTY = 1, /// ignore empty tokens
			TOK_TRIM         = 2  /// remove leading and trailing whitespace from tokens
		};

		typedef std::vector<std::string>::const_iterator Iterator;

		StringTokenizer(const std::string& str, const std::string& separators, int options = 0);
		~StringTokenizer();

		Iterator Begin() const;
		Iterator End() const;

		const std::string& operator [] (std::size_t index) const;
		std::size_t Count() const;
		/// Returns the number of tokens.

	private:
		StringTokenizer(const StringTokenizer&);
		StringTokenizer& operator = (const StringTokenizer&);

		std::vector<std::string> _tokens;
	};
#include "PX2StringTokenizer.inl"

}

#endif
/*
*
* �ļ�����	��	PX2LanguageManager.hpp
*
*/

#ifndef PX2LANGUAGEMANAGER_HPP
#define PX2LANGUAGEMANAGER_HPP

#include "PX2UnityPre.hpp"
#include "PX2Singleton.hpp"

namespace PX2
{

	class LanguageManager : public Singleton<LanguageManager>
	{
	public:
		LanguageManager ();
		virtual ~LanguageManager ();

		bool Load (const char *filename);
		bool Add (const char *filename);
		void SetLanguage (int index);
		bool HasValue (const std::string &key) const;
		std::string GetValue (const std::string &key);
		std::string GetValue (const std::string &key, int index);
		void Clear ();

	protected:
		int mLanguageIndex;
		typedef HashTable<FString, std::vector<std::string>, FixedStringHashCoder> LanguageTable;
		typedef LanguageTable::Element * LanguageTableIterator;

		LanguageTable mLanguages;
	};

#define PX2_LM LanguageManager::GetSingleton()
#define PX2_LMVAL LanguageManager::GetSingleton().GetValue

}

#endif
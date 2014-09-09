/*
*
* �ļ�����	��	PX2LogicManager.hpp
*
*/

#ifndef PX2LOGICMANAGER_HPP
#define PX2LOGICMANAGER_HPP

#include "PX2GamePre.hpp"
#include "PX2Singleton.hpp"
#include "PX2Gameable.hpp"

namespace PX2
{

	class LogicManager : public Singleton<LogicManager>
	{
	public:
		LogicManager ();
		virtual ~LogicManager();

		const std::vector<std::string> &GetActorLogicNames () const;
		const std::vector<std::string> &GetSceneLogicNames () const;

		Gameable *Factory (const std::string &name);

		Gameable *LoadFromXML (const std::string &filename);
		Gameable *LoadFromBinary (const std::string &filename);
		Gameable *CreateFromRttiName (const std::string &rttiName);

	protected:
		std::vector <std::string> mActorLogicNames;
		std::vector <std::string> mSceneLogicNames;
	};

#include "PX2LogicManager.inl"

}

#endif
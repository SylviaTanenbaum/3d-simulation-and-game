/*
*
* �ļ�����	��	PX2SoundSystem.hpp
*
*/

#ifndef PX2SOUNDSYSTEM_HPP
#define PX2SOUNDSYSTEM_HPP

#include "PX2SoundSystemPre.hpp"
#include "PX2Singleton.hpp"
#include "PX2APoint.hpp"
#include "PX2AVector.hpp"
#include "PX2Sound.hpp"

namespace PX2
{

	struct SoundSystemInitInfo
	{
		SoundSystemInitInfo ();
		
		int MaxChannels;
		float DopplerScale;
		float DistanceFactor;
		float RolloffScale;
	};

	struct SoundCreateInfo3D
	{
		SoundCreateInfo3D ();

		float MinDistance; 
		float MaxDistance;
		float Volume;
		APoint Position;
		AVector Velocity;
		bool IsLoop;
	};

	class SoundSystem : public Singleton<SoundSystem>
	{
	public:
		virtual ~SoundSystem ();

		enum SystemType
		{
			ST_NULL,
			ST_FMOD,
			ST_ANDROID,
			ST_MARM,
			ST_MAX_TYPE
		};
		SystemType GetSystemType () const;

		static SoundSystem *Create (SystemType type,
			const SoundSystemInitInfo &initInfo);

		void SetMaxNumPlaySameTime (int num);
		int GetMaxNumPlaySameTime () const;

		void SetPlaySameTimeRange (float time);
		float GetPlaySameTimeRange () const;

		virtual void Clear ();

		virtual void Update (double appSeconds, double elapsedSeconds);

		// listen
		/* �����Ĳ���������Ϊ0*/
		virtual void SetListener (const APoint *position,
			const AVector *velocity, const AVector *forward,
			const AVector *up);
		const APoint &GetListenerPos () const;

		/// ��ָ��ͨ����������
		/**
		* channel : �������ֵ�ͨ����0-3��
		* filename : �����ļ�����Ϊ0��ʾֹͣ��ǰ����
		* isLoop : �Ƿ�ѭ������
		* fadeSeconds : ���뵭��ʱ�䣬Ϊ0.0f��ʾ���������������
		*/
		virtual void PlayMusic (int channel, const char *filename,
			bool isLoop, float fadeSeconds, float volume=1.0f) = 0;
		virtual void SetMusicVolume (int channel, float volume) = 0;
		virtual void EnableMusic (bool enable);
		bool IsMusicEnable () const;

		// sound 
		virtual bool PlaySound2DControl (const char *filename,
			float volume, bool isLoop, Sound *&sound);
		virtual bool PlaySound3DControl (const char *filename, 
			const SoundCreateInfo3D &createInfo, Sound *&sound);
		virtual void LoadSound (const char *filename);
		virtual void UnloadSound (const char *filename);
		virtual void EnableSounds (bool enable);
		bool IsSoundEnable () const;

		bool CanPlaySameTime (const std::string &filename, float playTime);
		int GetNumPlaySameTime (const std::string &filename);
		void MinusNumPlaySameTime (const std::string &filename);
		void ResetNumPlaySameTime (const std::string &filename);

	protected:
		SoundSystem ();
		SoundSystem (SystemType type);
		
		SystemType mSystemType;
		APoint mListenPos;
		int mMaxNumPlaySameTime;
		float mPlaySameTimeRange;
		bool mIsMusicEnable;
		bool mIsSoundEnable;
		
		std::map<std::string, int> mNumCurPlaying;
		std::map<std::string, float> mLastPlayTime;
	};

#include "PX2SoundSystem.inl"

#define PX2_SS SoundSystem::GetSingleton()

}

#endif
/*
*
* �ļ�����	��	PX2ResourceManager.hpp
*
*/

#ifndef PX2RESOURCEMANAGER_HPP
#define PX2RESOURCEMANAGER_HPP

#include "PX2UnityPre.hpp"
#include "PX2TexPackData.hpp"
#include "PX2Runnable.hpp"
#include "PX2ObjectCopyPool.hpp"
#include "PX2ResourceUpdate.hpp"
#include "PX2HashTable.hpp"
#include "PX2FString.hpp"
#include "PX2CURLDownload.hpp"
#include "PX2XMLData.hpp"

namespace PX2
{

	class ResourceManager : public Runnable, public Singleton<ResourceManager>
	{
	public:
		ResourceManager ();
		virtual ~ResourceManager ();

		CURLDownload *GetCURLDownload ();

		virtual void Update (double appSeconds, double elapsedSeconds);

		/// ��Դ����״̬
		enum LoadState
		{
			LS_UNLOADED,
			LS_LOADQUE,
			LS_LOADING,
			LS_LOADED,
			LS_MAX_STATE
		};

		// ����
		void Clear ();
		void ClearRes (const std::string &resPath);
		Object *BlockLoad (const std::string &filename);
		Object *BlockLoadCopy (const std::string &filename);
		Object *BlockLoadShareCopy (const std::string &filename, bool vb, bool ib, 
			bool mi);
		ResHandle BackgroundLoad (const std::string &filename);
		ResHandle BackgroundDoFun (const std::string &funName, BackgroundFun func);
		Object *CheckRes (ResHandle handle);
		bool CheckFun (ResHandle handle);
		LoadState GetResLoadState (ResHandle handle);
		Object *ShareCopyVB_IB (Object *objFrom);
		Object *ShareCopyVB_IB_MI (Object *objFrom);
		Object *ShareCopyMI (Object *objFrom);
		Object *ShareCopy (Object *objFrom, bool vb, bool ib, bool mi);
		
		void Dump (const std::string &filename);
		void BeginDumpDiff ();
		void EndDumpDiff (const std::string &filename);

		void SetUseGarbageCollect (bool use);
		bool IsUseGarbageCollect () const;
		void SetGarbageCollectTime (float seconds);
		float GetGarbageCollectTime () const;

		// folder
		bool CreateFloder (const std::string &parentPath, const std::string &path);
		bool IsFloderExist (const std::string &parentPath, const std::string &path);

		/// ���buffer,�����Android�豸��apk�л�ȡ
		/**
		* ����Ҫ����ʹ��delete1�ͷŻ�õ�buffer
		*/
		bool LoadBuffer (const std::string &filename, int &bufferSize, 
			char* &buffer);
		
		// tex pack
		bool IsTexPack (const std::string &texPackPath);
		bool AddTexPack (const std::string &texPackPath);
		const TexPack &GetTexPack (const std::string &texPackPath);
		const TexPackElement &GetTexPackElement (
			const std::string &texPackPath, const std::string &eleName);

		/// ��ÿ�д·��
		/**
		* ��PC��Ϊ����ǰĿ¼�����ƶ��豸���ɸ��豸API���ء�
		*/
		std::string GetWriteablePath ();
		static const std::string GetResourcePath ();

		// ����ѡ��
		void DDSKeepCompressed (bool keep=true);
		bool IsDDSKeepCompressed ();

		// Save
		bool SaveTex2DPNG (Texture2D *tex2d, const std::string &filename);

		// data version
		/**
		* data version �Ǽ�¼��DataĿ¼��汾��Ϣ���ð汾��Ϣ�Ͱ���һ��
		*/
		bool LoadDataVersionXML (const std::string &filename);
		const ResourceVersionItem *GetDataVersionItem () const;

		// data update version
		/**
		* data update version ��¼�ڿ�д·���У�ֱ���ô��ļ��ķ�ʽ��
		*/
		bool LoadDataUpateVersionXML (const std::string &filename);
		const ResourceVersionItem *GetDataUpdateVersionItem () const;

		// update version
		/**
		* update version �Ǵӷ��������صİ汾��Ϣ���ð汾��Ϣ���򷢲���ʱ��û��
		* �й����º���С�
		*/
		bool LoadUpdateVersionXML (const std::string &filename);
		const ResourceVersionItem *GetUpdateVersionItem () const;

		// versionlist read
		/**
		* ��ȡ��Ӧ�汾�İ汾��Ϣ
		*/
		typedef HashTable<FString, ResourceFileMark, FixedStringHashCoder> VersionListTable;

		bool IsVersionListValued (const std::string &filename);

		bool LoadDataVersionList (const std::string &filename);
		VersionListTable &GetDataVersionList ();
		bool LoadDataUpdateVersionList (const std::string &filename);
		VersionListTable &GetDataUpdateVersionList ();
		bool LoadUpdateVersionList (const std::string &filename);
		VersionListTable &GetUpdateVersionList ();
		bool IsHasUpdate (const std::string &filename, std::string &outUpdatedFilename);
		bool IsHasUpdate (const std::string &filename);

		void SetVersion (const ResourceVersion &version);
		const ResourceVersion &GetVersion () const;

		enum DirType
		{
			DT_WIN,
			DT_ANDROID,
			DT_IOS,
			DT_MAX_TYPE
		};
		// versionlist writes
		/**
		* �ڹ��������ɰ汾��Ϣ
		*/
		void BeginWriteVersionList ();
		void AddVersionFile (const std::string &filename, DirType type);
		void EndWriteVersionList (const std::string &filename);
		void WriteDataList (const std::string &filename, VersionListTable &table);

		// download
		/**
		* fullPath��������·��
		*/
		bool Download (const std::string &fullPath, const std::string &url);

		// ��Դ������ص���������
		void DoResourceUpdateStuffs (const std::string &wwwAddr);
		void SetResourceUpdateCallback (ResourceUpdateStuffsCallback callback);
		
		static void SetDataUpdateServerType (const std::string &type);
		static std::string &GetDataUpdateServerType ();

public_internal:
		struct LoadRecord
		{
			enum RecordType
			{
				RT_OBJECT,
				RT_BUFFER,
				RT_FUN,
				RT_MAX_TYPE
			};

			LoadRecord ();
			~LoadRecord ();

			RecordType TheRecordType;
			BackgroundFun Fun;
			std::string Filename;
			ObjectPtr Obj;
			Pointer1<char> Buffer;
			int BufferSize;
			LoadState State;

			// ����Դ���ü���Ϊ1�󣬳���һ��ʱ�䳤�Ⱥ���Դ����ϵͳ���ա�
			double LastTouchedTime;
		};

		unsigned int RunLoadingThread ();
		void GarbageCollect (double appSeconds, double elapsedSeconds);
		
		// ������Դ·��.��Androidϵͳ�У�Ϊapk����Ŀ¼
		static void SetResourcePath (const std::string &resPath);

		virtual void Run ();

	protected:
		LoadRecord &InsertRecord (const FString &filename, bool isBuffer);
		LoadRecord &InsertRecord (const FString &funName, BackgroundFun fun);
		void _LoadTheRecord (LoadRecord &rec);
		Object *_LoadObject (const std::string &filename);
		bool _LoadBuffer (const std::string &filename, int &bufferSize,
			char* &buffer);
		Texture2D *LoadTexFormOtherImagefile (std::string outExt, 
			int bufferSize, const char*buffer);
		Texture2D *LoadTextureFromDDS (const std::string &filename);
		Texture2D *LoadTextureFromPVRTC(int bufferSize, const char *buffer);
		Texture2D *LoadTextureFromPVRTC_CCZ(int bufferSize, const char *buffer);
		bool GetFileDataFromZip (const std::string &packageName, 
			const std::string &filename, int &bufferSize, char* &buffer);
		void ShareCopyProcess (Node *node, Node *nodeFrom, bool vb, bool ib,
			bool mi);
		void ShareCopyProcess (Renderable *renderable,
			Renderable *renderableFrom, bool vb, bool ib, bool mi);
		void ReadVersionList (FileIO &in, VersionListTable &table);
		void ReadVersionList (BufferIO &in, VersionListTable &table);
		
	private:
		bool mDDSKeepCompressed;
		Mutex *mLoadRecordMutex;
		Mutex *mLoadingDequeMutex;
		Mutex *mTexPacksMutex;
		Thread *mLoadingThread;
		std::deque<LoadRecord *>mLoadingDeque;
		bool mQuitLoading;
		ConditionType mLoadingDequeCondition;

		bool mIsUseGarbageCollect;
		float mGarbageCollectTime;
		float mGarbageUpdateTime;
		typedef HashTable<FString, LoadRecord, FixedStringHashCoder> ResTable;
		typedef ResTable::Element * ResTableIterator;
		Mutex *mResTableMutex;
		ResTable mResTable;

		static TexPack msIvalidTexPack;
		HashTable<FString, TexPack, FixedStringHashCoder> mTexPacks;
		static TexPackElement msIvalidTexPackElement;
		HashTable<FString, TexPackElement, FixedStringHashCoder> mPackElements;

		static std::string msResPath;
		std::string mWriteablePath;

		// curl
		CURLDownload *mCurlDownLoad;

		// data version
		Pointer0<ResourceVersionItem> mDataVersionItem;

		// data update version
		Pointer0<ResourceVersionItem> mDataUpdateVersionItem;

		// udpate version
		Pointer0<ResourceVersionItem> mUpdateVersionItem;

		// version
		ResourceVersion mVersion;

		// version list
		int mEndVersionList;
		std::vector<ResourceFileMark> mVersionListToWrite;
		VersionListTable mDataVersionList; 
		VersionListTable mDataUpdateVersionList; 
		VersionListTable mUpdateVersionList; 
		ResourceUpdateStuffsCallback mResourceUpdateCallback;
		std::string mDataUpdatePath;
		static std::string mDataUpdateServerType;

		// dump
		std::vector<std::string> mBeginDumpDiffFiles;
	};

#include "PX2ResourceManager.inl"

#define PX2_RM ResourceManager::GetSingleton()

}

#endif
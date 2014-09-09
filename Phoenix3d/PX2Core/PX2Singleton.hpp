/*
*
* �ļ�����	��	PX2Singleton.hpp
*
*/

#ifndef PX2SINGLETON_HPP
#define PX2SINGLETON_HPP

#include "PX2Assert.hpp"
#include "PX2Noncopyable.hpp"

namespace PX2
{

	/// ģ�嵥����
	template <typename TYPE>
	class Singleton : private Noncopyable
	{
	public:
		Singleton ()
		{
			assertion(!msSingleton, "msSingleton must be null.");

			int offset = (int)(TYPE*)1 - (int)(Singleton<TYPE>*)(TYPE*)1;
			msSingleton = (TYPE*)((int)this + offset);
		}

		~Singleton ()
		{
			assertion(msSingleton!=0, "msSingleton mustn't be null.");
		}

		static void Set (TYPE *object)
		{
			msSingleton = object;
		}

		static TYPE &GetSingleton ()
		{
			assertion(msSingleton!=0, "msSingleton mustn't be null.");
			return (*msSingleton);
		}

		static TYPE *GetSingletonPtr ()
		{
			return msSingleton;
		}

	private:
		static TYPE *msSingleton;
	};

	template <typename TYPE>
	TYPE *Singleton<TYPE>::msSingleton = 0;

}

#endif
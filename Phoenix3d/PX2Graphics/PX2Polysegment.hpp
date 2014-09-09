/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Polysegment.hpp
*
* �汾		:	1.0 (2011/02/01)
*
* ����		��	more
*
*/

#ifndef PX2POLYSEGMENT_HPP
#define PX2POLYSEGMENT_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Renderable.hpp"

namespace PX2
{

	/// ����ͼ������
	/**
	* ���contiguousΪ�棬����ͼ��Ϊ���ӵ��߶Ρ�������˵��{V0,V1,V2,V3}����ɵ�
	* ����ͼ��Ϊ<V0,V1>,<V1,V2>,��<V2,V3>�������ϣ���߶��Ǳպϵģ����һ������
	* ����͵�һ�������ظ���������˵��{V0,V1,V2,V3=V0}��ɵ�ͼ��Ϊ<V0,V1>,
	* <V1,V2>,��<V2,V0>�����contiguousΪ�٣�����ͼ��Ϊ�߶��С�������˵��{V0,V1,
	* V2,V3}��ɵļ���ͼ��Ϊ<V0,V1>����<V2,V3>��������������£��������������
	* ż������
	*/
	class Polysegment : public Renderable
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(Polysegment);

	public:
		Polysegment (VertexFormat* vformat, VertexBuffer* vbuffer,
			bool contiguous);

		virtual ~Polysegment ();

		/**
		* ����������߶μ���ͼ�Σ�0 <= numSegments <= numVertices-1�����Ϊ�߶�
		* ����0 <= numSegments <= numVertices/2��
		*/
		int GetMaxNumSegments () const;
		void SetNumSegments (int numSegments);
		inline int GetNumSegments () const;

		/**
		* ����߶������ӵģ�����true�����򷵻�false��
		*/
		inline bool GetContiguous () const;

	protected:
		Polysegment () {};
		
		int mNumSegments;
		bool mContiguous;
	};

	PX2_REGISTER_STREAM(Polysegment);
	typedef Pointer0<Polysegment> PolysegmentPtr;
#include "PX2Polysegment.inl"

}

#endif

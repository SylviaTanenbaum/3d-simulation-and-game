
#ifndef __GRIDMAP_H__
#define __GRIDMAP_H__

#include "PX2GamePre.hpp"
#include "HeapNode.h"
#include "BitArray.h"
#include "Point2D.h"


namespace GridMove
{
	const float FIXPOINT_SCALE = 100.0f;
	class CLogicMap;

	//Ѱ·���
	class CNaviPath
	{
		friend class CLogicMap;

		struct stPathPoint
		{
			int x; //������Ļ�ϵ���������
			int y;
			int len; //������ڵ㵽�¸���ľ���
		};
		std::vector<stPathPoint>m_Points;
		CLogicMap *m_pMap;
		unsigned int m_GridUpdateAccum;

	public:
		CNaviPath() : m_pMap(NULL){}
		void Reset(CLogicMap *pmap);
		void Revert();
		void AddPathPoint( int x, int y );
		int  FindNextVisiblePoint( int i );
		Point2D GetPathPoint( int i )
		{ 
			assert( i < (int)m_Points.size() );
			return Point2D(m_Points[i].x, m_Points[i].y); 
		}
		Point2D GetPathGoal()
		{
			assert( (int)m_Points.size() > 1 );
			stPathPoint &pt = m_Points[ m_Points.size()-1 ];
			return Point2D( pt.x, pt.y );
		}
		int GetPathSegLen(int i)
		{
			assert(i<int(m_Points.size())-1);
			return m_Points[i].len;
		}
		int  GetNumPoint(){ return int(m_Points.size()); }
		void LooseGoal( int radius ); //�ı�path, ��path��goal�ں�ԭ��Ŀ�����radius�ĵط�
		void SmoothPath();
		void ComputePathSegLen();
		void LimitPathPoint( int number )
		{
			assert( number >= 2 );
			if( number >= int(m_Points.size()) ) return;

			m_Points.resize( number );
		}

		Point2D MoveOnPath(int &curpt, int &offset, int movelen); //���ص�ǰ�����
		bool IsPointOnPath( const Point2D &pt );
		int  GetPathLength();
		Point2D GetPathPosition(int curpt, int offset);
		bool IsPathOK(int curpt, int offset);

		static bool IsPointInSegment( int x, int y, int x1, int y1, int x2, int y2 );
	};

	class CLogicMap
	{
		friend class CNaviPath;
	public:
		enum MaskBits
		{
			maskDynamic			=   0x7f,   // ��ɫ���赲������+1�� �뿪-1
			maskStatic			=   0x80,   // ��ͼ�����赲
			maskStop            =   0xff,   //  
		};
		enum MaskPathResults
		{
			maskPathArrive      =   0,  //�ѽ��_��
			maskPathFound       =   1,  //�ҵ����Ե��_��·��
			maskPathNear        =   2,  //����Ŀ��
			maskPathFail        =   3,  //����ʧ��
			maskPathError       =   -1, //�e�`
		};
		enum MaskStepResults
		{
			maskStepArrive      =   0,  //���_
			maskStepOnTheWay    =   1,   //��;��
			maskStepObstruct    =   2,   //�����
			maskStepOutstretch  =   3,   //��������
		};

	public:
		CLogicMap();
		~CLogicMap();

		void CreateGraph(int lenghA, int lenghB, int cellsA, int cellsB, unsigned char *pmskbits=NULL);

		bool FindNaviPath( CNaviPath &path, const Point2D &start, const Point2D &end );

		/**
		* �ӿ�ʼ���ƶ��������㣬ֻ�������赲
		* \param start ��ʼ�㣬������Ϊ��λ
		* \param delta �ƶ�ʸ����������Ϊ��λ
		* \return �ƶ��Ľ�����
		*/
		Point2D DoMotion( const Point2D &start, const Point2D &delta );

		/**
		* �����Ƿ��ܹ�ֱ�ߴ�start�ƶ���end
		*/
		bool LineOfSightTest( const Point2D &start, const Point2D &end, int mask=maskStop );
		bool LineOfSightTest1( const Point2D &start, const Point2D &end, int mask=maskStop );
		bool LineOfSightTest2( const Point2D &start, const Point2D &end, int mask=maskStop );

		/**
		* ��������ĵ㣬�ڸ����ҳ����ߵĵ㣬�Ӵ˵�����Χ��ɢ����
		* \return �Ƿ��ܹ��ҵ�
		*/
		bool FindPointWalkable( Point2D &point, int range=50, int mask=maskStatic );
		bool CanWalkPixelCoord( int x, int y, int mask=maskStop );
		bool IsInSameGrid(const Point2D &p1, const Point2D &p2);
		void UpdateMask(int x1, int y1, int x2, int y2, bool b);
		unsigned int GetGridUpdateTime(int x, int y);

		bool CanWalkGridCoord( int x, int y, int mask=maskStop )
		{
			return CanWalk( x, y, mask );
		}

		bool IsPointInMap( const Point2D &point )
		{
			return point.x>=0 && point.x<m_lPlaneWidth && point.y>=0 && point.y<m_lPlaneHeight;
		}

		//�ڰ뾶Ϊradius��ԲȦ����һ������ʹ�����mask(����ˮ��)
		bool FindDirFaceMask( Point2D &point, const Point2D &center, int radius, int mask );

	public:
		int   m_lWidthMasks;
		int   m_lHeightMasks;
		int   m_lMaskPixelWidth;
		int   m_lMaskPixelHeight;
		int   m_lPlaneWidth;
		int   m_lPlaneHeight;
		unsigned char *m_pMaskData;
		unsigned int *m_GridUpdateTime;
		unsigned int m_GridUpdateAccum;

		CPathHeap m_PathHeap;
		BitArray2D *m_pVisitMap;
		std::vector<stPathHeapNode>m_ClosedNodes;

		void TryGotoNeighbour( stPathHeapNode &node, int dx, int dy );

		unsigned char GetGridAttrib( int x, int y )
		{ 
			return m_pMaskData[y*m_lWidthMasks+x]; 
		}

		bool CanWalk( int x, int y, int mask=maskStop )
		{ 
			return (m_pMaskData[y*m_lWidthMasks+x]&mask)==0;
		}

		void CoordPixel2Grid( int &x, int &y )
		{ 
			x/=m_lMaskPixelWidth, y/=m_lMaskPixelHeight; 
		}

		void CoordGrid2Pixel( int &x, int &y )
		{ 
			x = x*m_lMaskPixelWidth+m_lMaskPixelWidth/2;
			y = y*m_lMaskPixelHeight+m_lMaskPixelHeight/2;
		}

		/**
		* �ӿ�ʼ�㵽������֮���ҳ�һ��·��
		* \param path ���ڴ洢���ص�·��
		* \param start ��ʼ�㣬������Ϊ��λ
		* \param end �����㣬������Ϊ��λ
		* \return 0: �ɹ��� 
		*         1�������߼����󣨱����ϴ��ߵ��赲������ȥ�ˣ�
		*         2��Ѱ·�ڵ���ֹ࣬ͣѰ·��
		*         3: ��ʼ���Ŀ�����ͬһ����
		*/
		int FindNaviPath_Internal( CNaviPath &path, const Point2D &start, const Point2D &end );

		//��Ŀ�����Χ��Ŀ���
		bool FindSimplePath_Internal( CNaviPath &path, const Point2D &start, const Point2D &end , int range);
	};
}

#endif
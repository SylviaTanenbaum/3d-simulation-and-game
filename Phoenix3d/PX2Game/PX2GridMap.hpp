
#ifndef _PX2GRIDMAP_HPP_
#define _PX2GRIDMAP_HPP_

#include "PX2Heapnode.hpp"
#include <assert.h>

namespace PX2
{
	const float FIXPOINT_SCALE = 100.0f;

	class BitArray1D
	{
	public:
		BitArray1D( int len ) : m_NumBits(len)
		{
			m_BufLen = (m_NumBits+31)/32;
			m_pData = new unsigned int[m_BufLen];
		}
		~BitArray1D()
		{
			delete[] m_pData;
		}
		void Clear()
		{
			memset( m_pData, 0, m_BufLen*4 );
		}
		int GetBit( int i )
		{
			return (m_pData[i>>5] >> (i&31)) & 1;
		}
		void SetBit( int i, int bit )
		{
			unsigned int &data = m_pData[i>>5];
			int ibit = i&31;
			data = (data & ~(1<<ibit)) | (bit<<ibit);
		}

	private:
		unsigned int *m_pData;
		int m_NumBits;
		int m_BufLen;
	};
	class BitArray2D
	{
	public:
		BitArray2D( int nbitx, int nbity ) : m_nBitX(nbitx), m_nBitY(nbity), m_BitArray(nbitx*nbity)
		{
		}
		~BitArray2D()
		{
		}
		void Clear()
		{
			m_BitArray.Clear();
		}
		int GetBit( int x, int y )
		{
			return m_BitArray.GetBit( y*m_nBitX+x );
		}
		void SetBit( int x, int y, int bit )
		{
			m_BitArray.SetBit( y*m_nBitX+x, bit );
		}

		int GetWidth(){ return m_nBitX; }
		int GetHeight(){ return m_nBitY; }

	private:
		BitArray1D m_BitArray;
		int m_nBitX, m_nBitY;
	};
	class Point2D
	{

	public:

		Point2D(){x=0;y=0;}
		Point2D( int x1, int y1 ) : x(x1), y(y1){}
		Point2D( const Point2D &rhs ) : x(rhs.x), y(rhs.y){}
		Point2D &operator =( const Point2D &rhs ){ x=rhs.x, y=rhs.y; return *this; }
		Point2D operator +( const Point2D &rhs ) const
		{
			return Point2D(x+rhs.x, y+rhs.y);
		}
		Point2D operator -( const Point2D &rhs ) const
		{
			return Point2D(x-rhs.x, y-rhs.y);
		}
		Point2D operator *( const Point2D &rhs ) const
		{
			return Point2D(x*rhs.x, y*rhs.y);
		}
		Point2D operator /( const Point2D &rhs ) const
		{
			return Point2D(x/rhs.x, y/rhs.y);
		}

		Point2D operator *( int scale ) const
		{
			return Point2D(x*scale, y*scale);
		}

		Point2D operator /( int scale ) const
		{
			return Point2D(x/scale, y/scale);
		}

		bool operator==( const Point2D &rhs ) const
		{
			return x==rhs.x && y==rhs.y;
		}

		bool operator!=( const Point2D &rhs ) const
		{
			return x!=rhs.x || y!=rhs.y;
		}

		Point2D &operator +=( const Point2D &rhs )
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		Point2D &operator -=( const Point2D &rhs )
		{
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}

		Point2D &operator *=( float scale )
		{
			x = int(x*scale);
			y = int(y*scale);
			return *this;
		}

		Point2D &operator /=( float scale )
		{
			x = int(x/scale);
			y = int(y/scale);
			return *this;
		}

		int LengthSq(){ return x*x+y*y; }
		int Length(){ return (int)sqrt(double(x*x+y*y)); }

	public:

		int x;
		int y;

	};

	class CLogicMap;

	//Ѱ·���
	class CNaviPath
	{
		friend class CLogicMap;

		struct stPathPoint
		{
			int x; //������Ļ�ϵ���������
			int y;
		};
		std::vector<stPathPoint>m_Points;
		CLogicMap *m_pMap;

	public:
		CNaviPath() : m_pMap(NULL){}
		void Reset( CLogicMap *pmap ){ m_Points.resize(0); m_pMap = pmap; }
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
		int  GetNumPoint(){ return (int)m_Points.size(); }
		void LooseGoal( int radius ); //�ı�path, ��path��goal�ں�ԭ��Ŀ�����radius�ĵط�
		void SmoothPath();
		void LimitPathPoint( int number )
		{
			assert( number >= 2 );
			if( number >= int(m_Points.size()) ) return;

			m_Points.resize( number );
		}

		bool IsPointOnPath( const Point2D &pt );
		int  GetPathLength();

		static bool IsPointInSegment( int x, int y, int x1, int y1, int x2, int y2 );
	};

	class CLogicMap
	{
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

		void CreateGraph(float lenghA, float lenghB, int cellsA, int cellsB);

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
		bool FindPointWalkable( Point2D &point, int range=50 );
		bool CanWalkPixelCoord( int x, int y, int mask=maskStop );
		bool IsInSameGrid(const Point2D &p1, const Point2D &p2);
		bool UpdateMask(int x, int y, bool b);

		bool CanWalkGridCoord( int x, int y, int mask=maskStop )
		{
			return CanWalk( x, y, mask );
		}

		bool IsPointInMap( Point2D &point )
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

		//�ҳ���start��end�ߣ���Զ��ֱ��·��
		bool FindSimplePath_Internal( CNaviPath &path, const Point2D &start, const Point2D &end );
	};
}

#endif
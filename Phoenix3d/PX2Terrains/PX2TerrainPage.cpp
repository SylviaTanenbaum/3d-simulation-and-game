/*
*
* �ļ�����	��	PX2TerrainPage.cpp
*
*/


#include "PX2TerrainPage.hpp"
#include "PX2EditTerrainMaterial.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, TriMesh, TerrainPage);
PX2_IMPLEMENT_STREAM(TerrainPage);
PX2_IMPLEMENT_FACTORY(TerrainPage);
PX2_IMPLEMENT_DEFAULT_NAMES(TriMesh, TerrainPage);

//----------------------------------------------------------------------------
TerrainPage::TerrainPage (int size,	float* heights, const Float2& origin, 
	float spacing)
	:
mSize(size),
	mSizeM1(size - 1),
	mHeights(heights),
	mOrigin(origin),
	mSpacing(spacing)
{
	// size = 2^p + 1, p <= 7
	assertion(size ==  3 || size ==  5 || size ==   9 || size == 17
		|| size == 33 || size == 65 || size == 129, "Invalid page size\n");

	mInvSpacing = 1.0f/mSpacing;

	SetRenderLayer(Renderable::RL_TERRAIN);
}
//----------------------------------------------------------------------------
TerrainPage::~TerrainPage ()
{
	delete1(mHeights);
}
//----------------------------------------------------------------------------
float TerrainPage::GetHeight (float x, float y) const
{
	float xGrid = (x - mOrigin[0])*mInvSpacing;
	if (xGrid < 0.0f || xGrid >= (float)mSizeM1)
	{
		// ��λ�ڵ���ҳ��
		return 0.0f;
	}

	float yGrid = (y - mOrigin[1])*mInvSpacing;
	if (yGrid < 0.0f || yGrid >= (float)mSizeM1)
	{
		// ��λ���ٵ���ҳ��
		return 0.0f;
	}

	float fCol = Mathf::Floor(xGrid);
	int iCol = (int)fCol;
	float fRow = Mathf::Floor(yGrid);
	int iRow = (int)fRow;

	int index = iCol + mSize*iRow;
	float dx = xGrid - fCol;
	float dy = yGrid - fRow;
	float h00, h10, h01, h11, height;

	if ((iCol & 1) == (iRow & 1))
	{
		float diff = dx - dy;
		h00 = mHeights[index];
		h11 = mHeights[index + 1 + mSize];
		if (diff > 0.0f)
		{
			h10 = mHeights[index + 1];
			height = (1.0f - diff - dy)*h00 + diff*h10 + dy*h11;
		}
		else
		{
			h01 = mHeights[index + mSize];
			height = (1.0f + diff - dx)*h00 - diff*h01 + dx*h11;
		}
	}
	else
	{
		float sum = dx + dy;
		h10 = mHeights[index + 1];
		h01 = mHeights[index + mSize];
		if (sum <= 1.0f)
		{
			h00 = mHeights[index];
			height = (1.0f - sum)*h00 + dx*h10 + dy*h01;
		}
		else
		{
			h11 = mHeights[index + 1 + mSize];
			height = (sum - 1.0f)*h11 + (1.0f - dy)*h10 + (1.0f - dx)*h01;
		}
	}

	return height;
}
//----------------------------------------------------------------------------
void TerrainPage::SetJunglerFrequency (float fre)
{
	for (int i=0; i<(int)mJunglers.size(); i++)
	{
		mJunglers[i]->SetJunglerFrequency(fre);
	}
}
//----------------------------------------------------------------------------
void TerrainPage::SetJunglerStrength (float strength)
{
	for (int i=0; i<(int)mJunglers.size(); i++)
	{
		mJunglers[i]->SetJunglerStrength(strength);
	}
}
//----------------------------------------------------------------------------
void TerrainPage::AddJunglers (Texture2D *tex, std::vector<JObj> objs)
{
	if (0 == (int)objs.size())
		return;

	JunglerPtr junglerP = mJunglersMap[tex];
	Jungler *jungler = junglerP;

	if (jungler)
	{
		jungler->Add(objs);
	}
	else
	{
		jungler = new0 Jungler(tex, 1000, Jungler::JT_PLANE);
		jungler->Add(objs);

		mJunglers.push_back(jungler);
		mJunglersMap[tex] = jungler;
	}
}
//----------------------------------------------------------------------------
void TerrainPage::RemoveJunglers (Texture2D *tex, APoint center, float radius, 
	int num)
{
	if (0 == (int)mJunglers.size())
		return;

	if (0 == tex)
	{
		std::vector<JunglerPtr>::iterator it = mJunglers.begin();
		for (; it!=mJunglers.end(); it++)
		{
			RemoveJunglerPoints((*it), center, radius, num);
		}
	}
	else
	{
		JunglerPtr junglerP = mJunglersMap[tex];
		Jungler *jungler = junglerP;

		if (jungler)
		{
			RemoveJunglerPoints(jungler, center, radius, num);
		}
	}

	std::vector<JunglerPtr>::iterator it = mJunglers.begin();
	for (; it!=mJunglers.end();)
	{
		if (0==(*it)->GetNum())
		{
			mJunglersMap.erase((*it)->GetTexture());
			it = mJunglers.erase(it);
		}
		else
		{
			it++;
		}
	}
}
//----------------------------------------------------------------------------
void TerrainPage::RemoveJunglerPoints (Jungler *jungler, APoint center, float radius, 
	int num)
{
	if (!jungler)
		return;

	// ��Χ�ڸ���
	std::vector<int> indexs;
	for (int i=0; i<jungler->GetNum(); i++)
	{
		const APoint &pos = jungler->GetPos(i);
		AVector dir = pos - center;
		if (dir.Length() < radius)
		{
			indexs.push_back(i);
		}
	}

	std::vector<int> indexsRemoves;
	for (int i=0; i<(int)indexs.size(); i++)
	{
		float fRand = (float)num/(float)indexsRemoves.size();
		float fR = Mathf::IntervalRandom(0.0f, 1.0f);

		if (fR <= fRand)
		{
			indexsRemoves.push_back(indexs[i]);
		}
	}

	jungler->Remove(indexsRemoves);
}
//----------------------------------------------------------------------------
void TerrainPage::GetVisibleSet (Culler& culler, bool noCull)
{
	TriMesh::GetVisibleSet(culler, noCull);

	for (int i=0; i<(int)mJunglers.size(); i++)
	{
		culler.Insert(mJunglers[i]);
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// �־û�֧��
//----------------------------------------------------------------------------
TerrainPage::TerrainPage (LoadConstructor value)
	:
TriMesh(value),
	mSize(0),
	mSizeM1(0),
	mHeights(0),
	mOrigin(Float2(0.0f, 0.0f)),
	mSpacing(0.0f),
	mInvSpacing(0.0f)
{
}
//----------------------------------------------------------------------------
void TerrainPage::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	TriMesh::Load(source);
	PX2_VERSION_LOAD(source);

	source.Read(mSize);
	int numVertices = mSize*mSize;
	source.ReadVR(numVertices, mHeights);
	source.ReadAggregate(mOrigin);
	source.Read(mSpacing);

	mSizeM1 = mSize - 1;
	mInvSpacing = 1.0f/mSpacing;

	int numJunglers = 0;
	source.Read(numJunglers);
	if (numJunglers > 0)
	{
		mJunglers.resize(numJunglers);
		source.ReadPointerVV(numJunglers, &mJunglers[0]);
	}

	PX2_END_DEBUG_STREAM_LOAD(TerrainPage, source);
}
//----------------------------------------------------------------------------
void TerrainPage::Link (InStream& source)
{
	TriMesh::Link(source);

	mJunglersMap.clear();
	for (int i=0; i<(int)mJunglers.size(); i++)
	{
		source.ResolveLink(mJunglers[i]);
		mJunglersMap.insert(std::pair<Texture2D*, JunglerPtr>(
			mJunglers[i]->GetTexture(), mJunglers[i]));
	}
}
//----------------------------------------------------------------------------
void TerrainPage::PostLink ()
{
	TriMesh::PostLink();
}
//----------------------------------------------------------------------------
bool TerrainPage::Register (OutStream& target) const
{
	if (TriMesh::Register(target))
	{
		for (int i=0; i<(int)mJunglers.size(); i++)
		{
			target.Register(mJunglers[i]);
		}

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void TerrainPage::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	TriMesh::Save(target);
	PX2_VERSION_SAVE(target);

	target.Write(mSize);
	int numVertices = mSize*mSize;
	target.WriteN(numVertices, mHeights);
	target.WriteAggregate(mOrigin);
	target.Write(mSpacing);

	int numJunglers = (int)mJunglers.size();
	target.Write(numJunglers);
	for (int i=0; i<numJunglers; i++)
	{
		target.WritePointer(mJunglers[i]);
	}

	PX2_END_DEBUG_STREAM_SAVE(TerrainPage, target);
}
//----------------------------------------------------------------------------
int TerrainPage::GetStreamingSize (Stream &stream) const
{
	int size = TriMesh::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);
	size += sizeof(mSize);
	size += mSize*mSize*sizeof(mHeights[0]);
	size += sizeof(mOrigin);
	size += sizeof(mSpacing);
	int numJuns = (int)mJunglers.size();
	size += sizeof(numJuns);
	if (size > 0)
	{
		size += numJuns * PX2_POINTERSIZE(mJunglers[0]);
	}

	return size;
}
//----------------------------------------------------------------------------

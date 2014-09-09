/*
*
* �ļ�����	��	PX2Picker.cpp
*
*/

#include "PX2Picker.hpp"
#include "PX2SwitchNode.hpp"
#include "PX2TriMesh.hpp"
#include "PX2IntrLine3Triangle3.hpp"
#include "PX2VertexBufferAccessor.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
Picker::Picker (bool isDoMovPickCall, int pickInfo)
:
mIsDoMovPickCall(isDoMovPickCall),
mPickInfo(pickInfo),
mOrigin(APoint::ORIGIN),
mDirection(AVector::ZERO),
mTMin(0.0f),
mTMax(0.0f)
{
}
//----------------------------------------------------------------------------
Picker::~Picker ()
{
}
//----------------------------------------------------------------------------
void Picker::Execute (Movable* scene, const APoint& origin,
					  const AVector& direction, float tmin, float tmax)
{
#ifdef _DEBUG
	if (tmin == -Mathf::MAX_REAL)
	{
		assertion(tmax == Mathf::MAX_REAL, "Invalid inputs.\n");
	}
	else
	{
		assertion(tmin == 0.0f && tmax > 0.0f, "Invalid inputs.\n");
	}
#endif

	mOrigin = origin;
	mDirection = direction;
	mTMin = tmin;
	mTMax = tmax;
	Records.clear();
	bool hasMeshPicked = false;
	ExecuteRecursive(scene, hasMeshPicked);
}
//----------------------------------------------------------------------------
const PickRecord& Picker::GetClosestToZero () const
{
	if (Records.size() == 0)
	{
		return GetInvalid();
	}

	float closest = Mathf::FAbs(Records[0].T);
	int index = 0;
	const int numRecords = (int)Records.size();
	for (int i = 1; i < numRecords; ++i)
	{
		float tmp = Mathf::FAbs(Records[i].T);
		if (tmp < closest)
		{
			closest = tmp;
			index = i;
		}
	}
	return Records[index];
}
//----------------------------------------------------------------------------
const PickRecord& Picker::GetClosestNonnegative () const
{
	if (Records.size() == 0)
	{
		return GetInvalid();
	}

	// ��õ�һ���Ǹ���ֵ
	float closest = Mathf::MAX_REAL;
	int index;
	const int numRecords = (int)Records.size();
	for (index = 0; index < numRecords; ++index)
	{
		if (Records[index].T >= 0.0f)
		{
			closest = Records[index].T;
			break;
		}
	}
	if (index == numRecords)
	{
		// ����ֵ���Ǹ���
		return GetInvalid();
	}

	for (int i = index + 1; i < numRecords; ++i)
	{
		if (0.0f <= Records[i].T && Records[i].T < closest)
		{
			closest = Records[i].T;
			index = i;
		}
	}
	return Records[index];
}
//----------------------------------------------------------------------------
const PickRecord& Picker::GetClosestNonpositive () const
{
	if (Records.size() == 0)
	{
		return GetInvalid();
	}

	float closest = -Mathf::MAX_REAL;
	int index;
	const int numRecords = (int)Records.size();
	for (index = 0; index < numRecords; index++)
	{
		if (Records[index].T <= 0.0f)
		{
			closest = Records[index].T;
			break;
		}
	}
	if (index == numRecords)
	{
		// All values are positive.
		return GetInvalid();
	}

	for (int i = index + 1; i < numRecords; ++i)
	{
		if (closest < Records[i].T && Records[i].T <= 0.0f)
		{
			closest = Records[i].T;
			index = i;
		}
	}
	return Records[index];
}
//----------------------------------------------------------------------------
void Picker::ExecuteRecursive (Movable* object, bool &hasMeshPicked)
{
	if (object)
	{
		if (!object->IsDoPick())
			return;

		if (!object->IsShow() && !object->IsPickIngoreCullingMode())
			return;
	}

	Triangles* mesh = DynamicCast<Triangles>(object);
	if (mesh)
	{
		if (!mesh->GetVertexBuffer())
			return;

		if (mesh->WorldBound.TestIntersection(mOrigin, mDirection, mTMin, mTMax))
		{
			// �����ߴ���������ϵת����ģ������ϵ��
			APoint ptmp = mesh->WorldTransform.Inverse()*mOrigin;
			Vector3f modelOrigin(ptmp[0], ptmp[1], ptmp[2]);

			AVector vtmp = mesh->WorldTransform.Inverse()*mDirection;
			Vector3f modelDirection(vtmp[0], vtmp[1], vtmp[2]);

			Line3f line(modelOrigin, modelDirection);

			// ���ʷ�λ����
			VertexBufferAccessor vba(mesh);

			int numTriangles = mesh->GetNumTriangles();
			for (int i = 0; i < numTriangles; ++i)
			{
				int v0, v1, v2;
				if (!mesh->GetTriangle(i, v0, v1, v2))
				{
					continue;
				}

				Vector3f vertex0 = vba.Position<Vector3f>(v0);
				Vector3f vertex1 = vba.Position<Vector3f>(v1);
				Vector3f vertex2 = vba.Position<Vector3f>(v2);
				Triangle3f triangle(vertex0, vertex1, vertex2);

				IntrLine3Triangle3f calc(line, triangle);
				if (calc.Find() && mTMin <= calc.GetLineParameter()
					&&  calc.GetLineParameter() <= mTMax)
				{
					PickRecord record;
					record.Intersected = mesh;
					record.T = calc.GetLineParameter();
					record.Triangle = i;
					record.Bary[0] = calc.GetTriBary0();
					record.Bary[1] = calc.GetTriBary1();
					record.Bary[2] = calc.GetTriBary2();
					Records.push_back(record);

					if (mIsDoMovPickCall)
					{
						hasMeshPicked = true;
						mesh->OnPicked(mPickInfo);
					}
				}
			}
		}
		else
		{
			if (mIsDoMovPickCall)
				mesh->OnNotPicked(mPickInfo);
		}
		return;
	}

	SwitchNode* switchNode = DynamicCast<SwitchNode>(object);
	if (switchNode)
	{
		bool newHasChildPicked = false;

		int activeChild = switchNode->GetActiveChild();
		if (activeChild != SwitchNode::SN_INVALID_CHILD)
		{
			if (switchNode->WorldBound.TestIntersection(mOrigin, mDirection, mTMin, mTMax))
			{
				Movable* child = switchNode->GetChild(activeChild);
				if (child)
				{
					ExecuteRecursive(child, newHasChildPicked);
				}

				if (newHasChildPicked)
				{
					hasMeshPicked = true;
				}

				if (mIsDoMovPickCall)
				{
					if (hasMeshPicked)
					{
						switchNode->OnPicked(mPickInfo);
					}
					else
					{
						switchNode->OnNotPicked(mPickInfo);
					}
				}
			}
			else
			{
				if (mIsDoMovPickCall)
					switchNode->OnNotPicked(mPickInfo);
			}
		}
		return;
	}

	Node* node = DynamicCast<Node>(object);
	if (node)
	{
		bool newHasChildPicked = false;
		if (node->WorldBound.TestIntersection(mOrigin, mDirection, mTMin, mTMax))
		{
			Movable *movPriority = 0;
			if (node->IsDoPickPriority())
			{
				for (int i=0; i<node->GetNumChildren(); i++)
				{
					Movable *mov = node->GetChild(i);
					if (mov && mov->IsNotPickedParentChildrenNotPicked())
						movPriority = mov;
				}
			}

			// �����ȼ��
			bool doLastPick = false;
			if (movPriority)
			{
				ExecuteRecursive (movPriority, doLastPick);		
			}
			else
			{
				doLastPick = true;
			}

			if (doLastPick)
			{
				for (int i = 0; i < node->GetNumChildren(); ++i)
				{
					Movable* child = node->GetChild(i);
					if (child && child!=movPriority)
					{
						ExecuteRecursive(child, newHasChildPicked);
					}
				}

				if (newHasChildPicked)
				{
					hasMeshPicked = true;
				}

				if (mIsDoMovPickCall)
				{
					if (newHasChildPicked)
					{
						node->OnPicked(mPickInfo);
					}
					else
					{
						node->OnNotPicked(mPickInfo);
					}
				}
			}
		}
		else
		{
			if (mIsDoMovPickCall)
				node->OnNotPicked(mPickInfo);
		}
	}
}
//----------------------------------------------------------------------------
const PickRecord &Picker::GetInvalid()
{
	static PickRecord pr;
	return pr;
}
//----------------------------------------------------------------------------
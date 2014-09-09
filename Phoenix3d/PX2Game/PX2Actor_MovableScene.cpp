/*
*
* �ļ�����	��	PX2Actor_Movable.cpp
*
*/

#include "PX2Actor.hpp"
#include "PX2Scene.hpp"
#include "PX2ResourceManager.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
void Actor::SetMovableFilename (const std::string &filename, bool shareVIM)
{
	mIsShareVIM = shareVIM;

	mMoveableFilename = filename;

	Object *obj = 0;
	
	if (mIsShareVIM)
	{
		obj = PX2_RM.BlockLoadShareCopy(filename, true, true, false);
	}
	else
	{
		obj = PX2_RM.BlockLoadCopy(filename);
	}

	Movable *mov = DynamicCast<Movable>(obj);
	if (mov)
	{
		SetMovable(mov);
	}
}
//----------------------------------------------------------------------------
void Actor::SetMovable (Movable *movable)
{
	if (mScene && mMovable)
	{
		mScene->GetSceneNode()->DetachChild(mMovable);
	}

	mMovable = movable;

	mMovable->LocalTransform.SetScale(mScale);
	mMovable->LocalTransform.SetRotate(Matrix3f().MakeEulerXYZ(
		mRotation.X(), mRotation.Y(), mRotation.Z()));
	mMovable->LocalTransform.SetTranslate(mPosition);

	mMovable->Show(mIsVisible);

	if (mScene && mMovable)
	{
		mScene->GetSceneNode()->AttachChild(mMovable);
	}

	Node *node = DynamicCast<Node>(mMovable);
	if (node)
	{
		for (int i=0; i<node->GetNumChildren(); i++)
		{
			Renderable *renderable = DynamicCast<Renderable>(node->GetChild(i));
			if (renderable)
			{
				renderable->SetUpdatePriority(-1);
			}
		}
	}
}
//----------------------------------------------------------------------------
void Actor::ShowHelpMovable (bool show)
{
	mIsShowHelpMovable = show;

	if (mHelpMovable)
	{
		if (mIsShowHelpMovable)
		{
			mHelpMovable->Culling = Movable::CULL_DYNAMIC;
		}
		else
		{
			mHelpMovable->Culling = Movable::CULL_ALWAYS;
		}
	}
}
//----------------------------------------------------------------------------
void Actor::SetHelpMovable (Movable *movable)
{
	mHelpMovable = movable;

	mHelpMovable->LocalTransform.SetTranslate(mPosition);

	if (!mIsVisible)
	{
		mHelpMovable->Culling = Movable::CULL_ALWAYS;
	}
	else
	{
		mHelpMovable->Culling = Movable::CULL_DYNAMIC;
	}
}
//----------------------------------------------------------------------------
APoint Actor::GetAnchorPos (const std::string &name)
{
	if (!mMovable)
		return APoint::ORIGIN;

	Movable *mov = DynamicCast<Movable>(mMovable->GetObjectByName(name));
	if (mov)
	{
		return mov->WorldTransform.GetTranslate();
	}

	return APoint::ORIGIN;
}
//----------------------------------------------------------------------------
Node *Actor::GetAnchor (const std::string &name)
{
	if (!mMovable)
		return 0;

	return DynamicCast<Node>(mMovable->GetObjectByName(name));
}
//----------------------------------------------------------------------------
void Actor::SetVisible (bool visible)
{
	mIsVisible = visible;

	if (mMovable)
	{
		if (!mIsVisible)
			mMovable->Culling = Movable::CULL_ALWAYS;
		else
			mMovable->Culling = Movable::CULL_DYNAMIC;
	}
}
//----------------------------------------------------------------------------
void Actor::SetTransparent (float alpha)
{
	mActorTransparent = alpha;
}
//----------------------------------------------------------------------------
void Actor::SetScene (Scene *scene)
{
	if (mScene == scene)
		return;

	if (scene)
	{
		Node *sceneNode = scene->GetSceneNode();

		if (sceneNode)
		{
			double appTime = GetTimeInSeconds();

			if (mMovable)
			{
				sceneNode->AttachChild(mMovable);
				//mMovable->Update(appTime);
			}

			if (mHelpMovable)
			{
				sceneNode->AttachChild(mHelpMovable);
				//mHelpMovable->Update(appTime);
			}
		}
	}
	else
	{
		if (mScene)
		{
			Node *sceneNode = mScene->GetSceneNode();

			if (sceneNode)
			{
				if (mMovable)
				{
					sceneNode->DetachChild(mMovable);
				}

				if (mHelpMovable)
				{
					sceneNode->DetachChild(mHelpMovable);
				}
			}
		}
	}

	mScene = scene;
}
//----------------------------------------------------------------------------
void Actor::CalLights ()
{
}
//----------------------------------------------------------------------------
void Actor::SetSceneContainer (void *container)
{
	mSceneContainer = container;
}
//----------------------------------------------------------------------------
void Actor::SetSceneContainerIndex (int index)
{
	mSceneContainerIndex = index;
}
//----------------------------------------------------------------------------
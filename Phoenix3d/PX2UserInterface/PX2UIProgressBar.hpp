/*
*
* �ļ�����	��	PX2UIProgressBar.hpp
*
*/

#ifndef PX2UIPROGRESSBAR_HPP
#define PX2UIPROGRESSBAR_HPP

#include "PX2UIPre.hpp"
#include "PX2UIFrame.hpp"
#include "PX2UIPicBox.hpp"
#include "PX2Size.hpp"
#include "PX2UIProgressBarCtrl.hpp"

namespace PX2
{

	class UIProgressBar : public UIFrame
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_PROPERTY;
		PX2_DECLARE_STREAM(UIProgressBar);

	public:
		UIProgressBar ();
		virtual ~UIProgressBar ();

		void SetBackPicBox (UIPicBox *picBox);
		void SetProgressPicBox (UIPicBox *picBox);
		void SetOverPicBox (UIPicBox *picBox);
		UIPicBox *GetBackPicBox ();
		UIPicBox *GetProgressPicBox ();
		UIPicBox *GetOverPicBox ();

		void SetSize (float width, float height);
		void SetSize (const Sizef &size);
		float GetWidth () const;
		float GetHeight () const;
		const Sizef &GetSize () const;

		// 0-1.0f
		void SetProgress (float progress, bool useCallback=true);
		float GetProgress () const;

		void SetProgressAnimInit(float progress);
		void SetProgressAnim (float progress);

		void SetProgressAnimSpeed (float speed);
		float GetProgressAnimSpeed ();

		UIProgressBarCtrl *GetProgressBarCtrl ();

	protected:
		virtual void UpdateWorldData (double applicationTime);

		virtual void OnChildPicked (int info, Movable *child);
		virtual void OnNotPicked (int info);

		UIPicBoxPtr mBackPicBox;
		UIPicBoxPtr mProgressPicBox;
		UIPicBoxPtr mOverPicBox;
		Sizef mSize;
		float mProgress;
		UIProgressBarCtrlPtr mPBCtrl;
	};

	PX2_REGISTER_STREAM(UIProgressBar);
	typedef Pointer0<UIProgressBar> UIProgressBarPtr;

#include "PX2UIProgressBar.inl"

}

#endif
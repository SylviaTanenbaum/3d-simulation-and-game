/*
*
* �ļ�����	��	PX2UICheckButton.hpp
*
*/

#ifndef PX2UICHECKBUTTON_HPP
#define PX2UICHECKBUTTON_HPP

#include "PX2UIButtonBase.hpp"

namespace PX2
{

	class UICheckButton : public UIButtonBase
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_PROPERTY;
		PX2_DECLARE_STREAM(UICheckButton);

	public:
		UICheckButton ();
		virtual ~UICheckButton ();

		virtual void Enable (bool enable);

		virtual void OnEvent (Event *event);

		void Check (bool check);
		bool IsCheck () const;

		void OnCheck ();
		void OnDisCheck ();

	protected:
		virtual void UpdateWorldData (double applicationTime);
		virtual void OnChildUIAfterPicked (int info, Movable *child);
		virtual void OnNotPicked (int info);
	};

	PX2_REGISTER_STREAM(UICheckButton);
	typedef Pointer0<UICheckButton> UICheckButtonPtr;

}

#endif
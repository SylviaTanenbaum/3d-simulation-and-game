/*
*
* �ļ�����	��	PX2Notification.cpp
*
*/

#include "PX2Notification.hpp"
#include <typeinfo>
using namespace PX2;

//----------------------------------------------------------------------------
Notification::Notification()
{
}
//----------------------------------------------------------------------------
std::string Notification::GetTypeName() const
{
	return typeid(*this).name();
}
//----------------------------------------------------------------------------
Notification::~Notification()
{
}
//----------------------------------------------------------------------------
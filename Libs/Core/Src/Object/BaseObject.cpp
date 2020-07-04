// Copyright 2015-2020 Piperift - All rights reserved

#include "Object/BaseObject.h"

#include "Object/Object.h"
#include "Reflection/TClass.h"


Class* BaseObject::GetClass() const
{
	const auto* thisObj = static_cast<const Object*>(this);
	if (thisObj)
		return thisObj->GetClass();
	return nullptr;
}

Ptr<Object> BaseObject::Self() const
{
	const auto* thisObj = static_cast<const Object*>(this);
	if (thisObj)
		return thisObj->Self();
	return {};
}

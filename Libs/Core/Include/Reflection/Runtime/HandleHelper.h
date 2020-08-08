// Copyright 2015-2020 Piperift - All rights reserved
#pragma once

#include "CoreTypes.h"
#include "Object/BaseObject.h"
#include "Reflection/Runtime/ClassHandle.h"


namespace VCLang::Refl
{
	class HandleHelper
	{
	public:
		// #TODO: Move to TClass
		static eastl::shared_ptr<ClassHandle> CreateClassHandle(const Ptr<BaseObject>& instance)
		{
			return eastl::make_shared<ClassHandle>(instance);
		}
	};
}	 // namespace VCLang::Refl

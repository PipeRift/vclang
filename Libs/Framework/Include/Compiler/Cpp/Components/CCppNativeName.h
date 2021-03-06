// Copyright 2015-2020 Piperift - All rights reserved
#pragma once

#include "AST/Tree.h"

#include <Object/Struct.h>


namespace Rift
{
	struct CCppNativeName : public Struct
	{
		STRUCT(CCppNativeName, Struct)

		String codeName;

		CCppNativeName(String codeName) : codeName(codeName) {}
	};
}    // namespace Rift

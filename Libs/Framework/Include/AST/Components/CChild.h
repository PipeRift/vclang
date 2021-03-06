// Copyright 2015-2020 Piperift - All rights reserved
#pragma once

#include <AST/Types.h>
#include <Object/Struct.h>


namespace Rift
{
	struct CChild : public Struct
	{
		STRUCT(CChild, Struct)

		PROP(AST::Id, parent)
		AST::Id parent = AST::NoId;
	};
}    // namespace Rift

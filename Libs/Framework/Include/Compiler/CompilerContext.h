// Copyright 2015-2020 Piperift - All rights reserved

#pragma once

#include "Compiler/CompilerConfig.h"
#include "Module.h"

#include <CoreObject.h>
#include <Profiler.h>
#include <Reflection/Reflection.h>


namespace Rift::Compiler
{
	struct CompileError : public Struct
	{
		STRUCT(CompileError, Struct)

		PROP(String, text)
		String text;
	};


	struct Context : public Struct
	{
		STRUCT(Context, Struct)

		AST::Tree& ast;
		Config config;
		TArray<CompileError> errors;


		Context(AST::Tree& ast) : ast{ast} {}

		// Errors
		void AddError(StringView str);
		bool HasErrors() const
		{
			return errors.Size() > 0;
		}
	};
}    // namespace Rift::Compiler

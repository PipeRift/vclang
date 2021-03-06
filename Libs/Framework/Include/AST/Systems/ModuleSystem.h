// Copyright 2015-2020 Piperift - All rights reserved
#pragma once


namespace Rift::AST
{
	struct Tree;
}

namespace Rift::ModuleSystem
{
	void Init(AST::Tree& ast);
	void Run(AST::Tree& ast);

	void ScanModuleAssets(AST::Tree& ast);
}    // namespace Rift::ModuleSystem

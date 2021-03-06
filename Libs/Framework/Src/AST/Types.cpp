// Copyright 2015-2020 Piperift - All rights reserved

#include "AST/Types.h"

#include "AST/Serialization.h"

#include <Serialization/Contexts.h>


namespace Rift::Serl
{
	void Read(Serl::ReadContext& ct, AST::Id& val)
	{
		auto* astCt = dynamic_cast<ASTReadContext*>(&ct);
		if (EnsureMsg(astCt, "Serializing an AST::Id without an ASTReadContext"))
		{
			u32 dataId;
			astCt->Serialize(dataId);
			val = astCt->GetASTIds()[dataId];
		}
	}

	void Write(Serl::WriteContext& ct, AST::Id val)
	{
		auto* astCt = dynamic_cast<ASTWriteContext*>(&ct);
		if (EnsureMsg(astCt, "Serializing an AST::Id without an ASTWriteContext"))
		{
			const u32 dataId = astCt->GetASTIdToIndexes()[val];
			astCt->Serialize(dataId);
		}
	}
}    // namespace Rift::Serl

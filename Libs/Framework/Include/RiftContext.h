// Copyright 2015-2020 Piperift - All rights reserved

#pragma once

#include "Module.h"

#include <Context.h>


namespace Rift
{
	/**
	 * A solution represents an open project and all its build dependencies.
	 */
	// NOTE: Should this be removed?
	class RiftContext : public Context
	{
		CLASS(RiftContext, Context)
	};
}    // namespace Rift

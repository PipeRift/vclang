// Copyright 2015-2019 Piperift - All rights reserved

#pragma once

#include "CoreStruct.h"


class Container : public Struct
{
	STRUCT(Container, Struct)

	P(String, path, Transient);

	P(FName, name);
};

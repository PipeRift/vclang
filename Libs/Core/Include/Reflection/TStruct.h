// Copyright 2015-2020 Piperift - All rights reserved
#pragma once

#include "Reflection/StructType.h"
#include "StructType.h"
#include "TProperty.h"

#include <EASTL/type_traits.h>



/** TStruct will be specialized for each type at compile time and store
 * the metadata for that type
 */
template <typename Type>
class TStruct : public StructType
{
	static_assert(eastl::is_convertible<Type, Struct>::value, "Type does not inherit Struct!");

private:
	static TStruct _struct;


public:
	TStruct() : StructType()
	{
		Type::__meta_Registry();
		Type::__meta_RegistryProperties();
	}

	virtual BaseStruct* New() const override
	{
		return new Type();
	}


	static TStruct* GetStatic()
	{
		return &_struct;
	}
};

template <typename Type>
TStruct<Type> TStruct<Type>::_struct{};
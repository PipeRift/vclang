// Copyright 2015-2020 Piperift - All rights reserved
#pragma once

#include <Platform/Platform.h>
#include <Reflection/Registry/NativeTypeBuilder.h>
#include <Serialization/ContextsFwd.h>

#include <entt/entt.hpp>


namespace Rift
{
	namespace AST
	{
		enum class Id : u32
		{
		};

		constexpr entt::null_t NoId = entt::null;
	}    // namespace AST

	namespace Serl
	{
		void Read(Serl::ReadContext& ct, AST::Id& val);
		void Write(Serl::WriteContext& ct, AST::Id val);
	}    // namespace Serl
}    // namespace Rift

REFLECT_NATIVE_TYPE(Rift::AST::Id);


namespace entt
{
	// template <>
	// struct entt_traits<Rift::AST::Id> : public entt_traits<Rift::u32>
	//{};
}    // namespace entt


namespace Rift::AST
{
	using VersionType = entt::entt_traits<Id>::version_type;

	template <typename... Type>
	using TExclude = entt::exclude_t<Type...>;
}    // namespace Rift::AST


constexpr bool IsNone(Rift::AST::Id id)
{
	return id == Rift::AST::NoId;
}

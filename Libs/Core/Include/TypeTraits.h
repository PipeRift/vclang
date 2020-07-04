// Copyright 2015-2020 Piperift - All rights reserved
#pragma once

#include <EASTL/type_traits.h>


template <typename T, typename = void>
struct IsDefined
{
	static constexpr bool value = false;
};

template <typename T>
struct IsDefined<T, decltype(typeid(T), void())>
{
	static constexpr bool value = true;
};


/** SIZE SELECTORS */

template <class T, size_t size>
struct IsSmallerType : eastl::integral_constant<bool, (sizeof(T) <= size)>
{
};

template <class T, size_t size>
struct IsBiggerType : eastl::integral_constant<bool, (sizeof(T) > size)>
{
};


#define EnableIfSmallerType(size) typename = eastl::enable_if<IsSmallerType<T, size>::value>
#define EnableIfNotSmallerType(size) typename = eastl::enable_if<!IsSmallerType<T, size>::value>

#define EnableIfBiggerType(size) typename = eastl::enable_if<IsBiggerType<T, size>::value>
#define EnableIfNotBiggerType(size) typename = eastl::enable_if<!IsBiggerType<T, size>::value>

#define EnableIfPassByValue(T) \
	typename = eastl::enable_if < IsSmallerType<T, sizeof(size_t)>::value && eastl::is_copy_constructible<T>::type >
#define EnableIfNotPassByValue(T) \
	typename = eastl::enable_if<!(IsSmallerType<T, sizeof(size_t)>::value && eastl::is_copy_constructible<T>::type)>

#define EnableIfAll typename = void


template <bool B, class T = void>
using EnableIf = eastl::enable_if<B, T>;

template <bool B, class T = void>
using DisableIf = eastl::disable_if<B, T>;


template <bool B, class T = void>
using EnableIfT = eastl::enable_if_t<B, T>;

template <bool B, class T = void>
using DisableIfT = eastl::disable_if_t<B, T>;

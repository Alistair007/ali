#pragma once

#include <iostream>
#include <vector>
#include <type_traits>

#define _ALI_BEGIN namespace ali{
#define _ALI_END }

_ALI_BEGIN
template <typename T>
struct is_array_multidimensional
{
	static constexpr bool value =
		std::is_array<std::remove_extent<T>::type>::value;
};

template <typename T>
struct is_vector {
    // By default, allow any type
    static constexpr bool value = false;
};

template <typename T, typename Allocator>
struct is_vector<std::vector<T, Allocator>> {
    // Specialization for std::vector
    static constexpr bool value = true;
};

template <typename T>
struct is_vector_multidimensional
{
	static constexpr bool value =
		is_vector<T::value_type>::value;
};
_ALI_END
#pragma once
#include <type_traits>

template <typename T>
struct is_array_multidimensional
{
	static constexpr bool value =
		std::is_array<std::remove_extent<T>::type>::value;
};

// Primary template
template <typename T>
struct variable_template {
	using type = T;
};

// Specialization for template types
template <template <typename...> class Template, typename T, typename... Args>
struct variable_template<Template<T, Args...>> {
	using type = T;
};

template<typename T, typename ...A>
struct return_type;

template<typename F, typename ...A>
struct return_type<F(*)(A...)> {
	using type = F;
};

template<typename F, typename ...A>
struct return_type<F(A...)> {
	using type = std::invoke_result<F, A...>::type;
};

template<typename T>
struct lambda_return_type;

template<typename L, typename ...A>
struct lambda_return_type<L(A...)> {
	
};
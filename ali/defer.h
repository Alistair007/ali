#pragma once
#include <functional>

template<typename T>
class awaiting_function
{
public:
	awaiting_function(std::function<T()> f) {
		func = f;
	}
	~awaiting_function() {
		if (!skipped) {
			func();
		}
	}
	
	T skip_wait() {
		if (!skipped) {
			skipped = true;
			return func();
		}
		else throw("Function wait can't be skipped twice!");
	}

	T call() {
		return func();
	}
private:
	std::function<T()> func;
	bool skipped = false;
};

template<typename T>
class defer
{
public:
	template<typename Func, typename... Args>
	defer(Func&& func, Args&&... args) {
		// Use std::bind to create a callable object from the provided function and arguments
		auto bound_func = std::bind(std::forward<Func>(func), std::forward<Args>(args)...);

		this->func = bound_func;
	}
	awaiting_function<T> operator()() {
		return awaiting_function<T>(func);
	}
private:
	std::function<T()> func;
};

#define FUNC(function) <int>([&] {function; return 0;})
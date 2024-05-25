#pragma once
#include <type_traits>
#include <thread>
#include "meta.h"

template<typename _Func>
class promise
{
public:
	template<typename ..._Args>
	promise(_Func f, _Args... args) {
		thread = new std::thread([&] {
			ret_val = f(args...);
			done = true;
			});
	}

	return_type<_Func>::type await() {
		thread->join();
		return ret_val;
	}
private:
	std::thread* thread = nullptr;
	bool done = false;
	return_type<_Func>::type ret_val;
};


template<typename _Func>
class function {
public:
	function(_Func f) : func(f) {}

	template<typename... _Args>
	return_type<_Func>::type operator()(_Args... args) {
		return func(args...);
	}

	template<typename... _Args>
	promise<_Func> async(_Args... args) {
		return promise(func);
	}
private:
	_Func func;
};